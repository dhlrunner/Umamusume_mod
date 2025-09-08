#include "ModelController.h"

namespace Gallop::ModelController
{
	void* GetCardId_orig = nullptr;
	int GetCardId_hook(Il2CppObject* _this) {
		int ret = reinterpret_cast<decltype(GetCardId_hook)*>
			(GetCardId_orig)(_this);
		auto gen = std::bind(std::uniform_int_distribution<>(0, 1), std::default_random_engine());
		if (Settings::Global->winMotion564) {
			bool b = gen();
			int ret_edit = b ? 100701 : 100702;
			Logger::Info(SECTION_NAME, L"GetCardid ret=%d, replace=%d", ret, ret_edit);
			ret = ret_edit;
		}
		else if (Settings::Local->cardid > -1) {
			ret = Settings::Local->cardid;
			Logger::Info(SECTION_NAME, L"GetCardid ret=%d, replace=%d", ret, Settings::Local->cardid);
		}
		return 109701;

	}
	void Init() {
		Logger::Info(SECTION_NAME, L"Init");
		auto GetCardId_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"ModelController", "GetCardId", 0
		);
		EnableHook(GetCardId_addr, &GetCardId_hook, &GetCardId_orig, L"GetCardId");
	}
}