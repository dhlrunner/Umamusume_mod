#include "SingleModeStartResultCharaViewer.h"

namespace Gallop::SingleModeStartResultCharaViewer 
{
	void* SetupImageEffect_orig;
	void SetupImageEffect_hook(void* _this) {
		Logger::Info(SECTION_NAME, L"SingleModeStart_SetupImageEffect");
		Global::settingUpImageEffect = true;
		reinterpret_cast<decltype(SetupImageEffect_hook)*>(SetupImageEffect_orig)(_this);
		Global::settingUpImageEffect = false;
	}

	void Init()
	{
		Logger::Info(SECTION_NAME, L"Init");
		auto SetupImageEffect_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"SingleModeStartResultCharaViewer", "SetupImageEffect", 0
		);
		EnableHook(SetupImageEffect_addr, &SetupImageEffect_hook, &SetupImageEffect_orig, L"SingleModeStartResultCharaViewer_SetupImageEffect");
	}
}