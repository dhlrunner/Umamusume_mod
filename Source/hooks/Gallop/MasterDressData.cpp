#include "MasterDressData.h"

namespace Gallop::MasterDressData_
{
	void* Get_orig = nullptr;
	Il2CppObject* Get_hook(Il2CppObject* _this, int id) {
		Il2CppObject* ret = reinterpret_cast<decltype(Get_hook)*>(Get_orig)(_this, id);
		int enable = 1;
		il2cpp_field_set_value(ret, il2cpp_class_get_field_from_name(ret->klass, "UseLive"), &enable);
		il2cpp_field_set_value(ret, il2cpp_class_get_field_from_name(ret->klass, "UseLiveTheater"), &enable);
		//Logger::Info(SECTION_NAME, L"Force enabled dress for live");	
		return ret;
	}

	void Init() 
	{
		Logger::Info(SECTION_NAME, L"Init");
		auto Get_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"MasterDressData", "Get", 1
		);
		EnableHook(Get_addr, &Get_hook, &Get_orig, L"MasterDressData_Get");
	}
}