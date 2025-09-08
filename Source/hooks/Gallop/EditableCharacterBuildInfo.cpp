#include "EditableCharacterBuildInfo.h"

namespace Gallop::EditableCharacterBuildInfo
{
	void* ctor1_orig = nullptr;
	void ctor1_hook(Il2CppObject* _this, 
		int cardId, 
		int charaId, 
		int dressId, 
		ControllerType controllerType, 
		int zekken, 
		int mobId, 
		int backDancerColorId, 
		int headId, 
		bool isUseDressDataHeadModelSubId, 
		bool isEnableModelCache, 
		int chara_dress_color_set_id) {
		Logger::Debug(SECTION_NAME, L"EditableCharacterBuildInfo_ctor1 called origcharaid=%d, origdressid=%d, mobid=%d", charaId, dressId, mobId);
		
		/*cardId = 100702;
		charaId = 1007;
		dressId = 100701;*/

		Logger::Debug(SECTION_NAME, L"EditableCharacterBuildInfo_ctor called ccharaid=%d, cdressid=%d", charaId, dressId);
		return reinterpret_cast<decltype(ctor1_hook)*>(ctor1_orig)(_this, cardId, charaId, dressId, controllerType, zekken, mobId, backDancerColorId, headId, isUseDressDataHeadModelSubId, isEnableModelCache, chara_dress_color_set_id);
	}

	void Init() {
		auto ctor1_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"EditableCharacterBuildInfo", ".ctor", 11
		);
		//EnableHook(ctor1_addr, &ctor1_hook, &ctor1_orig, L"EditableCharacterBuildInfo_ctor1");
	}
}