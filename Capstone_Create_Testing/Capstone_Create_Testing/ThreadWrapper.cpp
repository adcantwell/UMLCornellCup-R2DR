#include "ThreadWrapper.h"
// constructor
ThreadWrapper::ThreadWrapper()
{
	iSleepMS = 15;
}

// call this function to start thread
void ThreadWrapper::Start()
{
	thread = gcnew Thread(gcnew ThreadStart(this, &ThreadWrapper::Entry));
	CommandQueue = gcnew ConcurrentQueue<iRobotCreate2::CreateCommand^>;
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
	while (true)
	{
		iRobotCreate2::CreateCommand^ Cmd;
		
		if (CommandQueue->TryDequeue(Cmd))
		{
			Cmd->SendCommand();
		}
	
		if (iSleepMS > 0)
		{
			thread->Sleep(iSleepMS);
		}
	}
}