#pragma once

#include <memory>

class ISensor;

class Alarm
{
public:
    using UniqueSensor = std::unique_ptr<ISensor>;
    explicit Alarm(UniqueSensor s);
    [[deprecated("inject sensor via the appropriate ctor")]]
    Alarm();
    double lowThreshold () const;
    double highThreshold() const;
    void check();
    bool isAlarmOn();
protected:
    UniqueSensor m_sensor;
    const double m_lowPressureTreshold;
    const double m_highPressureTreshold;
    bool m_alarmOn;
};
