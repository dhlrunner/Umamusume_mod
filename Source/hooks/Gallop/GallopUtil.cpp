#include "GallopUtil.h"

using namespace std;
namespace Gallop::GallopUtil
{
	void* GotoTitleOnError_orig = nullptr;
	void GotoTitleOnError_hook(Il2CppString* text) {
		Logger::Debug(SECTION_NAME, L"GallopUtil_GotoTitleOnError text=%s", text->chars);
		if (Settings::Global->gotoTitleOnError) {
			return reinterpret_cast<decltype(GotoTitleOnError_hook)*>
				(GotoTitleOnError_orig)(text);
		}
	}

	void* IsUseDressInMode_orig;
	bool IsUseDressInMode_hook(CharacterClothMode mode, Il2CppObject* elem)
	{
		bool ret = false;
		if (mode == CharacterClothMode::LiveTheater)
			ret = true;
		else
			ret = reinterpret_cast<decltype(IsUseDressInMode_hook)*>(IsUseDressInMode_orig)(mode, elem);

		Logger::Debug(SECTION_NAME, L"IsUseDressInMode mode=%d, ret=%d", mode,ret);
		return ret;
	}

	void Init() 
	{
		Logger::Info(SECTION_NAME, L"Init");
		auto GotoTitleOnError_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"GallopUtil", "GotoTitleOnError", 1
		);
		EnableHook(GotoTitleOnError_addr, &GotoTitleOnError_hook, &GotoTitleOnError_orig, L"GotoTitleOnError");

		auto IsUseDressInMode_addr = reinterpret_cast<bool(*)(CharacterClothMode, Il2CppObject*)>(
			il2cpp_symbols::get_method_pointer(
				"umamusume.dll", "Gallop",
				"GallopUtil", "IsUseDressInMode", 2
			));
		EnableHook(IsUseDressInMode_addr, &IsUseDressInMode_hook, &IsUseDressInMode_orig, L"GallopUtil_IsUseDressInMode");


	}
}