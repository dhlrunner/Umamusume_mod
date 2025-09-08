#include "CharacterBuildInfo.h"

namespace Gallop::CharacterBuildInfo_
{
	void* ctor_orig = nullptr;
	void ctor_hook(Il2CppObject* _this,
		int charaId, int dressId, int controllerType, int headId = 0, int zekken = 0, int mobId = 0,
		int backDancerColorId = -1, bool isUseDressDataHeadModelSubId = true,
		int audienceId = 0, int motionDressId = -1, bool isEnableModelCache = true) {
				
		CharacterBuildInfo* info =
			(CharacterBuildInfo*)((uint8_t*)_this + sizeof(Il2CppObject));
		Logger::Debug(SECTION_NAME, L"CharacterBuildInfo_ctor called origcharaid=%d, origdressid=%d, mini=%d, mobid=%d", charaId, dressId, info->_miniMobParentCharaId, mobId);

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
				info->_charaId = Settings::Local->gachaCutinChara;
				charaId = Settings::Local->gachaCutinChara;
			}
			if (Settings::Local->gachaCutinDress > -1) {
				/*if (dressId == 900101)
					dressId = 900201;*/
					//else

				info->_dressId = Settings::Local->gachaCutinDress;
				dressId = Settings::Local->gachaCutinDress;
			}
			if (Settings::Local->gachaCutinHeadid > -1) {
				info->_headModelSubId = Settings::Local->gachaCutinHeadid;
				headId = Settings::Local->gachaCutinHeadid;
			}
		}

		if (Settings::Local->changeStoryChar) {
			if ((Settings::Local->story3dCharID < 0) || (Settings::Local->story3dClothID < 0) || (Settings::Local->story3dHeadID < 0))
			{
				std::string line;
				while (true) {
					try {


						std::cout << "Enter charaid, mobid, dressid, headid" << line << "\n";
						std::cout << "Default is: " << charaId << " " << mobId << " " << dressId << " " << headId << "\n";

						std::getline(std::cin, line);

						//std::cout <<  "Entered: " << line;
						std::vector < std::string > arg = Utils::explode(line, ' ');


						int _charaId = std::stoi(arg.at(0).c_str());
						int _mobId = std::stoi(arg.at(1).c_str());
						int _dressId = std::stoi(arg.at(2).c_str());
						int _headid = std::stoi(arg.at(3).c_str());

						charaId = _charaId;
						mobId = _mobId;
						dressId = _dressId;
						headId = _headid;

						printf("CutInModelController.Context set manual %d %d %d %d\n", charaId, mobId, dressId, headId);
						break;
					}
					catch (std::invalid_argument&) {
						printf("Value Error: please enter number only\n");
					}
					catch (std::out_of_range&) {
						std::cout << "You entered " << line << "\n";
						printf_s("Argument Error: please enter {CharID} {mob id} {Dress id} {Head ID} \n");
					}
				}



				//printf("Enter charaid, clothid, headid, mobid: ");

				//scanf_s("%d %d %d %d", &charaId, &clothId, &headId, &mobId);
				printf("\n");
			}
			else
			{
				charaId = Settings::Local->story3dCharID;
				dressId = Settings::Local->story3dClothID;
				headId = Settings::Local->story3dHeadID;
				printf("CharacterBuildInfo_ctor set %d %d %d\n", charaId, dressId, headId);
			}
		}
		

		//controllerType = 0x0c;
		
		Logger::Debug(SECTION_NAME, L"CharacterBuildInfo_ctor called ccharaid=%d, cdressid=%d", charaId, dressId);
		//charaId = 1070;
		//dressId = 2;

		//FieldInfo* ismini
		return reinterpret_cast<decltype(ctor_hook)*>
			(ctor_orig)(_this, charaId, dressId, controllerType, headId,
				zekken, mobId, backDancerColorId, isUseDressDataHeadModelSubId, audienceId,
				motionDressId, isEnableModelCache);
	}

	void* ctor2_orig = nullptr;
	void ctor2_hook(CharacterBuildInfo* src) {
		int charaId;
		il2cpp_field_get_value((Il2CppObject*)src, il2cpp_class_get_field_from_name(((Il2CppObject*)src)->klass, "_charaId"), &charaId);
		int mobId;
		il2cpp_field_get_value((Il2CppObject*)src, il2cpp_class_get_field_from_name(((Il2CppObject*)src)->klass, "_mobId"), &mobId);
		int dressId;
		il2cpp_field_get_value((Il2CppObject*)src, il2cpp_class_get_field_from_name(((Il2CppObject*)src)->klass, "_dressId"), &dressId);
		//Il2CppString* name;
		//il2cpp_field_get_value((Il2CppObject*)src, il2cpp_class_get_field_from_name(((Il2CppObject*)src)->klass, "_name"), &name);

		Logger::Debug(SECTION_NAME, L"CharacterBuildInfo_ctor_overload1 called charaid=%d, mobId=%d, dressId=%d", charaId, mobId, dressId);

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
	void ctor3_hook(void* _this,
		int cardId, int charaId, int dressId, int controllerType, int headId = 0, int zekken = 0, int mobId = 0, int backDancerColorId = -1,
		int overrideClothCategory = 0xFFFFFFFF, bool isUseDressDataHeadModelSubId = true,
		int audienceId = 0, int motionDressId = -1, bool isEnableModelCache = true, int charaDressColorSetId = 0) {
		Logger::Debug(SECTION_NAME, L"CharacterBuildInfo_ctor2 called origcharaid=%d, origdressid=%d, mobId=%d", charaId, dressId, mobId);

		if (Settings::Local->gachaCutinChara > -1) {
			charaId = Settings::Local->gachaCutinChara;
		}
		if (Settings::Local->gachaCutinDress > -1) {
			dressId = Settings::Local->gachaCutinDress;
		}
		if (Settings::Local->gachaCutinHeadid > -1) {
			headId = Settings::Local->gachaCutinHeadid;
		}
		//controllerType = 0x0c;
		Logger::Debug(SECTION_NAME, L"CharacterBuildInfo_ctor2 called ccharaid=%d, cdressid=%d", charaId, dressId);
		return reinterpret_cast<decltype(ctor3_hook)*>
			(ctor3_orig)(_this, cardId, charaId, dressId, controllerType,
				headId, zekken, mobId, backDancerColorId, overrideClothCategory,
				isUseDressDataHeadModelSubId, audienceId, motionDressId, isEnableModelCache, charaDressColorSetId);

	}
	
	void* IsMini_orig = nullptr;
	bool IsMini_hook(CharacterBuildInfo* _this) {
		Logger::Debug(SECTION_NAME, L"IsMini called");
		FieldInfo* contollerTypeField = il2cpp_class_get_field_from_name(((Il2CppObject*)_this)->klass, "_controllerType");
		int controllerType = 0x0c;
		il2cpp_field_set_value((Il2CppObject*)_this, contollerTypeField, &controllerType);
		bool ret = reinterpret_cast<decltype(IsMini_hook)*>
			(IsMini_orig)(_this);
		return true;
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

		auto IsMini_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"CharacterBuildInfo", "IsMini", 0
		);
		//EnableHook(IsMini_addr, &IsMini_hook, &IsMini_orig, L"CharacterBuildInfo_IsMini");

	}
}