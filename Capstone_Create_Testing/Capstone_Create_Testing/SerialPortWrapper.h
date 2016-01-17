#pragma once
#include <iostream>
#include <sstream>
#using <System.dll>
using namespace System;
using namespace System::IO::Ports;

public ref class SerialPortWrapper
{
public:
	static bool Open(SerialPort^ Port, unsigned __int16 PortNumber, unsigned __int32 BaudRate, Parity Parity, unsigned __int16 DataBits, StopBits StopBits, Handshake FlowControl);
	static void SetPortName(SerialPort^ Port, String^ PortName);
	static void SetPortBaudRate(SerialPort^ Port, unsigned __int32 BaudRate);
	static void SetPortParity(SerialPort^ Port, Parity PortParity);
	static void SetPortDataBits(SerialPort^ Port, unsigned __int16 PortDataBits);
	static void SetPortStopBits(SerialPort^ Port, StopBits PortStopBits);
	static void SetPortFlowControl(SerialPort^ Port, Handshake PortFlowControl);
	static void Close(SerialPort^ Port);
};