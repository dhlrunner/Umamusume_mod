#include "UnityEngine.EventSystems.h"

namespace UnityEngine::EventSystems
{
	void* ProcessMouseEvent_orig;
	void ProcessMouseEvent_hook(void* _this, int id) {

		bool isOpen = Global::imgui_settingwnd_open || Global::isShowingSeekbar;

		if (!isOpen)
			return reinterpret_cast<decltype(ProcessMouseEvent_hook)*>(ProcessMouseEvent_orig)(_this, id);
	}

	void Init() {
		Logger::Info(SECTION_NAME, L"Init");
		auto ProcessMouseEvent_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "UnityEngine.EventSystems",
			"GallopStandaloneInputModule", "ProcessMouseEvent", 1
		);
		EnableHook(ProcessMouseEvent_addr, &ProcessMouseEvent_hook, &ProcessMouseEvent_orig, L"ProcessMouseEvent");
	}
}