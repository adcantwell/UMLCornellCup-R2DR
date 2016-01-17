#pragma once
#define CREATE_PORT_NUMBER 4
#define CREATE2_BAUD 115200
#define CREATE2_DATABITS 8
#define CREATE2_PARITY Parity::None
#define CREATE2_STOPBITS StopBits::One
#define CREATE2_FLOWCONTROL Handshake::None


#include <math.h>
#include <bitset>
#using <System.dll>
using namespace System;
using namespace System::IO::Ports;

enum DriveDirection
{
	FORWARD_LEFT = 0,
	FORWARD_RIGHT,
	BACKWARD_LEFT,
	BACKWARD_RIGHT
};

enum Opcode
{
	OPCODE_RESET = 7,
	OPCODE_START = 128,
	OPCODE_BAUD,
	OPCODE_SAFE_MODE = 131,
	OPCODE_FULL_MODE,
	OPCODE_POWER_OFF,
	OPCODE_SPOT_CLEAN,
	OPCODE_CLEAN,
	OPCODE_MAX_CLEAN,
	OPCODE_DRIVE,
	OPCODE_MOTORS,
	OPCODE_LEDS,
	OPCODE_SONG,
	OPCODE_PLAY,
	OPCODE_QUERY,
	OPCODE_FORCE_SEEKING_DOCK,
	OPCODE_PWM_MOTORS,
	OPCODE_DRIVE_PWM,
	OPCODE_STREAM = 148,
	OPCODE_QUERYLIST,
	OPCODE_DO_STREAM,
	OPCODE_SCHEDULING_LEDS = 162,
	OPCODE_DIGIT_LEDS_RAW,
	OPCODE_DIGIT_LEDS_ASCII,
	OPCODE_BUTTONS,
	OPCODE_SCHEDULE = 167,
	OPCODE_SET_DAY_TIME,
	OPCODE_STOP = 173
};

public ref class iRobotCreate2
{
public:
	static SerialPort^ CreatePort;

	void SendCommand(SerialPort^ Port, Opcode Cmd, __int16 DataBits[], __int8 NumDataBits);
	void SendCommand(SerialPort^ Port, Opcode Cmd);
	void SendRadialDriveCommand(DriveDirection Direction, __int16 Distance, __int16 Velocity, __int16 Radius);
	void SendStartCommand();
	void SendResetCommand();
	void SendStopCommand();
	void EnterSafeMode();
	void EnterFullMode();

	static array<Byte>^ Int16ToTwosComplementByteArray(__int16 Velocity);

	/*
	void Start();
	void Stop();
	void Reset();
	void DriveForward();
	void DriveBackward();
	void FullMode();
	void SafeMode();

	void br00tal();
	void H34dbang();
	*/
};