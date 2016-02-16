#include "iRobotThread.h"

iRobotThread::iRobotThread()
{
	iSleepMS = 15;
}

void iRobotThread::Start()
{
	CommandQueue = gcnew ConcurrentQueue<iRobotCreate2::CreateCommand^>;
	ThreadWrapper::Start();
}

void iRobotThread::Entry()
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