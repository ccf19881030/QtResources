///////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright 2016 Advanced Software Engineering Limited
//
// You may use and modify the code in this file in your application, provided the code and
// its modifications are used only in conjunction with ChartDirector. Usage of this software
// is subjected to the terms and condition of the ChartDirector license.
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "randomwalk.h"
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
RandomWalk::RandomWalk(RandomWalk::DataHandler *handler, void *param)
: stopThread(false), handler(handler), param(param)
{
}

//
// Destructor
//
RandomWalk::~RandomWalk()
{
	stop();
}

//
// Stop the random generator thread
//
void RandomWalk::stop()
{
    stopThread = true;
    wait();
    stopThread = false;
}

//
// The random generator thread
//
void RandomWalk::run()
{
    qint64 currentTime = 0;
    qint64 nextTime = 0;
	
    // Random walk variables
	srand(999);
	double series0 = 32;
	double series1 = 63;
    double upperLimit = 94;
    double scaleFactor = sqrt(interval * 0.1);

    // Variables to keep track of the timing
    QElapsedTimer timer;
    timer.start();

    while (!stopThread)
	{
        // Compute the next data value
        currentTime = timer.elapsed();
        if ((series0 = fabs(series0 + (rand() / (double)RAND_MAX - 0.5) * scaleFactor)) > upperLimit)
			series0 = upperLimit * 2 - series0;
		if ((series1 = fabs(series1 + (rand() / (double)RAND_MAX - 0.5) * scaleFactor)) > upperLimit)
			series1 = upperLimit * 2 - series1;

        // Call the handler
        handler(param, currentTime / 1000.0, series0, series1);

        // Sleep until next walk
        if ((nextTime += interval) <= currentTime)
            nextTime = currentTime + interval;

        msleep((unsigned long)(nextTime - currentTime));
	}
}
