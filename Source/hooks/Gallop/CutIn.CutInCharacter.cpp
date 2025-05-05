#include "CutIn.CutInCharacter.h"

namespace Gallop::CutIn::CutInCharacter
{
	void* CreateModel_orig = nullptr;
	bool CreateModel_hook(Il2CppObject* _this, Il2CppObject* info, ControllerType controllerType) {
		Logger::Info(SECTION_NAME, L"CreateModel");
		FieldInfo* _charaIdField = il2cpp_class_get_field_from_name(info->klass, "_charaId");
		FieldInfo* _clothIdField = il2cpp_class_get_field_from_name(info->klass, "_clothId");
		FieldInfo* _headIdField = il2cpp_class_get_field_from_name(info->klass, "_headId");

		int charaId = 1007;
		il2cpp_field_set_value(info, _charaIdField, &charaId);
		int clothId = 100701;
		il2cpp_field_set_value(info, _clothIdField, &clothId);
		int headId = 0;
		il2cpp_field_set_value(info, _headIdField, &headId);

		return reinterpret_cast<decltype(CreateModel_hook)*>(CreateModel_orig)(_this, info, controllerType);
	}

	void* EntryModel_orig = nullptr;
	bool EntryModel_hook(Il2CppObject* _this, Il2CppObject* model, int type, Il2CppObject* info) {
		
		return reinterpret_cast<decltype(EntryModel_hook)*>(EntryModel_orig)(_this, model, type, info);
	}

	void* SetupModelComponent_orig = nullptr;
	bool SetupModelComponent_hook(Il2CppObject* _this, Il2CppObject* model) {
		Logger::Info(SECTION_NAME, L"SetupModelComponent");
		FieldInfo* _charaIdField = il2cpp_class_get_field_from_name(model->klass, "_charaId");
		FieldInfo* _clothIdField = il2cpp_class_get_field_from_name(model->klass, "_clothId");
		FieldInfo* _headIdField = il2cpp_class_get_field_from_name(model->klass, "_headId");
		int charaId = 1007;
		il2cpp_field_set_value(model, _charaIdField, &charaId);
		int clothId = 100701;
		il2cpp_field_set_value(model, _clothIdField, &clothId);
		int headId = 0;
		il2cpp_field_set_value(model, _headIdField, &headId);
		return reinterpret_cast<decltype(SetupModelComponent_hook)*>(SetupModelComponent_orig)(_this, model);
	}
	void Init() {
		Logger::Info(SECTION_NAME, L"Init");
		auto CreateModel_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop.CutIn",
			"CutInCharacter", "CreateModel", 2
		);
		EnableHook(CreateModel_addr, CreateModel_hook, reinterpret_cast<void**>(&CreateModel_orig), L"CutIn.CutInCharacter_CreateModel");

		auto EntryModel_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop.CutIn",
			"CutInCharacter", "EntryModel", 3
		);
		EnableHook(EntryModel_addr, EntryModel_hook, reinterpret_cast<void**>(&EntryModel_orig), L"CutIn.CutInCharacter_EntryModel");
	}
}