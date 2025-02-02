#include "CySpringUpdater.h"

namespace Gallop::Model::Component::CySpringUpdater
{
	void* set_SpringUpdateMode_orig = nullptr;
	void set_SpringUpdateMode_hook(Il2CppObject* _this, int value)
	{
		
		reinterpret_cast<decltype(set_SpringUpdateMode_hook)*>(set_SpringUpdateMode_orig)(_this, 1);
	}

	void* get_SpringUpdateMode_orig = nullptr;
	int get_SpringUpdateMode_hook(Il2CppObject* _this)
	{
		set_SpringUpdateMode_hook(_this, 1);
		return reinterpret_cast<decltype(get_SpringUpdateMode_hook)*>(get_SpringUpdateMode_orig)(_this);
	}

	void Init() 
	{
		auto set_SpringUpdateMode_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop.Model.Component",
			"CySpringUpdater", "set_SpringUpdateMode", 1
		);
		EnableHook(set_SpringUpdateMode_addr, &set_SpringUpdateMode_hook, &set_SpringUpdateMode_orig, L"CySpringUpdater_set_SpringUpdateMode");
	
		auto get_SpringUpdateMode_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop.Model.Component",
			"CySpringUpdater", "get_SpringUpdateMode", 0
		);
		EnableHook(get_SpringUpdateMode_addr, &get_SpringUpdateMode_hook, &get_SpringUpdateMode_orig, L"CySpringUpdater_get_SpringUpdateMode");


	}
}
