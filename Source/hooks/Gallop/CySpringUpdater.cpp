#include "CySpringUpdater.h"

namespace Gallop::Model::Component::CySpringUpdater
{
	void* set_SpringUpdateMode_orig = nullptr;
	void set_SpringUpdateMode_hook(Il2CppObject* _this, SpringUpdateMode value)
	{
		
		reinterpret_cast<decltype(set_SpringUpdateMode_hook)*>(set_SpringUpdateMode_orig)(_this, SpringUpdateMode::Mode60FPS);
	}

	void* get_SpringUpdateMode_orig = nullptr;
	int get_SpringUpdateMode_hook(Il2CppObject* _this)
	{
		set_SpringUpdateMode_hook(_this, SpringUpdateMode::Mode60FPS);
		return reinterpret_cast<decltype(get_SpringUpdateMode_hook)*>(get_SpringUpdateMode_orig)(_this);
	}

	void* Refresh_orig;
	void Refresh_hook(Il2CppObject* _this, Il2CppObject* context) 
	{
		Logger::Debug(SECTION_NAME, L"CySpring_Refresh called");
		

		return reinterpret_cast<decltype(Refresh_hook)*>(Refresh_orig)(_this, context);
	}

	void* BeginSimulation_orig;
	void BeginSimulation_hook(Il2CppObject* _this)
	{
		//Logger::Debug(SECTION_NAME, L"CySpring_BeginSimulation called");
		/*FieldInfo* Context_f = il2cpp_class_get_field_from_name(_this->klass, "_context");
		Il2CppObject* context;
		il2cpp_field_get_value(_this, Context_f, &context);*/
		FieldInfo* Cyspring_Field = il2cpp_class_get_field_from_name(_this->klass, "_cySpring");
		//printf("CySpring field=%p\n", Cyspring_Field);
		Il2CppObject* Cyspring;
		il2cpp_field_get_value(_this, Cyspring_Field, &Cyspring);
		FieldInfo* timescale_filed = il2cpp_class_get_field_from_name(Cyspring->klass, "_timescale");
		float _timescale = 0.8f;
		if (Settings::Global->autoFpsSet) 
		{

		}
		//il2cpp_field_get_value(Cyspring, timescale_filed, &_timescale);
		il2cpp_field_set_value(Cyspring, timescale_filed, &_timescale);
		//Logger::Debug(SECTION_NAME, L"CySpring timescale=%.2f", _timescale);
		return reinterpret_cast<decltype(BeginSimulation_hook)*>(BeginSimulation_orig)(_this);
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

		auto Refresh_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop.Model.Component",
			"CySpringUpdater", "Refresh", 1
		);
		EnableHook(Refresh_addr, &Refresh_hook, &Refresh_orig, L"CySpringUpdater_Refresh");

		auto BeginSimulation_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop.Model.Component",
			"CySpringUpdater", "BeginSimulation", 0
		);
		//EnableHook(BeginSimulation_addr, &BeginSimulation_hook, &BeginSimulation_orig, L"CySpringUpdater_BeginSimulation");
	}
}
