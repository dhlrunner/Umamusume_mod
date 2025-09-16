#include "GallopDialogUtil.h"

namespace GallopDialog
{
	/// <summary>
	/// 기본 버튼없는 다이얼로그 생성
	/// </summary>
	/// <param name="title">제목</param>
	/// <param name="text">내용</param>
	/// <param name="canClose">바깥쪽 터치로 닫을수 있는지 여부</param>
	/// <returns></returns>
	Il2CppObject* ShowTextDialog(std::wstring title, std::wstring text, bool canClose)
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
		return il2cpp_symbols::get_method_pointer<Il2CppObject * (*)(Il2CppObject * data, bool isEnableOutsideClick)>
			("umamusume.dll", "Gallop", "DialogManager", "PushSystemDialog", 2)(dialogData, canClose);

	}

	/// <summary>
	/// 다이얼로그 메인 텍스트 갱신 (주의: 너무 빠르면 에러남)
	/// </summary>
	/// <param name="targetDialogObj">타겟 다이얼로그 오브젝트</param>
	/// <param name="text">갱신 텍스트</param>
	void SetDialogMessage(Il2CppObject* targetDialogObj, std::wstring text)
	{
		Il2CppString* textStr = il2cpp_string_new16(text.data());
		auto get_CurrentDialogObj = reinterpret_cast<Il2CppObject * (*)(Il2CppObject * _this)>(il2cpp_symbols::get_method_pointer("umamusume.dll", "Gallop", "DialogCommon", "get_CurrentDialogObj", 0));
		auto dialogObj = get_CurrentDialogObj(targetDialogObj);
		auto get_TextCommon = reinterpret_cast<Il2CppObject * (*)(Il2CppObject * _this)>(il2cpp_symbols::get_method_pointer("umamusume.dll", "Gallop", "DialogObject", "get_Text", 0));
		auto txtCommon = get_TextCommon(dialogObj);
		auto setTextCommon = reinterpret_cast<Il2CppObject * (*)(Il2CppObject * _this, Il2CppString* text)>(il2cpp_symbols::get_method_pointer("umamusume.dll", "Gallop", "TextCommon", "set_text", 1));
		if(setTextCommon && txtCommon && textStr)
			setTextCommon(txtCommon, textStr);

	}

	/// <summary>
	/// 다이얼로그 닫기
	/// </summary>
	/// <param name="targetDialogObj">타겟 다이얼로그 오브젝트</param>
	void CloseDialog(Il2CppObject* targetDialogObj) 
	{
		il2cpp_class_get_method_from_name_type<void(*)(Il2CppObject*)>(targetDialogObj->klass, "Close",0)->methodPointer(targetDialogObj);
		
		/*auto close = reinterpret_cast<void(*)(Il2CppObject*,bool)>(il2cpp_symbols::get_method_pointer("umamusume.dll", "Gallop", "DialogManager", "DispClose", 2));
		close(targetDialogObj, false);
		auto distroy = reinterpret_cast<void(*)(Il2CppDelegate*, bool)>(il2cpp_symbols::get_method_pointer("umamusume.dll", "Gallop", "DialogManager", "RemoveAllDialog", 2));
		distroy(nullptr, true);*/
	}

	/// <summary>
	/// 화면 중간에 뜨는 토스트 메세지
	/// </summary>
	/// <param name="text">텍스트</param>
	void ShowToast(std::wstring text)
	{
		Il2CppString* textStr = il2cpp_string_new16(text.data());
		auto UIManager = il2cpp::GetSingletonInstance(il2cpp_symbols::get_class("umamusume.dll", "Gallop", "UIManager"));
		//printf("UIManager ptr=%p\n", UIManager->klass);
		//il2cpp_class_get_method_from_name_type<void (*)(Il2CppObject*, Il2CppString*)>(UIManager->klass, "get_UserData", 0)->methodPointer(UIManager, textStr);

		//il2cpp_runtime_object_init(dialogData);
		//printf("dialogData pointer: %p\n", dialogData);
		auto show = reinterpret_cast<void(*)(Il2CppObject*, Il2CppString*, Unity::CameraType__Enum)>(il2cpp_symbols::get_method_pointer("umamusume.dll", "Gallop", "UIManager", "ShowNotification", 2));
		//printf("show pointer: %p\n", show);
		Unity::CameraType__Enum camType = Unity::CameraType__Enum::Game;

		show(UIManager, textStr, Unity::CameraType__Enum::Game);
	}
}