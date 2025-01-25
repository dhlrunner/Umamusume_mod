#include "CharacterBuildInfo.h"

namespace Gallop::CharacterBuildInfo_
{
	void* ctor_orig = nullptr;
	void ctor_hook(CharacterBuildInfo* _this,
		int charaId, int dressId, int controllerType, int headId = 0, int zekken = 0, int mobId = 0,
		int backDancerColorId = -1, bool isUseDressDataHeadModelSubId = true,
		int audienceId = 0, int motionDressId = -1, bool isEnableModelCache = true) {
		Logger::Debug(SECTION_NAME, L"CharacterBuildInfo_ctor called origcharaid=%d, origdressid=%d, mini=%d", charaId, dressId, _this->_miniMobParentCharaId);

		//if(_this.)
		if (Settings::Global->homeAllDiamond) {
			charaId = 1067;
			dressId = 106701;
			headId = 0;
		}
		else {
			if (Settings::Local->gachaCutinChara > -1) {
				/*if (charaId == 9001)
					charaId = 9002;*/
					//else
				_this->_charaId = Settings::Local->gachaCutinChara;
				charaId = Settings::Local->gachaCutinChara;
			}
			if (Settings::Local->gachaCutinDress > -1) {
				/*if (dressId == 900101)
					dressId = 900201;*/
					//else

				_this->_dressId = Settings::Local->gachaCutinDress;
				dressId = Settings::Local->gachaCutinDress;
			}
			if (Settings::Local->gachaCutinHeadid > -1) {
				_this->_headModelSubId = Settings::Local->gachaCutinHeadid;
				headId = Settings::Local->gachaCutinHeadid;
			}
		}
		//controllerType = 0x0c;

		Logger::Debug(SECTION_NAME, L"CharacterBuildInfo_ctor called ccharaid=%d, cdressid=%d", charaId, dressId);
		//charaId = 1070;
		//dressId = 2;
		return reinterpret_cast<decltype(ctor_hook)*>
			(ctor_orig)(_this, charaId, dressId, controllerType, headId,
				zekken, mobId, backDancerColorId, isUseDressDataHeadModelSubId, audienceId,
				motionDressId, isEnableModelCache);
	}

	void* ctor2_orig = nullptr;
	void ctor2_hook(CharacterBuildInfo* src) {
		Logger::Debug(SECTION_NAME, L"CharacterBuildInfo_ctor_overload1 called charaid=%d, dressid=%d", src->_charaId, src->_dressId);

		if (Settings::Local->gachaCutinChara > -1) {
			src->_charaId = Settings::Local->gachaCutinChara;
		}
		if (Settings::Local->gachaCutinDress > -1) {
			src->_dressId = Settings::Local->gachaCutinDress;
		}
		if (Settings::Local->gachaCutinHeadid > -1) {
			src->_headModelSubId = Settings::Local->gachaCutinHeadid;
		}
		Logger::Debug(SECTION_NAME, L"CharacterBuildInfo_ctor_overload1 called ccharaid=%d, cdressid=%d", src->_charaId, src->_dressId);
		return reinterpret_cast<decltype(ctor2_hook)*>
			(ctor2_orig)(src);
	}

	void* ctor3_orig = nullptr;
	void ctor3_hook(void* _instance,
		int cardId, int charaId, int dressId, int controllerType, int headId = 0, int zekken = 0, int mobId = 0, int backDancerColorId = -1,
		int overrideClothCategory = 0xFFFFFFFF, bool isUseDressDataHeadModelSubId = true,
		int audienceId = 0, int motionDressId = -1, bool isEnableModelCache = true, int charaDressColorSetId = 0) {
		Logger::Debug(SECTION_NAME, L"CharacterBuildInfo_ctor2 called origcharaid=%d, origdressid=%d", charaId, dressId);

		if (Settings::Local->gachaCutinChara > -1) {
			charaId = Settings::Local->gachaCutinChara;
		}
		if (Settings::Local->gachaCutinDress > -1) {
			dressId = Settings::Local->gachaCutinDress;
		}
		if (Settings::Local->gachaCutinHeadid > -1) {
			headId = Settings::Local->gachaCutinHeadid;
		}

		Logger::Debug(SECTION_NAME, L"CharacterBuildInfo_ctor2 called ccharaid=%d, cdressid=%d", charaId, dressId);
		return reinterpret_cast<decltype(ctor3_hook)*>
			(ctor3_orig)(_instance, cardId, charaId, dressId, controllerType,
				headId, zekken, mobId, backDancerColorId, overrideClothCategory,
				isUseDressDataHeadModelSubId, audienceId, motionDressId, isEnableModelCache, charaDressColorSetId);

	}
	
	void Init() 
	{
		Logger::Info(SECTION_NAME, L"Init");

		auto ctor_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"CharacterBuildInfo", ".ctor", 9 + 2
		);
		EnableHook(ctor_addr, &ctor_hook, &ctor_orig, L"CharacterBuildInfo_ctor");

		auto ctor2_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"CharacterBuildInfo", ".ctor", 0
		);
		EnableHook(ctor2_addr, &ctor2_hook, &ctor2_orig, L"CharacterBuildInfo_ctor2");

		auto ctor3_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"CharacterBuildInfo", ".ctor", 11 + 2 + 1
		);
		EnableHook(ctor3_addr, &ctor3_hook, &ctor3_orig, L"CharacterBuildInfo_ctor3");

	}
}