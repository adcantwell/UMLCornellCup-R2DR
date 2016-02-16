#include "ThreadWrapper.h"
// constructor
ThreadWrapper::ThreadWrapper()
{
	iSleepMS = 0;
}

// call this function to start thread
void ThreadWrapper::Start()
{
	thread = gcnew Thread(gcnew ThreadStart(this, &ThreadWrapper::Entry));
	thread->Start();
}

// call this function to stop thread
bool ThreadWrapper::Stop()
{
	if (thread == nullptr)
	{
		return false;
	}

	thread->Abort();

	return true;
}

// thread entry point
void ThreadWrapper::Entry()
{
	
}