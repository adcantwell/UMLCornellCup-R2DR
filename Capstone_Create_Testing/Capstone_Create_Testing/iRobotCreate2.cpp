#include "iRobotCreate2.h"

void iRobotCreate2::SendCommand(SerialPort^ Port, Opcode Cmd)
{
	array<Byte>^ FullCommmand = { Cmd };
	Port->Write(FullCommmand, 0, 1);
}

void iRobotCreate2::SendCommand(SerialPort^ Port, Opcode Cmd, __int16 DataBits[], __int8 NumDataBits)
{
	array<Byte>^ FullCommmand = gcnew array<Byte>(NumDataBits + 1);
	unsigned char uchar_buffer;

	uchar_buffer = static_cast<unsigned char>(Cmd);
	FullCommmand[0] = uchar_buffer;

	for (int i = 1; i <= NumDataBits; i++)
	{
		uchar_buffer = static_cast<unsigned char>(DataBits[i-1]);
		FullCommmand[i] = uchar_buffer;
	}

	Port->Write(FullCommmand, 0, NumDataBits);
}

void iRobotCreate2::SendStartCommand()
{
	SendCommand(CreatePort, OPCODE_START);
}

void iRobotCreate2::SendResetCommand()
{
	SendCommand(CreatePort, OPCODE_RESET);
}

void iRobotCreate2::SendStopCommand()
{
	SendCommand(CreatePort, OPCODE_STOP);
}

void iRobotCreate2::EnterSafeMode()
{
	SendCommand(CreatePort, OPCODE_SAFE_MODE);
}

void iRobotCreate2::EnterFullMode()
{
	SendCommand(CreatePort, OPCODE_FULL_MODE);
}

void iRobotCreate2::SendRadialDriveCommand(DriveDirection Direction, __int16 Distance, __int16 Velocity, __int16 Radius)
{
	array<Byte>^ arrVelocity = gcnew array<Byte>(2);
	array<Byte>^ arrRadius = gcnew array<Byte>(2);
	__int16 DataBits[4];

	switch (Direction)
	{
	case FORWARD_RIGHT:
		Radius = -Radius;
		break;
	case BACKWARD_LEFT:
		Velocity = -Velocity;
		break;
	case BACKWARD_RIGHT:
		Radius = -Radius;
		Velocity = -Velocity;
		break;
	}

	arrVelocity = iRobotCreate2::Int16ToTwosComplementByteArray(Velocity);
	arrRadius = iRobotCreate2::Int16ToTwosComplementByteArray(Radius);

	DataBits[0] = arrVelocity[0];
	DataBits[1] = arrVelocity[1];
	DataBits[2] = arrRadius[0];
	DataBits[3] = arrRadius[1];

	SendCommand(CreatePort, OPCODE_DRIVE, DataBits, 4);
}

array<Byte>^ iRobotCreate2::Int16ToTwosComplementByteArray(__int16 Velocity)
{
	unsigned char high;
	unsigned char low;
	__int16 Vel2sC = Velocity ^ 0xFFFF + 1;
	
	high = (Vel2sC & 0xFF00) >> 8;
	low = Vel2sC & 0x00FF;

	array<Byte>^ result = { high, low };
	return result;
}

//DEPRECATED//
/*
void Create2::Start()
{
	array<Byte>^ start = { 128 };
	mSerialPort->Write(start, 0, 1);
}

void Create2::Stop()
{
	array<Byte>^ stop = { 173 };
	mSerialPort->Write(stop, 0, 1);
}

void Create2::Reset()
{
	array<Byte>^ reset = { 7 };
	mSerialPort->Write(reset, 0, 1);
}


void Create2::FullMode()
{
	array<Byte>^ full = { 132 };
	mSerialPort->Write(full, 0, 1);
}

void Create2::SafeMode()
{
	array<Byte>^ full = { 131 };
	mSerialPort->Write(full, 0, 1);
}

void Create2::DriveForward()
{
	array<Byte>^ driveforward = { 145, 0, 100, 0, 100 };
	mSerialPort->Write(driveforward, 0, 5);
}

void Create2::DriveBackward()
{
	array<Byte>^ drivebackward = { 145, 255, 156, 255, 156 };
	mSerialPort->Write(drivebackward, 0, 5);
}

*/


/*
void Create2::br00tal()
{
	array<Byte>^ br00tal_0 = { 140, 0, 13, 39, 8, 39, 8, 39, 8, 51, 8, 57, 8, 58, 8, 57, 16, 53, 8, 57, 8, 56, 16, 52, 8, 56, 8, 55, 16 };
	mSerialPort->Write(br00tal_0, 0, 29);

	array<Byte>^ br00tal_1 = { 140, 1, 13, 39, 8, 39, 8, 39, 8, 56, 8, 62, 8, 63, 8, 62, 16, 58, 8, 62, 8, 61, 16, 57, 8, 61, 8, 60, 16 };
	mSerialPort->Write(br00tal_1, 0, 29);

	array<Byte>^ br00tal_2 = { 140, 2, 12, 39, 8, 39, 8, 39, 8, 39, 8, 39, 8, 39, 8, 39, 8, 39, 8, 39, 8, 39, 8, 39, 8, 39, 8 };
	mSerialPort->Write(br00tal_2, 0, 27);

	array<Byte>^ br00tal_3 = { 140, 3, 8, 39, 8, 41, 8, 43, 8, 48, 8, 52, 8, 51, 8, 47, 8, 46, 8 };
	mSerialPort->Write(br00tal_3, 0, 19);
}

void Create2::H34dbang()
{
	array<Byte>^ play0 = { 141, 0 };
	array<Byte>^ play1 = { 141, 1 };
	array<Byte>^ play2 = { 141, 2 };
	array<Byte>^ play3 = { 141, 3 };
	mSerialPort->Write(play0, 0, 2);
	Sleep(2020);
	mSerialPort->Write(play0, 0, 2);
	Sleep(2020);
	mSerialPort->Write(play1, 0, 2);
	Sleep(2020);
	mSerialPort->Write(play1, 0, 2);
	Sleep(2020);
	mSerialPort->Write(play2, 0, 2);
	Sleep(1520);
	mSerialPort->Write(play2, 0, 2);
	Sleep(1520);
	mSerialPort->Write(play3, 0, 2);
	Sleep(1020);
	mSerialPort->Write(play2, 0, 2);
	Sleep(1520);
	mSerialPort->Write(play2, 0, 2);
	Sleep(1520);
	mSerialPort->Write(play3, 0, 2);
	Sleep(1020);
	mSerialPort->Write(play2, 0, 2);
	Sleep(1520);
	mSerialPort->Write(play2, 0, 2);
	Sleep(1520);
	mSerialPort->Write(play3, 0, 2);
	Sleep(1020);
	mSerialPort->Write(play2, 0, 2);
	Sleep(1520);
	mSerialPort->Write(play2, 0, 2);
	Sleep(1520);
	mSerialPort->Write(play3, 0, 2);
	Sleep(1020);
}
*/