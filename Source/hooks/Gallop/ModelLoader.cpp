#include "ModelLoader.h"


namespace Gallop::ModelLoader
{
	void* CreateNormalModel_orig = nullptr;
	void* CreateNormalModel_hook(Il2CppObject* _this, Il2CppObject* charInfo) {
		Logger::Info(SECTION_NAME, L"CreateNormalModel");
		int charaId;
		il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_charaId"), &charaId);
		int mobId;
		il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_mobId"), &mobId);
		int dressId;
		il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_dressId"), &dressId);
		Logger::Debug(SECTION_NAME, L"CharacterBuildInfo_ctor called origcharaid=%d, origdressid=%d, mobid=%d", charaId, dressId, mobId);

		return reinterpret_cast<decltype(CreateNormalModel_hook)*>(CreateNormalModel_orig)(_this, charInfo);

	}

	void* CreateModel_orig = nullptr;
	void* CreateModel_hook(Il2CppObject* charInfo) {
		Logger::Info(SECTION_NAME, L"CreateModel");
        int audienceId;
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_audienceId"), &audienceId);
        wprintf(L"_audienceId: %d\n", audienceId);

        // AudienceBuildInfo _audienceInfo; // 복잡한 객체이므로 일단 생략

        int backDancerColorId;
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_backDancerColorId"), &backDancerColorId);
        wprintf(L"_backDancerColorId: %d\n", backDancerColorId);

        int bodyModelSubId;
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_bodyModelSubId"), &bodyModelSubId);
        wprintf(L"_bodyModelSubId: %d\n", bodyModelSubId);

        int bodySize; // ModelLoader.BodySize (Enum -> int)
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_bodySize"), &bodySize);
        wprintf(L"_bodySize: %d\n", bodySize);

        int bustType; // ModelLoader.BustType (Enum -> int)
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_bustType"), &bustType);
        wprintf(L"_bustType: %d\n", bustType);

        int cardId;
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_cardId"), &cardId);
        wprintf(L"_cardId: %d\n", cardId);

        // CharacterBuildPathInfo _charaBuildPathInfo; // 복잡한 객체이므로 일단 생략

        int charaId;
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_charaId"), &charaId);
        wprintf(L"_charaId: %d\n", charaId);

        // ClothBuildPathInfo _clothBuildPathInfo; // 복잡한 객체이므로 일단 생략

        int controllerType; // ModelLoader.ControllerType (Enum -> int)
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_controllerType"), &controllerType);
        wprintf(L"_controllerType: %d\n", controllerType);

        int defaultPersonalityType; // ModelLoader.DefaultPersonalityType (Enum -> int)
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_defaultPersonalityType"), &defaultPersonalityType);
        wprintf(L"_defaultPersonalityType: %d\n", defaultPersonalityType);

        // Texture[] _dirtTextureArray; // 배열이므로 일단 생략

        // MasterDressData.DressData _dressElement; // 복잡한 객체이므로 일단 생략

        int dressId;
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_dressId"), &dressId);
        wprintf(L"_dressId: %d\n", dressId);

        int frameColor; // ModelLoader.TrackSuitColor (Enum -> int)
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_frameColor"), &frameColor);
        wprintf(L"_frameColor: %d\n", frameColor);

        int genderType; // ModelLoader.GenderType (Enum -> int)
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_genderType"), &genderType);
        wprintf(L"_genderType: %d\n", genderType);

        int headModelSubId;
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_headModelSubId"), &headModelSubId);
        wprintf(L"_headModelSubId: %d\n", headModelSubId);

        float height;
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_height"), &height);
        wprintf(L"_height: %f\n", height);

        int heightType; // ModelLoader.HeightType (Enum -> int)
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_heightType"), &heightType);
        wprintf(L"_heightType: %d\n", heightType);

        bool initialized;
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_initialized"), &initialized);
        wprintf(L"_initialized: %s\n", initialized ? L"true" : L"false");

        bool isEnableModelCache;
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_isEnableModelCache"), &isEnableModelCache);
        wprintf(L"_isEnableModelCache: %s\n", isEnableModelCache ? L"true" : L"false");

        bool isPersonalDress;
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_isPersonalDress"), &isPersonalDress);
        wprintf(L"_isPersonalDress: %s\n", isPersonalDress ? L"true" : L"false");

        bool isPreCreatedLoadHashKey;
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_isPreCreatedLoadHashKey"), &isPreCreatedLoadHashKey);
        wprintf(L"_isPreCreatedLoadHashKey: %s\n", isPreCreatedLoadHashKey ? L"true" : L"false");

        bool isUseDressDataHeadModelSubId;
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_isUseDressDataHeadModelSubId"), &isUseDressDataHeadModelSubId);
        wprintf(L"_isUseDressDataHeadModelSubId: %s\n", isUseDressDataHeadModelSubId ? L"true" : L"false");

        // ResourceManager.ResourceHash _loadHashKey; // 복잡한 객체이므로 일단 생략

        int miniMobParentCharaId;
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_miniMobParentCharaId"), &miniMobParentCharaId);
        wprintf(L"_miniMobParentCharaId: %d\n", miniMobParentCharaId);

        int miniMobTailId;
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_miniMobTailId"), &miniMobTailId);
        wprintf(L"_miniMobTailId: %d\n", miniMobTailId);

        int mobId;
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_mobId"), &mobId);
        wprintf(L"_mobId: %d\n", mobId);

        // MobBuildInfo _mobInfo; // 복잡한 객체이므로 일단 생략

        int motionBodyModelSubId;
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_motionBodyModelSubId"), &motionBodyModelSubId);
        wprintf(L"_motionBodyModelSubId: %d\n", motionBodyModelSubId);

        int motionDressId;
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_motionDressId"), &motionDressId);
        wprintf(L"_motionDressId: %d\n", motionDressId);

        Il2CppString* name;
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_name"), &name);
        if (name != nullptr) {
            //const wchar_t* wideName = il2cpp_string_to_utf16(name);
            wprintf(L"_name: %S\n", Utils::ConvertWstringToUTF8(name->chars).c_str());
        }
        else {
            wprintf(L"_name: nullptr\n");
        }

        int npcType; // RaceDefine.RaceNpcType (Enum -> int)
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_npcType"), &npcType);
        wprintf(L"_npcType: %d\n", npcType);

        int overrideClothCategory; // CySpringDataContainer.Category (Enum -> int)
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_overrideClothCategory"), &overrideClothCategory);
        wprintf(L"_overrideClothCategory: %d\n", overrideClothCategory);

        int popularity;
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_popularity"), &popularity);
        wprintf(L"_popularity: %d\n", popularity);

        int raceGateInPersonalityType; // ModelLoader.DefaultPersonalityType (Enum -> int)
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_raceGateInPersonalityType"), &raceGateInPersonalityType);
        wprintf(L"_raceGateInPersonalityType: %d\n", raceGateInPersonalityType);

        int raceOverRunPersonalityType; // ModelLoader.RacePersonalityType (Enum -> int)
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_raceOverRunPersonalityType"), &raceOverRunPersonalityType);
        wprintf(L"_raceOverRunPersonalityType: %d\n", raceOverRunPersonalityType);

        int raceRunningType; // ModelLoader.RaceRunningType (Enum -> int)
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_raceRunningType"), &raceRunningType);
        wprintf(L"_raceRunningType: %d\n", raceRunningType);

        int raceRunPersonalityType; // ModelLoader.RacePersonalityType (Enum -> int)
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_raceRunPersonalityType"), &raceRunPersonalityType);
        wprintf(L"_raceRunPersonalityType: %d\n", raceRunPersonalityType);

        int skinType; // ModelLoader.SkinType (Enum -> int)
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_skinType"), &skinType);
        wprintf(L"_skinType: %d\n", skinType);

        int socksType; // ModelLoader.SocksType (Enum -> int)
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_socksType"), &socksType);
        wprintf(L"_socksType: %d\n", socksType);

        // GameObject _sweatLocator; // 복잡한 객체이므로 일단 생략
        // GameObject _sweatObject; // 복잡한 객체이므로 일단 생략

        // Texture[] _wetTextureArray; // 배열이므로 일단 생략

        int zekken;
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_zekken"), &zekken);
        wprintf(L"_zekken: %d\n", zekken);

        int zekkenColor; // ModelLoader.ZekkenColor (Enum -> int)
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_zekkenColor"), &zekkenColor);
        wprintf(L"_zekkenColor: %d\n", zekkenColor);

        int zekkenFontColor; // ModelLoader.ZekkenFontColor (Enum -> int)
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_zekkenFontColor"), &zekkenFontColor);
        wprintf(L"_zekkenFontColor: %d\n", zekkenFontColor);

        int zekkenFontStyle; // FontStyle (Enum -> int)
        il2cpp_field_get_value(charInfo, il2cpp_class_get_field_from_name(((Il2CppObject*)charInfo)->klass, "_zekkenFontStyle"), &zekkenFontStyle);
        wprintf(L"_zekkenFontStyle: %d\n", zekkenFontStyle);
		Logger::Debug(SECTION_NAME, L"CreateModel called origcharaid=%d, origdressid=%d, mobid=%d", charaId, dressId, mobId);

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