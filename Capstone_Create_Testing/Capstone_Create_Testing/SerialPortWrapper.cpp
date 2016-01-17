#include "SerialPortWrapper.h"
using namespace std;

bool SerialPortWrapper::Open(SerialPort^ Port, unsigned __int16 PortNumber, unsigned __int32 BaudRate, Parity Parity, unsigned __int16 DataBits, StopBits StopBits, Handshake FlowControl)
{
	String^ strPort = String::Format("COM{0}", PortNumber);

	bool PortExists;

	for each (String^ s in SerialPort::GetPortNames())
	{
		if (strPort->Equals(s))
		{
			PortExists = true;
			break;
		}

		PortExists = false;
	}
	
	if (PortExists)
	{
		SetPortName(Port, strPort);
		SetPortBaudRate(Port, BaudRate);
		SetPortParity(Port, Parity);
		SetPortDataBits(Port, DataBits);
		SetPortStopBits(Port, StopBits);
		SetPortFlowControl(Port, FlowControl);
		Port->ReadTimeout = 500;
		Port->WriteTimeout = 500;
		Port->Open();
		if (Port->IsOpen)
		{
			return true;
		}
	}
	return false;
}

void SerialPortWrapper::Close(SerialPort^ Port)
{
	Port->Close();
}

void SerialPortWrapper::SetPortName(SerialPort^ Port, String^ PortName)
{
	Port->PortName = PortName;
}
void SerialPortWrapper::SetPortBaudRate(SerialPort^ Port, unsigned __int32 BaudRate)
{
	Port->BaudRate = BaudRate;
}
void SerialPortWrapper::SetPortParity(SerialPort^ Port, Parity PortParity)
{
	Port->Parity = PortParity;
}
void SerialPortWrapper::SetPortDataBits(SerialPort^ Port, unsigned __int16 PortDataBits)
{
	Port->DataBits = PortDataBits;
}
void SerialPortWrapper::SetPortStopBits(SerialPort^ Port, StopBits PortStopBits)
{
	Port->StopBits = PortStopBits;
}
void SerialPortWrapper::SetPortFlowControl(SerialPort^ Port, Handshake PortFlowControl)
{
	Port->Handshake = PortFlowControl;
}