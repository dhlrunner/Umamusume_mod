#include "CutIn.h"

namespace Gallop::CutIn
{
	namespace CutInCharacter
	{
		void* Gallop_Cutin_CutinCharacter_ctor_orig = nullptr;
		void* Gallop_Cutin_CutinCharacter_ctor_hook(void* _this, CutInCharacterCreateInfo* createInfo) {
			Logger::Debug(SECTION_NAME, L"CutinCharacter type=%d charaid=%d dressid=%d, headid=%d, is어쩌구=%d, index=%d\n",
				createInfo->_characterType, createInfo->_charaId, createInfo->_clothId, createInfo->_headId, createInfo->IsUseDressDataHeadModelSubId, createInfo->_charaIndex);

			if (Settings::Global->homeAllDiamond) {
				createInfo->_characterType = (int)(TimelineKeyCharacterType)-1;
				createInfo->_charaId = 1067;
				createInfo->_clothId = 106701;
				createInfo->_headId = 0;
			}
			else {
				if (Settings::Local->gachaCharaType > -1) {
					createInfo->_characterType = Settings::Local->gachaCharaType;
				}
				if (Settings::Local->gachaCutinChara > -1) {
					createInfo->_charaId = Settings::Local->gachaCutinChara;
				}
				if (Settings::Local->gachaCutinDress > -1) {
					createInfo->_clothId = Settings::Local->gachaCutinDress;
				}
				if (Settings::Local->gachaCutinHeadid > -1) {
					createInfo->_headId = Settings::Local->gachaCutinHeadid;
				}
			}



			/*if (createInfo->_charaId == 1001) {
				createInfo->_charaId = 1026;
				if (createInfo->_clothId == 901001) {
					createInfo->_clothId = 901026;
				}
				else {
					createInfo->_clothId = 102601;
				}
			}
			else {*/
			//createInfo->_characterType = FixCharaId;
			/*createInfo->_charaId = 1065;
			createInfo->_clothId = 2;
			createInfo->_headId = 0;*/
			//}

			//createInfo->IsUseDressDataHeadModelSubId = 1;
			return reinterpret_cast<decltype(Gallop_Cutin_CutinCharacter_ctor_hook)*>
				(Gallop_Cutin_CutinCharacter_ctor_orig)(_this, createInfo);
		}
	}


	void Init()
	{
		Logger::Info(SECTION_NAME, L"Init");
		auto Gallop_Cutin_CutinCharacter_ctor_addr = reinterpret_cast<void(*)(void*, CutInCharacterCreateInfo*)> (
			il2cpp_symbols::get_method_pointer(
				"umamusume.dll", "Gallop.CutIn",
				"CutInCharacter", ".ctor", 1
			)
		);
		EnableHook(Gallop_Cutin_CutinCharacter_ctor_addr, &CutInCharacter::Gallop_Cutin_CutinCharacter_ctor_hook, &CutInCharacter::Gallop_Cutin_CutinCharacter_ctor_orig, L"CutInCharacter_ctor");
	}

}