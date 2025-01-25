#include "Screen.h"

using namespace Unity;
namespace Gallop::Screen
{
	
	void* ChangeScreenOrientation_orig = nullptr;
	Il2CppObject* ChangeScreenOrientation_hook(ScreenOrientation targetOrientation, bool isForce) {
		Logger::Debug(SECTION_NAME, L"ChangeScreenOrientation Hook %d\n", targetOrientation);
		return reinterpret_cast<decltype(ChangeScreenOrientation_hook)*>(ChangeScreenOrientation_orig)(
			Settings::Global->forceLandscape ? ScreenOrientation::Landscape : targetOrientation, isForce);
	}

	void Init()
	{
		Logger::Info(SECTION_NAME, L"Init");
		auto ChangeScreenOrientation_addr = reinterpret_cast<void (*)(
			ScreenOrientation, bool)>(il2cpp_symbols::get_method_pointer(
				"umamusume.dll",
				"Gallop",
				"Screen", "ChangeScreenOrientation", 2));
		EnableHook(ChangeScreenOrientation_addr, &ChangeScreenOrientation_hook, &ChangeScreenOrientation_orig, L"ChangeScreenOrientation");

	}
}