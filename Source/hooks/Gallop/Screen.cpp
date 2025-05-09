#include "Screen.h"

using namespace Unity;
namespace Gallop::Screen
{
	
	void* ChangeScreenOrientation_orig = nullptr;
	Il2CppObject* ChangeScreenOrientation_hook(ScreenOrientation targetOrientation, bool isForce) {
		Logger::Debug(SECTION_NAME, L"ChangeScreenOrientation Hook %d", targetOrientation);
		return reinterpret_cast<decltype(ChangeScreenOrientation_hook)*>(ChangeScreenOrientation_orig)(
			Settings::Global->forceLandscape ? ScreenOrientation::Landscape : targetOrientation, isForce);
	}

	void* ChangeScreenOrientationPortraitAsync_orig;
	il2cpp::IEnumerator* ChangeScreenOrientationPortraitAsync_hook()
	{
		printf("ChangeScreenOrientationPortraitAsync hooked\n");
		if (Settings::Global->forceLandscape) {
			auto ienum = new il2cpp::IEnumerator(reinterpret_cast<Il2CppObject* (*)()>(il2cpp_symbols::get_method_pointer(
				"umamusume.dll",
				"Gallop",
				"Screen", "ChangeScreenOrientationLandscapeAsync", -1))());

			
			
			UnityEngine::CoreModule::Screen_set_orientation_hook(ScreenOrientation::Landscape);
			ChangeScreenOrientation_hook(ScreenOrientation::Landscape, true);
			return ienum;
		}

		return reinterpret_cast<decltype(ChangeScreenOrientationPortraitAsync_hook)*>(ChangeScreenOrientationPortraitAsync_orig)();

	}

	void Init()
	{
		Logger::Info(SECTION_NAME, L"Init");
		auto ChangeScreenOrientation_addr = reinterpret_cast<void (*)(
			ScreenOrientation, bool)>(il2cpp_symbols::get_method_pointer(
				"umamusume.dll",
				"Gallop",
				"Screen", "ChangeScreenOrientation", 2));
		EnableHook(ChangeScreenOrientation_addr, ChangeScreenOrientation_hook, &ChangeScreenOrientation_orig, L"ChangeScreenOrientation");

		auto ChangeScreenOrientationPortraitAsync_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"Screen", "ChangeScreenOrientationPortraitAsync", 0
		);
		EnableHook(ChangeScreenOrientationPortraitAsync_addr, ChangeScreenOrientationPortraitAsync_hook, &ChangeScreenOrientationPortraitAsync_orig, L"ChangeScreenOrientationPortraitAsync");


		
		if (Settings::Global->forceLandscape) {
			il2cpp::IEnumerator ienum(reinterpret_cast<Il2CppObject * (*)()>(il2cpp_symbols::get_method_pointer(
				"umamusume.dll",
				"Gallop",
				"Screen", "ChangeScreenOrientationLandscapeAsync", -1))());
			ienum.MoveNext();
		}
	}
}