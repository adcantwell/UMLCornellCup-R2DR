#include "Server.h"

Server::Server()
{
	bInit = false;
}

bool Server::Init()
{
	Create2.CreatePort = gcnew SerialPort();
	CreateWriteThread = gcnew ThreadWrapper();

	if (SerialPortWrapper::Open(Create2.CreatePort, CREATE2_PORT_NUMBER, CREATE2_BAUD, CREATE2_PARITY, CREATE2_DATABITS, CREATE2_STOPBITS, CREATE2_FLOWCONTROL))
		bInit = true;

	return bInit;
}

bool Server::StartCreateWriteThread()
{
	if (CreateWriteThread == nullptr)
	{
		return false;
	}

	CreateWriteThread->Start();
	return true;
}

bool Server::StopCreateWriteThread()
{
	if (CreateWriteThread == nullptr)
	{
		return false;
	}

	CreateWriteThread->Stop();
	return true;
}

void Server::AddCreateCommandToQueue(iRobotCreate2::CreateCommand^ Cmd)
{
	CreateWriteThread->CommandQueue->Enqueue(Cmd);
}

void Server::Cleanup()
{
	Create2.SendStopCommand_Direct();
	StopCreateWriteThread();
	SerialPortWrapper::Close(Create2.CreatePort);
}

