#pragma once
#include "iRobotCreate2.h"
#using <System.dll>
using namespace System;
using namespace System::Threading;
using namespace System::Collections::Concurrent;


//#include "Server.h"

public ref class ThreadWrapper
{
private:
	Thread^ thread;

	unsigned __int32 iSleepMS;

public:
	// constructor
	ThreadWrapper();
	// call this function to start thread
	void Start();
	// call this function to stop thread
	bool Stop();
	// thread entry point
	void Entry();
	// queue for sending commands to the create
	ConcurrentQueue<iRobotCreate2::CreateCommand^>^ CommandQueue;
};