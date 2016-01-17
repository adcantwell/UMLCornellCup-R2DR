#pragma once
#include "SerialPortWrapper.h"
#include "iRobotCreate2.h"

public ref class Server
{
public:
	iRobotCreate2 Create2;
	bool Init();
	void Cleanup();
};