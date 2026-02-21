#pragma once

#include <QObject>
#include <QString>
#include <QSocketNotifier>
#include <QElapsedTimer>

#include <gpiod.h>

// libgpiod v2 Reader: emits pressed() on falling edge and pressedChanged(true/false) on both edges
class GpioReader : public QObject
{
  Q_OBJECT

public:
  // chipPath e.g. "/dev/gpiochip0", lineOffset e.g. 17
  explicit GpioReader(const QString& chipPath,
                      unsigned int lineOffset,
                      int debounceMs = 35,
                      QObject* parent = nullptr)
    : QObject(parent),
      m_chipPath(chipPath),
      m_offset(lineOffset),
      m_debounceMs(debounceMs)
  {
    m_timer.start();

    // open chip
    m_chip = gpiod_chip_open(m_chipPath.toUtf8().constData());
    if (!m_chip) {
      emit error(QString("gpiod_chip_open(%1) failed").arg(m_chipPath));
      return;
    }

    // settings: input + pull-up + both edges
    m_settings = gpiod_line_settings_new();
    if (!m_settings) {
      emit error("gpiod_line_settings_new failed");
      return;
    }

    gpiod_line_settings_set_direction(m_settings, GPIOD_LINE_DIRECTION_INPUT);

    // Pull-up (Button to GND)
    gpiod_line_settings_set_bias(m_settings, GPIOD_LINE_BIAS_PULL_UP);

    // We need BOTH edges for hold detection (press + release)
    gpiod_line_settings_set_edge_detection(m_settings, GPIOD_LINE_EDGE_BOTH);

    // line config
    m_lineConfig = gpiod_line_config_new();
    if (!m_lineConfig) {
      emit error("gpiod_line_config_new failed");
      return;
    }

    unsigned int offsets[1] = { m_offset };
    if (gpiod_line_config_add_line_settings(m_lineConfig, offsets, 1, m_settings) < 0) {
      emit error(QString("gpiod_line_config_add_line_settings failed (line %1)").arg(m_offset));
      return;
    }

    // request config
    m_reqConfig = gpiod_request_config_new();
    if (!m_reqConfig) {
      emit error("gpiod_request_config_new failed");
      return;
    }

    gpiod_request_config_set_consumer(m_reqConfig, "bikecomputer");

    // request lines
    m_request = gpiod_chip_request_lines(m_chip, m_reqConfig, m_lineConfig);
    if (!m_request) {
      emit error(QString("gpiod_chip_request_lines failed (line %1). Permission?").arg(m_offset));
      return;
    }

    // event buffer
    m_eventBuf = gpiod_edge_event_buffer_new(8);
    if (!m_eventBuf) {
      emit error("gpiod_edge_event_buffer_new failed");
      return;
    }

    // socket notifier on request fd
    const int fd = gpiod_line_request_get_fd(m_request);
    if (fd < 0) {
      emit error("gpiod_line_request_get_fd failed");
      return;
    }

    m_notifier = new QSocketNotifier(fd, QSocketNotifier::Read, this);
    connect(m_notifier, &QSocketNotifier::activated, this, &GpioReader::handleReadable);
  }

  ~GpioReader() override
  {
    if (m_notifier) {
      m_notifier->setEnabled(false);
      delete m_notifier;
      m_notifier = nullptr;
    }

    if (m_eventBuf) {
      gpiod_edge_event_buffer_free(m_eventBuf);
      m_eventBuf = nullptr;
    }

    if (m_request) {
      gpiod_line_request_release(m_request);
      m_request = nullptr;
    }

    if (m_reqConfig) {
      gpiod_request_config_free(m_reqConfig);
      m_reqConfig = nullptr;
    }

    if (m_lineConfig) {
      gpiod_line_config_free(m_lineConfig);
      m_lineConfig = nullptr;
    }

    if (m_settings) {
      gpiod_line_settings_free(m_settings);
      m_settings = nullptr;
    }

    if (m_chip) {
      gpiod_chip_close(m_chip);
      m_chip = nullptr;
    }
  }

signals:
  void pressed();                 // falling edge (button pressed, assuming pull-up)
  void pressedChanged(bool down); // true on falling, false on rising (for long-press)
  void error(QString msg);

private slots:
  void handleReadable()
  {
    if (!m_request || !m_eventBuf) return;

    const qint64 now = m_timer.elapsed();
    if (now - m_lastMs < m_debounceMs) {
      // debounce: ignore fast bounces
      // still consume events so fd doesn't stay readable
      (void)gpiod_line_request_read_edge_events(m_request, m_eventBuf, 8);
      return;
    }

    const int n = gpiod_line_request_read_edge_events(m_request, m_eventBuf, 8);
    if (n <= 0) return;

    // take the newest event (last one) to avoid backlog jitter
    struct gpiod_edge_event* ev = gpiod_edge_event_buffer_get_event(m_eventBuf, n - 1);
    if (!ev) return;

    const int type = gpiod_edge_event_get_event_type(ev);

    m_lastMs = now;

    if (type == GPIOD_EDGE_EVENT_FALLING_EDGE) {
      emit pressedChanged(true);
      emit pressed(); // keep old behavior
    } else if (type == GPIOD_EDGE_EVENT_RISING_EDGE) {
      emit pressedChanged(false);
    }
  }

private:
  QString m_chipPath;
  unsigned int m_offset = 0;
  int m_debounceMs = 35;

  QElapsedTimer m_timer;
  qint64 m_lastMs = -1000000;

  QSocketNotifier* m_notifier = nullptr;

  struct gpiod_chip* m_chip = nullptr;
  struct gpiod_request_config* m_reqConfig = nullptr;
  struct gpiod_line_settings* m_settings = nullptr;
  struct gpiod_line_config* m_lineConfig = nullptr;
  struct gpiod_line_request* m_request = nullptr;
  struct gpiod_edge_event_buffer* m_eventBuf = nullptr;
};
