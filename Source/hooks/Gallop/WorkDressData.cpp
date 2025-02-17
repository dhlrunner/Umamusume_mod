#include "WorkDressData.h"

namespace Gallop::WorkDressData
{
	/*void* GetDressListByCharaId_orig;
	Il2CppObject* GetDressListByCharaId_hook(Il2CppObject* _this, int charaId, CharacterClothMode mode, bool isMob, bool isOnlyMiniCharaDress, bool isEnablePrivateDress)
	{

	}*/

	void Init() 
	{
		Logger::Info(SECTION_NAME, L"Init");
		auto GetDressListByCharaId_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"WorkDressData", "GetDressListByCharaId", 5
		);
		//EnableHook(GetDressListByCharaId_addr, &GetDressListByCharaId_hook, &GetDressListByCharaId_orig, L"WorkDressData_GetDressListByCharaId");
	}
}