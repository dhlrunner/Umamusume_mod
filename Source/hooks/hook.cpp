#include "hook.h"


bool InitHooks_DLLMain()
{
	if (MH_Initialize() != MH_OK) {
		Logger::Error(L"HOOK", L"Failed to initialize MinHook");
		return false;
	}
	
	//init settings
	Settings::Init();
	Settings::LoadSettings("umamusume.exe.local\\config.json");

	//Enable windows api hooks
	WinHook_init();
	
	

	
	
	return true;
}

void InitHooks_BeforeBoot()
{
	
}

void InitHooks_AfterIl2cppInit()
{
	//Imgui init
	ImGuiWindows::InitKiero();

	//init global
	Global::currSceneName = il2cpp_string_new16(L"");

	//il2cpp_dump();
	libnative::Init(GetActiveWindow());

	//Unity Init
	Unity::HookInit();

	//Cyan Init
	Cyan::Init();

	//Gallop Init
	Gallop::Init();

	//Cute Init
	Cute::Init();

	//Set the flag
	Global::Game_HookFinished = true;

	//thread start
	BackgroundWorker::Init();


}
