///////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright 2016 Advanced Software Engineering Limited
//
// You may use and modify the code in this file in your application, provided the code and
// its modifications are used only in conjunction with ChartDirector. Usage of this software
// is subjected to the terms and condition of the ChartDirector license.
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "randomwalk.h"
#include <math.h>


// The period of the data series in milliseconds. This random series implementation just use the 
// windows timer for timing. In many computers, the default windows timer resolution is 1/64 sec,
// or 15.6ms. This means the interval may not be exactly accurate.
const int interval = 100;

//
// Constructor. The handler is the function to call then new data are generated. The "param" is a
// parameter for passing to the handler function.
//
RandomWalk::RandomWalk(RandomWalk::DataHandler *handler, void *param)
: thread(0), stopThread(true), handler(handler), param(param)
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
// Start the random generator thread
//
void RandomWalk::start()
{
	if (0 == thread)
	{
		thread = AfxBeginThread(threadProc, this, 0, 0, CREATE_SUSPENDED);  
		thread->m_bAutoDelete = FALSE;
		stopThread = false;
		thread->ResumeThread();			
	}
}

//
// Stop the random generator thread
//
void RandomWalk::stop()
{
	if (0 != thread)
    {
		stopThread = true;
		::WaitForSingleObject(thread->m_hThread, INFINITE);
		delete thread;
        thread = 0;
	}
}

//
// The random generator thread
//
UINT RandomWalk::threadProc(LPVOID obj)
{
	RandomWalk *self = (RandomWalk *)obj;

    // Variables to keep track of the timing
	bool isFirst = true;
	LARGE_INTEGER startTime;
	LARGE_INTEGER currentTime;
	LARGE_INTEGER nextTime;
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency); 
	
    // Random walk variables
	srand(999);
	double series0 = 32;
	double series1 = 63;
    double upperLimit = 94;
    double scaleFactor = sqrt(interval * 0.1);

	while (!self->stopThread)
	{
        // Get current elapsed time
		QueryPerformanceCounter(&currentTime);
		if (isFirst)
		{
			startTime = nextTime = currentTime;
			isFirst = false;
		}

        // Compute the next data value
		double elapsedTime = (currentTime.QuadPart - startTime.QuadPart) / (double)frequency.QuadPart;
		if ((series0 = fabs(series0 + (rand() / (double)RAND_MAX - 0.5) * scaleFactor)) > upperLimit)
			series0 = upperLimit * 2 - series0;
		if ((series1 = fabs(series1 + (rand() / (double)RAND_MAX - 0.5) * scaleFactor)) > upperLimit)
			series1 = upperLimit * 2 - series1;
		
        // Call the handler
		self->handler(self->param, elapsedTime, series0, series1);

        // Sleep until next walk
		if ((nextTime.QuadPart += frequency.QuadPart * interval / 1000) <= currentTime.QuadPart)
			nextTime.QuadPart = currentTime.QuadPart + frequency.QuadPart * interval / 1000;

		::Sleep((int)((nextTime.QuadPart - currentTime.QuadPart) * 1000 / frequency.QuadPart));		
	}

	return 0;
}
