#include "ModelLoader.h"


namespace Gallop::ModelLoader
{
	void* CreateNormalModel_orig = nullptr;
	void* CreateNormalModel_hook(Il2CppObject* _this, Il2CppObject* charInfo) {
        CharacterBuildInfo* info =
            (CharacterBuildInfo*)((uint8_t*)charInfo + sizeof(Il2CppObject));
		Logger::Info(SECTION_NAME, L"CreateNormalModel");
		/*int charaId;
		il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_charaId"), &charaId);
		int mobId;
		il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_mobId"), &mobId);
		int dressId;
		il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_dressId"), &dressId);*/
		//Logger::Debug(SECTION_NAME, L"CharacterBuildInfo_ctor called origcharaid=%d, origdressid=%d, mobid=%d", charaId, dressId, mobId);

       /* printf("===== CreateNormalModel dump =====\n");
        printf("_cardId                     : %d\n", info->_cardId);
        printf("_charaId                    : %d\n", info->_charaId);
        printf("_mobId                      : %d\n", info->_mobId);
        printf("_audienceId                 : %d\n", info->_audienceId);
        printf("_headModelSubId             : %d\n", info->_headModelSubId);
        printf("_bodyModelSubId             : %d\n", info->_bodyModelSubId);
        printf("_motionBodyModelSubId       : %d\n", info->_motionBodyModelSubId);
        printf("_dressId                    : %d\n", info->_dressId);
        printf("_motionDressId              : %d\n", info->_motionDressId);
        printf("_controllerType             : %d\n", info->_controllerType);
        printf("_zekken                     : %d\n", info->_zekken);
        printf("_genderType                 : %d\n", info->_genderType);
        printf("_heightType                 : %d\n", info->_heightType);
        printf("_bodySize                   : %d\n", info->_bodySize);
        printf("_bustType                   : %d\n", info->_bustType);
        printf("_skinType                   : %d\n", info->_skinType);
        printf("_socksType                  : %d\n", info->_socksType);
        printf("_defaultPersonalityType     : %d\n", info->_defaultPersonalityType);
        printf("_raceGateInPersonalityType  : %d\n", info->_raceGateInPersonalityType);
        printf("_raceRunPersonalityType     : %d\n", info->_raceRunPersonalityType);
        printf("_raceOverRunPersonalityType : %d\n", info->_raceOverRunPersonalityType);
        printf("_raceRunningType            : %d\n", info->_raceRunningType);
        printf("_zekkenColor                : %d\n", info->_zekkenColor);
        printf("_zekkenFontColor            : %d\n", info->_zekkenFontColor);
        printf("_zekkenFontStyle            : %d\n", info->_zekkenFontStyle);
        printf("_frameColor                 : %d\n", info->_frameColor);
        printf("_popularity                 : %d\n", info->_popularity);
        printf("_npcType                    : %d\n", info->_npcType);
        printf("_backDancerColorId          : %d\n", info->_backDancerColorId);
        printf("_attachmentModelId          : %d\n", info->_attachmentModelId);
        printf("_miniMobTailId              : %d\n", info->_miniMobTailId);
        printf("_miniMobParentCharaId       : %d\n", info->_miniMobParentCharaId);
        printf("_overrideClothCategory      : %d\n", info->_overrideClothCategory);
        printf("_charaDressColorSetId       : %d\n", info->_charaDressColorSetId);
        printf("===========================================\n");*/


		return reinterpret_cast<decltype(CreateNormalModel_hook)*>(CreateNormalModel_orig)(_this, charInfo);

	}

