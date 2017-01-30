#include "Alarm.h"
#include "Sensor.h"
#include "ISensor.h"

Alarm::Alarm(UniqueSensor s)
    : m_sensor(std::move(s))
    , m_lowPressureTreshold(17)
    , m_highPressureTreshold(21)
    , m_alarmOn(false)
{}

Alarm::Alarm()
    : Alarm(std::make_unique<Sensor>())
{}

double Alarm::lowThreshold() const
{
    return m_lowPressureTreshold;
}

double Alarm::highThreshold() const
{
    return m_highPressureTreshold;
}

void Alarm::check()
{
  double psiPressureValue = m_sensor->popNextPressurePsiValue();

  if(psiPressureValue < m_lowPressureTreshold ||
      m_highPressureTreshold < psiPressureValue)
  {
    m_alarmOn = true;
  }
}

bool Alarm::isAlarmOn()
{
  return m_alarmOn;
}
