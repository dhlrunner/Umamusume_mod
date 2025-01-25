#include "GallopUtil.h"

using namespace std;
namespace Gallop::GallopUtil
{
	void* GotoTitleOnError_orig = nullptr;
	void GotoTitleOnError_hook(Il2CppString* text) {
		Logger::Debug(SECTION_NAME, L"GallopUtil_GotoTitleOnError text=%s", wstring(text->chars).c_str());
		if (Settings::Global->gotoTitleOnError) {
			return reinterpret_cast<decltype(GotoTitleOnError_hook)*>
				(GotoTitleOnError_orig)(text);
		}
	}

	void Init() 
	{
		Logger::Info(SECTION_NAME, L"Init");
		auto GotoTitleOnError_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"GallopUtil", "GotoTitleOnError", 1
		);
		EnableHook(GotoTitleOnError_addr, &GotoTitleOnError_hook, &GotoTitleOnError_orig, L"GotoTitleOnError");
	}
}