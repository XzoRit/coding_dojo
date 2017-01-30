#pragma once
#include "ISensor.h"

class Sensor : public ISensor
{
public:
    Sensor();
    ~Sensor() override;
    double popNextPressurePsiValue() override;
};
