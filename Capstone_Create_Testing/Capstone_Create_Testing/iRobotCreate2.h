#pragma once
#define CREATE2_PORT_NUMBER 4
#define CREATE2_BAUD 115200
#define CREATE2_DATABITS 8
#define CREATE2_PARITY Parity::None
#define CREATE2_STOPBITS StopBits::One
#define CREATE2_FLOWCONTROL Handshake::None

#using <System.dll>
using namespace System;
using namespace System::IO::Ports;

enum DriveDirection
{
	FORWARD_LEFT = 0,
	FORWARD_RIGHT,
	BACKWARD_LEFT,
	BACKWARD_RIGHT,
	FORWARD,
	BACKWARD,
	STOP
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
	static array<Byte>^ Int16ToTwosComplementByteArray(__int16 Int16);
	
	
	ref class CreateCommand
	{
	private:
		array<Byte>^ Command;
		int CommandLength;
	public:
		void SendCommand(){
			CreatePort->Write(Command, 0, CommandLength);
		}
	
		void SetCommand(array<Byte>^ arr, int len){
			Command = arr;
			CommandLength = len;
		}
	};
	
	CreateCommand^ ProcessCommand(Opcode Cmd, __int16 DataBits[], __int8 NumDataBits);
	CreateCommand^ ProcessCommand(Opcode Cmd);
	CreateCommand^ ProcessRadialDriveCommand(DriveDirection Direction, __int16 Distance, __int16 Velocity, __int16 Radius);
	
	static void SendCommand_Direct(SerialPort^ Port, Opcode Cmd, __int16 DataBits[], __int8 NumDataBits);
	static void SendCommand_Direct(SerialPort^ Port, Opcode Cmd);
	static void SendStopCommand_Direct();
	/*
	void SendRadialDriveCommand(DriveDirection Direction, __int16 Distance, __int16 Velocity, __int16 Radius);
	void SendStartCommand();
	void SendResetCommand();
	void SendStopCommand();
	void SendSafeMode();
	void SendFullMode();
	*/

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