
#include "Sensor.h"

#include <cstdlib>
#include <time.h>

Sensor::Sensor()
    : ISensor()
{
    srand((unsigned)time(0));
}

Sensor::~Sensor()
{
}

double Sensor::popNextPressurePsiValue()
{
    // placeholder implementation that simulates a real sensor in a real tire
    double pressure = 16 + (float)rand()/((float)RAND_MAX/(6));
    return pressure;
}
