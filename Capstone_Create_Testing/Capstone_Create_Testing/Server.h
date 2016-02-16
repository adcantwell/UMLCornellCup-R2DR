#pragma once
#include "SerialPortWrapper.h"
#include "iRobotCreate2.h"
#include "iRobotThread.h"
#include "R200.h"
#include "RSThread.h"


public ref class Server
{
private:
	bool bInit;
	static iRobotThread^ CreateWriteThread;
	static RSThread^ RSDataThread;
public:
	static iRobotCreate2 Create2;
	static R200 RSR200;
	Server();
	bool Init();

	bool StartCreateWriteThread();
	bool StopCreateWriteThread();
	static void AddCreateCommandToQueue(iRobotCreate2::CreateCommand^ Cmd);

	bool StartRSDataThread();
	bool StopRSDataThread();

	void Cleanup();
};