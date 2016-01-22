#pragma once
#using <System.dll>
using namespace System;
using namespace System::Threading;

public ref class ThrThread
{
private:
	Thread^ thread;

	unsigned __int32 iSleepMS;

public:
	// constructor
	ThrThread()
	{
		iSleepMS = 0;
	}

	// destructor
	~ThrThread()
	{
	}

	// call this function to start thread
	void Start()
	{
		thread = gcnew Thread(gcnew ThreadStart(this, &ThrThread::Entry));
		thread->Start();
	}

	// call this function to stop thread
	bool Stop()
	{
		if (thread == nullptr)
		{
			return false;
		}

		thread->Abort();

		return true;
	}

	// thread entry point
	void Entry()
	{
		while (true)
		{
			Console::WriteLine("TEST");

			if (iSleepMS > 0)
			{
				thread->Sleep(iSleepMS);
			}
		}
	}
};

public ref class Server
{
private:
	bool bInit, bRunning;

	ThrThread^ thrRead;

public:
	// constructor
	Server()
	{
		bInit = false;
		bRunning = false;
	}

	// setup method
	bool Init()
	{
		thrRead = gcnew ThrThread();

		bInit = true;

		return bInit;
	}

	// start read thread
	bool StartReadThread()
	{
		if (thrRead == nullptr)
		{
			return false;
		}

		thrRead->Start();

		return true;
	}

	// stop read thread
	bool StopReadThread()
	{
		if (thrRead == nullptr)
		{
			return false;
		}

		thrRead->Stop();

		return true;
	}
};

//ConcurrrentQueue, custom datatype that contains function pointer and arguments list.  X camera condition -> add custom datatype containing appropriate function and args onto Queue
//in the Entry() function of the thread, pop the Queue and call the function