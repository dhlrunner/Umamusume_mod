#include "MasterEventMotionData.h"
#include <xstring>
using namespace std;

namespace Gallop::MasterEventMotionData
{
	void* GetAnimCommand_orig = nullptr;
	Il2CppObject* GetAnimCommand_hook(Il2CppObject* _this, Il2CppString* commandName) {
		wstring orig = commandName->chars;
		Il2CppObject* ret = nullptr;
		if (Settings::Global->walkMotionAllUrara) {
			if (orig.starts_with(L"homewalk")) {
				if (orig.contains(L"_U")) {
					orig = L"homewalk03_U";
				}
				else if (orig.contains(L"_D")) {
					orig = L"homewalk03_D";
				}
				else {
					orig = L"homewalk03";
				}
				Logger::Info(SECTION_NAME, L"Replaced walk motion to urara");
			}

			ret = reinterpret_cast<decltype(GetAnimCommand_hook)*>
				(GetAnimCommand_orig)(_this, il2cpp_string_new_utf16(orig.data(), orig.length()));
		}
		else {
			ret = reinterpret_cast<decltype(GetAnimCommand_hook)*>
				(GetAnimCommand_orig)(_this, commandName);
		}
		return ret;
	}

	void Init()
	{
		Logger::Info(SECTION_NAME, L"Init");

		auto GetAnimCommand_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"MasterEventMotionData", "GetAnimCommand", 1
		);
		EnableHook(GetAnimCommand_addr, &GetAnimCommand_hook, &GetAnimCommand_orig, L"GetAnimCommand");

	}
}