///////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright 2016 Advanced Software Engineering Limited
//
// You may use and modify the code in this file in your application, provided the code and
// its modifications are used only in conjunction with ChartDirector. Usage of this software
// is subjected to the terms and condition of the ChartDirector license.
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "randomwave.h"
#include <math.h>
#include <QElapsedTimer>


// The period of the data series in milliseconds. This random series implementation just use the 
// windows timer for timing. In many computers, the default windows timer resolution is 1/64 sec,
// or 15.6ms. This means the interval may not be exactly accurate.
const int interval = 100;

//
// Constructor. The handler is the function to call then new data are generated. The "param" is a
// parameter for passing to the handler function.
//
RandomWave::RandomWave(RandomWave::DataHandler *handler, void *param)
: stopThread(false), handler(handler), param(param)
{
}

//
// Destructor
//
RandomWave::~RandomWave()
{
	stop();
}

//
// Stop the random generator thread
//
void RandomWave::stop()
{
    stopThread = true;
    wait();
    stopThread = false;
}

//
// The random generator thread
//
void RandomWave::run()
{
    qint64 currentTime = 0;
    qint64 nextTime = 0;
	
    // Variables to keep track of the timing
    QElapsedTimer timer;
    timer.start();

    while (!stopThread)
	{
        // Compute the next data value
        currentTime = timer.elapsed();
        double p = currentTime / 1000.0 * 4;
        double series0 = 20 + cos(p * 2.2) * 10 + 1 / (cos(p) * cos(p) + 0.01);
        double series1 = 210 + 60 * sin(p / 21.7) * sin(p / 7.8);

        // Call the handler
        handler(param, currentTime / 1000.0, series0, series1);

        // Sleep until next walk
        if ((nextTime += interval) <= currentTime)
            nextTime = currentTime + interval;

        msleep((unsigned long)(nextTime - currentTime));
	}
}
