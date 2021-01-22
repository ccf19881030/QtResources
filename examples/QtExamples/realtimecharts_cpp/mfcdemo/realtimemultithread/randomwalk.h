///////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright 2016 Advanced Software Engineering Limited
//
// You may use and modify the code in this file in your application, provided the code and
// its modifications are used only in conjunction with ChartDirector. Usage of this software
// is subjected to the terms and condition of the ChartDirector license.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef RANDOMDATA_HDR
#define RANDOMDATA_HDR

#include <afxmt.h>

//
// A Random series generator using the random walk method
//
class RandomWalk
{
public:

    typedef void DataHandler(void *param, double elapsedTime, double series0, double series1);

	RandomWalk(DataHandler *handler, void *param);
	~RandomWalk();
	void start();
	void stop();

private :

    // Disable copying and assignment
    RandomWalk & operator=(const RandomWalk&);
    RandomWalk(const RandomWalk&);

    // The main thread of the random series generator
	CWinThread *thread;
	static UINT threadProc(LPVOID obj);
	bool stopThread;

    // The callback function to handle the generated data
	DataHandler *handler;
	void *param;
};

#endif
