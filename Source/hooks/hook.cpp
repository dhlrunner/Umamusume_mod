#include "hook.h"


DWORD WINAPI InitHooks_DLLMain(void*)
{
	if (MH_Initialize() != MH_OK) {
		Logger::Error(L"HOOK", L"Failed to initialize MinHook");
		return false;
	}
	
	//init settings
	Settings::Init();

	switch (Global::gameType) {
	case Global::GameType::UMAMUSUME_DMM_JP:
		Settings::LoadSettings("umamusume.exe.local\\config.json");
		break;
	case Global::GameType::UMAMUSUME_STEAM_JP:
		Settings::LoadSettings("UmamusumePrettyDerby_Jpn.exe.local\\config.json");
		break;
	}


	//Enable windows api hooks
	WinHook_init();
	
	return true;
}

void InitHooks_BeforeBoot()
{
	//LibNative.Runtume Init
	LibNative::Runtime::Init();

	//Unity Init
	Unity::HookInit();
}

void InitHooks_AfterIl2cppInit()
{
	//Imgui init
	ImGuiWindows::InitKiero();

	//init global
	Global::currSceneName = il2cpp_string_new16(L"_Boot");

	//il2cpp_dump();
	libnative::Init(GetActiveWindow());

	

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
