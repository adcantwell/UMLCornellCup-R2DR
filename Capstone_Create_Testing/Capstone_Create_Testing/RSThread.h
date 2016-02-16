#pragma once
#include "iRobotCreate2.h"
#include "ThreadWrapper.h"

public ref class RSThread : public ThreadWrapper
{
public:
	// constructor
	RSThread();
	// call this function to start thread
	void Start() override;
	// thread entry point
	void Entry() override;
};