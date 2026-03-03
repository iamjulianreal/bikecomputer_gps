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
        hardware_PWM(m_pi, m_pwmGpio, 0, 0);
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

    // Use hardware PWM on GPIO18 to avoid interfering with bit-banged GPS serial
    const int rc = hardware_PWM(m_pi, m_pwmGpio, static_cast<unsigned>(m_pwmFrequency), 0);
    if (rc != 0) {
        markUnavailable(QStringLiteral("hardware_PWM init failed on GPIO18"));
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
    const unsigned dutyCycle = static_cast<unsigned>((clamped * 1000000) / 100);
    const int rc = hardware_PWM(m_pi, m_pwmGpio, static_cast<unsigned>(m_pwmFrequency), dutyCycle);
    if (rc != 0) {
        markUnavailable(QStringLiteral("hardware_PWM failed on GPIO18"));
        return;
    }

    m_brightness = clamped;
    emit brightnessChanged();
#endif
}
