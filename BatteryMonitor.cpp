#include "BatteryMonitor.h"

#include <QDebug>
#include <QTimer>
#include <QtGlobal>

#include <algorithm>
#include <cstdint>

#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>

namespace {
constexpr const char *kI2cDev = "/dev/i2c-0";
constexpr int kAddress = 0x36;
constexpr uint8_t kSocRegister = 0x04;
constexpr int kDefaultPollIntervalMs = 60000;
constexpr int kMinPollIntervalMs = 5000;
}

BatteryMonitor::BatteryMonitor(QObject *parent)
    : QObject(parent),
      m_available(false),
      m_percent(0),
      m_warned(false),
      m_timer(new QTimer(this))
{
    connect(m_timer, &QTimer::timeout, this, [this]() { poll(); });
    int pollMs = qEnvironmentVariableIntValue("BIKECOMPUTER_BATTERY_POLL_MS", nullptr);
    if (pollMs < kMinPollIntervalMs) {
        pollMs = kDefaultPollIntervalMs;
    }
    m_timer->setInterval(pollMs);
    poll();
    m_timer->start();
}

bool BatteryMonitor::available() const
{
    return m_available;
}

int BatteryMonitor::percent() const
{
    return m_percent;
}

void BatteryMonitor::poll()
{
    bool changed = false;

    const int fd = ::open(kI2cDev, O_RDWR);
    if (fd < 0) {
        if (!m_warned) {
            qWarning() << "BatteryMonitor: cannot open" << kI2cDev;
            m_warned = true;
        }
        if (m_available) {
            m_available = false;
            changed = true;
        }
        if (changed) emit batteryChanged();
        return;
    }

    if (ioctl(fd, I2C_SLAVE, kAddress) < 0) {
        if (!m_warned) {
            qWarning() << "BatteryMonitor: cannot select I2C address" << Qt::hex << kAddress;
            m_warned = true;
        }
        ::close(fd);
        if (m_available) {
            m_available = false;
            changed = true;
        }
        if (changed) emit batteryChanged();
        return;
    }

    uint8_t reg = kSocRegister;
    if (::write(fd, &reg, 1) != 1) {
        if (!m_warned) {
            qWarning() << "BatteryMonitor: failed writing register" << Qt::hex << int(kSocRegister);
            m_warned = true;
        }
        ::close(fd);
        if (m_available) {
            m_available = false;
            changed = true;
        }
        if (changed) emit batteryChanged();
        return;
    }

    uint8_t data[2] = {0, 0};
    if (::read(fd, data, 2) != 2) {
        if (!m_warned) {
            qWarning() << "BatteryMonitor: failed reading SOC bytes";
            m_warned = true;
        }
        ::close(fd);
        if (m_available) {
            m_available = false;
            changed = true;
        }
        if (changed) emit batteryChanged();
        return;
    }

    ::close(fd);

    m_warned = false;

    const uint16_t raw = (uint16_t(data[0]) << 8) | uint16_t(data[1]);
    const int computed = std::clamp(int(raw / 256), 0, 100);

    if (!m_available) {
        m_available = true;
        changed = true;
    }
    if (m_percent != computed) {
        m_percent = computed;
        changed = true;
    }

    if (changed) {
        emit batteryChanged();
    }
}
