#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "ISensor.h"

class StubSensor : public ISensor
{
public:
  double popNextPressurePsiValue() override;
  void value(double v);
private:
  double m_value;
};

inline double StubSensor::popNextPressurePsiValue()
{
  return m_value;
}

inline void StubSensor::value(double v)
{
  m_value = v;
}

#include <memory>

class SensorForwarder : public ISensor
{
public:
  explicit SensorForwarder(ISensor* s);
  ~SensorForwarder() override;
  double popNextPressurePsiValue() override;
private:
  ISensor* m_sensor;
};

inline SensorForwarder::SensorForwarder(ISensor* s)
  : m_sensor{s}
{
}

inline SensorForwarder::~SensorForwarder()
{
  m_sensor = nullptr;
}

inline double SensorForwarder::popNextPressurePsiValue()
{
  return m_sensor->popNextPressurePsiValue();
}

#include "Alarm.h"

TEST_CASE("alarm depends on sensor values")
{
  auto sensor = std::make_unique<StubSensor>();
  auto a = Alarm{std::make_unique<SensorForwarder>(sensor.get())};

  const double okValue     {a.lowThreshold()  + 0};
  const double tooLowValue {a.lowThreshold()  - 1};
  const double tooHighValue{a.highThreshold() + 1};

  SUBCASE("alarm is off if value is in ok range")
  {
    sensor->value(okValue);
    a.check();
    CHECK_FALSE(a.isAlarmOn());
  }
  SUBCASE("alarm is on")
  {
    SUBCASE("pressure under lower limit")
    {
      sensor->value(tooLowValue);
    }
    SUBCASE("pressure above higher limit")
    {
      sensor->value(tooHighValue);
    }
    a.check();
    CHECK(a.isAlarmOn());
  }
}

#include "HtmlTextConverter.h"
#include <sstream>

TEST_CASE("html text converter")
{
  const auto testTxt{"line 1\nline 2\nline 3\n"};
  const auto convertedTestTxt{"line 1<br />line 2<br />line 3<br />"};

  std::stringstream str;
  str << testTxt;
  CHECK(convertedTestTxt == HtmlTextConverter::convert(str));
}

int main(int argc, char** argv)
{
  doctest::Context context;

  context.applyCommandLine(argc, argv);
  int res = context.run();

  if(context.shouldExit()) return res;
  else return res;
}
