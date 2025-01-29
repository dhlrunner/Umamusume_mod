#include "RaceUIFinishOrderFlash.h"

namespace Gallop::RaceUIFinishOrderFlash
{
	void* Play_orig = nullptr;
	void Play_hook(Il2CppObject* _instance, int finishOrder, void* param2) {
		
		if (Global::showFinishOrderFlash) {
			Logger::Info(SECTION_NAME, L"RaceUIFinishOrderFlash_Play finishOrder=%d\n", finishOrder);
			return reinterpret_cast<decltype(Play_hook)*>(Play_orig)(_instance, finishOrder, param2);
		}
		else {
			Logger::Info(SECTION_NAME, L"RaceUIFinishOrderFlash_Play ignored\n");
		}

	}
	
	void Init()
	{
		Logger::Info(SECTION_NAME, L"Init");
		auto Play_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"RaceUIFinishOrderFlash", "Play", 2
		);
		EnableHook(Play_addr, &Play_hook, &Play_orig, L"RaceUIFinishOrderFlash_Play");

	}
}