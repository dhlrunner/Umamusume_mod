#include "GameSystem.h"

namespace Gallop::GameSystem 
{
	void* ApplicationQuit_orig;
	void ApplicationQuit_hook() {
		Logger::Debug(SECTION_NAME, L"GameSystem.ApplicationQuit() hooked");
		Global::gameTerminating = true;
		return reinterpret_cast<decltype(ApplicationQuit_hook)*>
			(ApplicationQuit_orig)();
	}

	void* OnApplicationQuit_orig;
	void OnApplicationQuit_hook() {
		Logger::Debug(SECTION_NAME, L"GameSystem.OnApplicationQuit() hooked");
		Global::gameTerminating = true;
		return reinterpret_cast<decltype(OnApplicationQuit_hook)*>
			(OnApplicationQuit_orig)();
	}

	void Init()
	{
		Logger::Info(SECTION_NAME, L"Init");
		auto ApplicationQuit_addr = il2cpp_symbols::get_method_pointer(
				"umamusume.dll", "Gallop",
				"GameSystem", "ApplicationQuit", 0
		);
		EnableHook(ApplicationQuit_addr, &ApplicationQuit_hook, &ApplicationQuit_orig, L"ApplicationQuit");

		auto OnApplicationQuit_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"GameSystem", "OnApplicationQuit", 0
		);
		EnableHook(OnApplicationQuit_addr, &OnApplicationQuit_hook, &OnApplicationQuit_orig, L"OnApplicationQuit");
	}


}