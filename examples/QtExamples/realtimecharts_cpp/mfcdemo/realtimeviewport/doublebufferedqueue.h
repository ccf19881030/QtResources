///////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright 2016 Advanced Software Engineering Limited
//
// You may use and modify the code in this file in your application, provided the code and
// its modifications are used only in conjunction with ChartDirector. Usage of this software
// is subjected to the terms and condition of the ChartDirector license.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef DOUBLEBUFFEREDQUEUE_HDR
#define DOUBLEBUFFEREDQUEUE_HDR

template <class T>
class DoubleBufferedQueue
{
public:

    //
    // Constructor - construct a queue with the given buffer size
    //
	DoubleBufferedQueue(int bufferSize = 10000) :
		bufferLen(0), bufferSize(bufferSize)
	{ 
		buffer0 = buffer = new T[bufferSize]; 
		buffer1 = new T[bufferSize];
		InitializeCriticalSection(&lock);
	}

    //
    // Destructor
    //
	~DoubleBufferedQueue()
	{
		 DeleteCriticalSection(&lock);
		 delete[] buffer0;
		 delete[] buffer1;
	}

    //
    // Add an item to the queue. Returns true if successful, false if the buffer is full.
    //
	bool put(const T& datum)
	{
		EnterCriticalSection(&lock);
		bool canWrite = bufferLen < bufferSize;
		if (canWrite) buffer[bufferLen++] = datum;
		LeaveCriticalSection(&lock);
		return canWrite;
	}

    //
    // Get all the items in the queue. The T** argument should be the address of a variable to
    // receive the pointer to the item array. The return value is the size of the array.
    //
	int get(T** data)
	{
		EnterCriticalSection(&lock);
		*data = buffer;
		int ret = bufferLen;
		buffer = (buffer == buffer0) ? buffer1 : buffer0;
		bufferLen = 0;
		LeaveCriticalSection(&lock);
		return ret;
	}

private:

    // Disable copying and assignment
    DoubleBufferedQueue & operator=(const DoubleBufferedQueue&);
    DoubleBufferedQueue(const DoubleBufferedQueue&);

	T* buffer0;
	T* buffer1;
	T* buffer;
	int bufferLen;
	int bufferSize;
	CRITICAL_SECTION lock;
};


#endif
