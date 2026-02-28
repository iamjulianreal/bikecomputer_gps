#pragma once

#include <QObject>

class QTimer;

class BatteryMonitor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool available READ available NOTIFY batteryChanged)
    Q_PROPERTY(int percent READ percent NOTIFY batteryChanged)

public:
    explicit BatteryMonitor(QObject *parent = nullptr);

    bool available() const;
    int percent() const;

signals:
    void batteryChanged();

private:
    void poll();

    bool m_available;
    int m_percent;
    bool m_warned;
    QTimer *m_timer;
};
