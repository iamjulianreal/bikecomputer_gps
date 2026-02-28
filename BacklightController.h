#pragma once

#include <QObject>
#include <QString>

class BacklightController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int brightness READ brightness NOTIFY brightnessChanged)

public:
    explicit BacklightController(QObject *parent = nullptr);
    ~BacklightController() override;

    int brightness() const;

    Q_INVOKABLE void increase();
    Q_INVOKABLE void decrease();

signals:
    void brightnessChanged();

private:
    bool ensurePwmReady();
    void setBrightness(int percent);
    void markUnavailable(const QString &reason);

    int m_brightness;
    bool m_initialized;
    bool m_unavailable;
    int m_pi;
    int m_pwmGpio;
    int m_pwmFrequency;
};
