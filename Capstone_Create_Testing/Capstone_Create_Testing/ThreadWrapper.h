#pragma once
#include "iRobotCreate2.h"
#using <System.dll>
using namespace System;
using namespace System::Threading;
using namespace System::Collections::Concurrent;


//#include "Server.h"

public ref class ThreadWrapper
{
protected:
	Thread^ thread;

	unsigned __int32 iSleepMS;

public:
	// constructor
	ThreadWrapper();
	// call this function to start thread
	virtual void Start();
	// call this function to stop thread
	virtual bool Stop();
	// thread entry point
	virtual void Entry();
};