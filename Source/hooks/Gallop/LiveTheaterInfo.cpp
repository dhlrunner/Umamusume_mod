#include "LiveTheaterInfo.h"

namespace Gallop::LiveTheaterInfo {

	void* CheckDress_orig = nullptr;
	void CheckDress_hook(void* _this, int index, Gallop::CharaDressIdSet* idset) {
		Logger::Info(SECTION_NAME, L"LiveTheaterInfo_CheckDress called index=%d, charaid=%d", index, idset->_charaId);
		if (Settings::Global->liveCharaAutoDressReplace) {
			return reinterpret_cast<decltype(CheckDress_hook)*>
				(CheckDress_orig)(_this, index, idset);
		}
		return;
	}

	void Init() {
		auto CheckDress_addr = reinterpret_cast<void(*)(void*, int, CharaDressIdSet*)>(
			il2cpp_symbols::get_method_pointer(
				"umamusume.dll", "Gallop",
				"LiveTheaterInfo", "CheckDress", 2
			));
		if (CheckDress_addr == nullptr) {
			Logger::Error(SECTION_NAME, L"CheckDress_addr is nullptr");
			return;
		}
		else {
			Logger::Info(SECTION_NAME, L"CheckDress_addr=%p", CheckDress_addr);
			MH_CreateHook(CheckDress_addr, &CheckDress_hook, &CheckDress_orig);
			MH_EnableHook(CheckDress_addr);
		}
		
	}
}