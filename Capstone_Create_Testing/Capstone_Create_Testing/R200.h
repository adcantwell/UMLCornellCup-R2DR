#pragma once
#include <pxcsensemanager.h>
#include <pxcpersontrackingmodule.h>
#include <pxcpersontrackingdata.h>
#include <pxcpersontrackingconfiguration.h>

public ref class R200
{
public:
	static PXCSenseManager* SenseManager;
	static PXCPersonTrackingModule* PTModule;
	static PXCPersonTrackingConfiguration* PTConfig;

	static bool Init();
	static void Cleanup();
};