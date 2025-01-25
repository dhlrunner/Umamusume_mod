#include "Unityengine.CoreModule.h"

using namespace Unity;
namespace UnityEngine::CoreModule
{
	void* Screen_set_orientation_orig = nullptr;
	void Screen_set_orientation_hook(ScreenOrientation orientation) {
		printf("SetScreenOrientation Hook %d\n", orientation);
		if ((orientation == ScreenOrientation::Portrait ||
			orientation == ScreenOrientation::PortraitUpsideDown) && Settings::Global->forceLandscape) {
			orientation = ScreenOrientation::Landscape;
		}
		reinterpret_cast<decltype(Screen_set_orientation_hook)*>(Screen_set_orientation_orig)(
			orientation);
	}

	void Init() 
	{
		Logger::Info(SECTION_NAME, L"Init");

		auto Screen_set_orientation_addr = reinterpret_cast<void (*)(
			ScreenOrientation)>(il2cpp_symbols::get_method_pointer(
				"UnityEngine.CoreModule.dll",
				"UnityEngine",
				"Screen", "set_orientation", 1));
		EnableHook(Screen_set_orientation_addr, &Screen_set_orientation_hook, &Screen_set_orientation_orig, L"Screen_set_orientation");
	}
}