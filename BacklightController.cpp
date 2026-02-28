#include "BacklightController.h"

#include <QDebug>
#include <QtGlobal>

#if __has_include(<pigpiod_if2.h>)
#include <pigpiod_if2.h>
#define BIKECOMPUTER_HAS_PIGPIOD 1
#else
#define BIKECOMPUTER_HAS_PIGPIOD 0
#endif

BacklightController::BacklightController(QObject *parent)
    : QObject(parent),
      m_brightness(70),
      m_initialized(false),
      m_unavailable(false),
      m_pi(-1),
      m_pwmGpio(18),
      m_pwmFrequency(qEnvironmentVariableIntValue("BIKECOMPUTER_BACKLIGHT_PWM_HZ", nullptr))
{
    if (m_pwmFrequency <= 0) {
        m_pwmFrequency = 2000;
    }
}

BacklightController::~BacklightController()
{
#if BIKECOMPUTER_HAS_PIGPIOD
    if (m_pi >= 0) {
        set_PWM_dutycycle(m_pi, m_pwmGpio, 0);
        pigpio_stop(m_pi);
        m_pi = -1;
    }
#endif
}


int BacklightController::brightness() const
{
    return m_brightness;
}

void BacklightController::increase()
{
    setBrightness(m_brightness + 10);
}

void BacklightController::decrease()
{
    setBrightness(m_brightness - 10);
}

void BacklightController::markUnavailable(const QString &reason)
{
    if (m_unavailable) {
        return;
    }

    m_unavailable = true;
    qWarning() << "Backlight PWM unavailable:" << reason;
}

bool BacklightController::ensurePwmReady()
{
#if BIKECOMPUTER_HAS_PIGPIOD
    if (m_unavailable) {
        return false;
    }

    if (m_initialized) {
        return true;
    }

    m_pi = pigpio_start(nullptr, nullptr);
    if (m_pi < 0) {
        markUnavailable(QStringLiteral("pigpio_start failed; is pigpiod running?"));
        return false;
    }

    set_mode(m_pi, m_pwmGpio, PI_OUTPUT);
    const int actualFreq = set_PWM_frequency(m_pi, m_pwmGpio, m_pwmFrequency);
    if (actualFreq <= 0) {
        markUnavailable(QStringLiteral("set_PWM_frequency failed on GPIO18"));
        return false;
    }

    if (set_PWM_range(m_pi, m_pwmGpio, 100) < 0) {
        markUnavailable(QStringLiteral("set_PWM_range failed on GPIO18"));
        return false;
    }

    m_initialized = true;
    return true;
#else
    markUnavailable(QStringLiteral("pigpiod_if2.h not available at build time"));
    return false;
#endif
}

void BacklightController::setBrightness(int percent)
{
    const int clamped = qBound(5, percent, 100);
    if (clamped == m_brightness && m_initialized) {
        return;
    }

    if (!ensurePwmReady()) {
        return;
    }

#if BIKECOMPUTER_HAS_PIGPIOD
    const int rc = set_PWM_dutycycle(m_pi, m_pwmGpio, clamped);
    if (rc != 0) {
        markUnavailable(QStringLiteral("set_PWM_dutycycle failed on GPIO18"));
        return;
    }

    m_brightness = clamped;
    emit brightnessChanged();
#endif
}
