///////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright 2016 Advanced Software Engineering Limited
//
// You may use and modify the code in this file in your application, provided the code and
// its modifications are used only in conjunction with ChartDirector. Usage of this software
// is subjected to the terms and condition of the ChartDirector license.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef RANDOMDATA_HDR
#define RANDOMDATA_HDR

#include <QThread>

//
// A Random series generator using the random walk method
//
class RandomWalk : public QThread
{
Q_OBJECT
public:

    typedef void DataHandler(void *param, double elapsedTime, double series0, double series1);

	RandomWalk(DataHandler *handler, void *param);
    virtual ~RandomWalk();

    // stop the thread
    void stop();

protected :
    // The thread of the random series generator
    void run();

private :

    // Disable copying and assignment
    RandomWalk & operator=(const RandomWalk&);
    RandomWalk(const RandomWalk&);

    // Flag to stop the flag
    bool stopThread;

    // The callback function to handle the generated data
	DataHandler *handler;
	void *param;
};

#endif