	void* CreateModel_orig = nullptr;
	void* CreateModel_hook(Il2CppObject* charInfo) {
        CharacterBuildInfo* info =
            (CharacterBuildInfo*)((uint8_t*)charInfo + sizeof(Il2CppObject));

		Logger::Info(SECTION_NAME, L"CreateModel");
        printf("===== CreateModel dump =====\n");
        //wprintf(L"_name                      : %S\n", Utils::ConvertWstringToUTF8(info->_name->chars).c_str());
        printf("_cardId                     : %d\n", info->_cardId);
        printf("_charaId                    : %d\n", info->_charaId);
        printf("_mobId                      : %d\n", info->_mobId);
        printf("_audienceId                 : %d\n", info->_audienceId);
        printf("_headModelSubId             : %d\n", info->_headModelSubId);
        printf("_bodyModelSubId             : %d\n", info->_bodyModelSubId);
        printf("_motionBodyModelSubId       : %d\n", info->_motionBodyModelSubId);
        printf("_dressId                    : %d\n", info->_dressId);
        printf("_motionDressId              : %d\n", info->_motionDressId);
        printf("_controllerType             : %d\n", info->_controllerType);
        printf("_zekken                     : %d\n", info->_zekken);
        printf("_genderType                 : %d\n", info->_genderType);
        printf("_heightType                 : %d\n", info->_heightType);
        printf("_bodySize                   : %d\n", info->_bodySize);
        printf("_bustType                   : %d\n", info->_bustType);
        printf("_skinType                   : %d\n", info->_skinType);
        printf("_socksType                  : %d\n", info->_socksType);
        printf("_defaultPersonalityType     : %d\n", info->_defaultPersonalityType);
        printf("_raceGateInPersonalityType  : %d\n", info->_raceGateInPersonalityType);
        printf("_raceRunPersonalityType     : %d\n", info->_raceRunPersonalityType);
        printf("_raceOverRunPersonalityType : %d\n", info->_raceOverRunPersonalityType);
        printf("_raceRunningType            : %d\n", info->_raceRunningType);
        printf("_zekkenColor                : %d\n", info->_zekkenColor);
        printf("_zekkenFontColor            : %d\n", info->_zekkenFontColor);
        printf("_zekkenFontStyle            : %d\n", info->_zekkenFontStyle);
        printf("_frameColor                 : %d\n", info->_frameColor);
        printf("_popularity                 : %d\n", info->_popularity);
        printf("_npcType                    : %d\n", info->_npcType);
        printf("_backDancerColorId          : %d\n", info->_backDancerColorId);
        printf("_attachmentModelId          : %d\n", info->_attachmentModelId);
        printf("_miniMobTailId              : %d\n", info->_miniMobTailId);
        printf("_miniMobParentCharaId       : %d\n", info->_miniMobParentCharaId);
        printf("_overrideClothCategory      : %d\n", info->_overrideClothCategory);
        printf("_charaDressColorSetId       : %d\n", info->_charaDressColorSetId);
        printf("===========================================\n");
		//Logger::Debug(SECTION_NAME, L"CreateModel called origcharaid=%d, origdressid=%d, mobid=%d", charaId, dressId, mobId);

		return reinterpret_cast<decltype(CreateModel_hook)*>(CreateModel_orig)(charInfo);

	}
	void Init() 
	{
		Logger::Info(SECTION_NAME, L"Init");
		auto CreateNormalModel_addr = reinterpret_cast<void* (*)(Il2CppObject*, Il2CppObject*)>(
			il2cpp_symbols::get_method_pointer(
				"umamusume.dll", "Gallop",
				"ModelLoader", "CreateNormalModel", 1
			)
		);
		EnableHook(CreateNormalModel_addr, CreateNormalModel_hook, reinterpret_cast<void**>(&CreateNormalModel_orig), L"ModelLoader_CreateNormalModel");

		auto CreateModel_addr = reinterpret_cast<void* (*)(Il2CppObject*, Il2CppObject*)>(
			il2cpp_symbols::get_method_pointer(
				"umamusume.dll", "Gallop",
				"ModelLoader", "CreateModel", 1
			)
			);
		EnableHook(CreateModel_addr, CreateModel_hook, reinterpret_cast<void**>(&CreateModel_orig), L"ModelLoader_CreateModel");
	}
}