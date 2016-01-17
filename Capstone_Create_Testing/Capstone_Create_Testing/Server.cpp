#include "Server.h"

bool Server::Init()
{
	Create2.CreatePort = gcnew SerialPort();

	if (SerialPortWrapper::Open(Create2.CreatePort, CREATE_PORT_NUMBER, CREATE2_BAUD, CREATE2_PARITY, CREATE2_DATABITS, CREATE2_STOPBITS, CREATE2_FLOWCONTROL))
		return true;

	return false;
}

void Server::Cleanup()
{
	Create2.SendStopCommand();
	SerialPortWrapper::Close(Create2.CreatePort);
}

