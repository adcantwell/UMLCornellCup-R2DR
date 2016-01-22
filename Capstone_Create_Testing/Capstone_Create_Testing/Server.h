#pragma once
#include "SerialPortWrapper.h"
#include "iRobotCreate2.h"
#include "ThreadWrapper.h"


public ref class Server
{
private:
	bool bInit;
	ThreadWrapper^ CreateWriteThread;
public:
	static iRobotCreate2 Create2;
	Server();
	bool Init();
	bool StartCreateWriteThread();
	bool StopCreateWriteThread();
	void AddCreateCommandToQueue(iRobotCreate2::CreateCommand^ Cmd);
	void Cleanup();
};