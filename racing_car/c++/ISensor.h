#pragma once

class ISensor
{
public:
    virtual ~ISensor() = 0;
    virtual double popNextPressurePsiValue() = 0;
};

inline ISensor::~ISensor()
{
}
