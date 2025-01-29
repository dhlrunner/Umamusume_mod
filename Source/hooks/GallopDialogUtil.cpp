#include "GallopDialogUtil.h"

using namespace std;

namespace GallopDialog
{
	Il2CppObject* GetSingletonInstance(Il2CppClass* klass)
	{
		if (!klass || !klass->parent)
		{
			return nullptr;
		}
		auto instanceField = il2cpp_class_get_field_from_name(klass, "_instance");
		if (!instanceField)
		{
			instanceField = il2cpp_class_get_field_from_name(klass, "instance");
			if (!instanceField)
			{
				return nullptr;
			}
		}
		Il2CppObject* instance;
		il2cpp_field_static_get_value(instanceField, &instance);
		return instance;
	}

	void ShowTextDialog(wstring title, wstring text)
	{
		Il2CppString* titleStr = il2cpp_string_new16(title.data());
		Il2CppString* textStr = il2cpp_string_new16(text.data());

		auto dialogData = il2cpp_object_new(il2cpp_symbols::get_class("umamusume.dll", "Gallop", "DialogCommon/Data"));
		il2cpp_runtime_object_init(dialogData);
		dialogData =
			il2cpp_class_get_method_from_name_type<Il2CppObject *(*)(
				Il2CppObject * _this,
				Il2CppString * headerTextArg,
				Il2CppString * message)>(dialogData->klass, "SetSimpleNoButtonMessage", 2)->methodPointer(dialogData, titleStr, textStr);
		auto errorDialog = il2cpp_symbols::get_method_pointer<Il2CppObject * (*)(Il2CppObject * data, bool isEnableOutsideClick)>
			("umamusume.dll", "Gallop", "DialogManager", "PushSystemDialog", 2)(dialogData, true);

	}

	void ShowToast(wstring text)
	{
		Il2CppString* textStr = il2cpp_string_new16(text.data());
		auto UIManager = GetSingletonInstance(il2cpp_symbols::get_class("umamusume.dll", "Gallop", "UIManager"));
		//printf("UIManager ptr=%p\n", UIManager->klass);
		//il2cpp_class_get_method_from_name_type<void (*)(Il2CppObject*, Il2CppString*)>(UIManager->klass, "get_UserData", 0)->methodPointer(UIManager, textStr);

		//il2cpp_runtime_object_init(dialogData);
		//printf("dialogData pointer: %p\n", dialogData);
		auto show = reinterpret_cast<void(*)(Il2CppObject*, Il2CppString*)>(il2cpp_symbols::get_method_pointer("umamusume.dll", "Gallop", "UIManager", "ShowNotification", 1));
		//printf("show pointer: %p\n", show);
		show(UIManager, textStr);
	}
}