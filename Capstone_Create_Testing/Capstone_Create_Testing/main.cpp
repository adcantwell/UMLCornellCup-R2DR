#include "SerialPortWrapper.h"
#include "Server.h"
#include "iRobotCreate2.h"

int main()
{
	//FOR TESTING//
	/*
	StringComparer^ strcmp = StringComparer::OrdinalIgnoreCase;
	
	String^ strCommand;
	bool Continue = true;
	__int16 input;

	while (Continue)
	{
		strCommand = Console::ReadLine();

		if (strcmp->Equals("quit", strCommand))
		{
			Continue = false;
		}
		else
		{
			input = Convert::ToInt16(strCommand);
			array<Byte>^ result = iRobotCreate2::Int16ToTwosComplementByteArray(input);
			Console::WriteLine("High = {0}, Low = {1}", result[0], result[1]);
		}
	}
	*/

	//IN PROGRESS//
	
	Server NUC;

	String^ strCommand;
	StringComparer^ strcmp = StringComparer::OrdinalIgnoreCase;
	bool Continue = true;

	if (NUC.Init())
	{
		NUC.Create2.SendStartCommand();
		NUC.Create2.EnterSafeMode();

		while (Continue)
		{
			strCommand = Console::ReadLine();
			if (strcmp->Equals("quit", strCommand))
			{
				Continue = false;
			}
			if (strcmp->Equals("forward_l", strCommand))
			{
				NUC.Create2.SendRadialDriveCommand(FORWARD_LEFT, 0, 100, 100);
			}
			if (strcmp->Equals("back_l", strCommand))
			{
				NUC.Create2.SendRadialDriveCommand(BACKWARD_LEFT, 0, 100, 100);
			}
			if (strcmp->Equals("forward_r", strCommand))
			{
				NUC.Create2.SendRadialDriveCommand(FORWARD_RIGHT, 0, 100, 100);
			}
			if (strcmp->Equals("back_r", strCommand))
			{
				NUC.Create2.SendRadialDriveCommand(BACKWARD_RIGHT, 0, 100, 100);
			}
			if (strcmp->Equals("safe", strCommand))
			{
				NUC.Create2.EnterSafeMode();
			}
			if (strcmp->Equals("stop", strCommand))
			{
				NUC.Create2.SendStopCommand();
			}
			if (strcmp->Equals("reset", strCommand))
			{
				NUC.Create2.SendResetCommand();
			}
		}



		NUC.Cleanup();
	}
	else
	{
		NUC.Cleanup();
		Console::WriteLine("Server initialization failed.");
	}
	
	

	//DEPRECATED//
	/*
	if ( TestPort.Open(4) )
	{
		TestPort.mContinue = true;

		Console::WriteLine("Type QUIT to exit");

		while (TestPort.mContinue)
		{
			strCommand = Console::ReadLine();

			if (strcmp->Equals("quit", strCommand))
			{
				TestPort.mContinue = false;
			}
			else if (strcmp->Equals("forward", strCommand))
			{
				TestPort.DriveForward();
			}
			else if (strcmp->Equals("backward", strCommand))
			{
				TestPort.DriveBackward();
			}
			else if (strcmp->Equals("stop", strCommand))
			{
				TestPort.Stop();
			}
			else if (strcmp->Equals("start", strCommand))
			{
				TestPort.Start();
				TestPort.SafeMode();
			}
			else if (strcmp->Equals("br00tal", strCommand))
			{
				TestPort.br00tal();
			}
			else if (strcmp->Equals("h34dbang", strCommand))
			{
				TestPort.H34dbang();
			}
		}
	}
	*/
}