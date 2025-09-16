#include "MasterLiveData.h"

namespace Gallop::MasterLiveData
{
	void* Get_orig = nullptr;
	Il2CppObject* Get_hook(Il2CppObject* _this, int id) {
		Il2CppObject* ret = reinterpret_cast<decltype(Get_hook)*>(Get_orig)(_this, id);

		for (size_t i = 0; i < Settings::Global->forceEnabledLiveIDs.size(); i++) {
			if (id == Settings::Global->forceEnabledLiveIDs[i]) {
				bool enable = true;
				il2cpp_field_set_value(ret, il2cpp_class_get_field_from_name(ret->klass, "HasLive"), &enable);
				Logger::Info(SECTION_NAME, L"Force enabled hidden live %d", id);
			}
		}
		//if (id == 1052 || id == 1080 || id == 9051 || id == 1091 || id == 1152 || id == 1153 || id == 1174) {
		//	
		//	//MessageBoxW(NULL, L"Hidden live enabled by mod", L"Info", MB_OK);
		//}
		return ret;
	}


	void Init()
	{
		Logger::Info(SECTION_NAME, L"Init");
		auto Get_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"MasterLiveData", "Get", 1
		);
		EnableHook(Get_addr, &Get_hook, &Get_orig, L"MasterLiveData_Get");
		
	}
}