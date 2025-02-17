#include "MasterDataManager.h"

namespace Gallop::MasterDataManager
{
	void* InvokeSetupListener_orig;
	void InvokeSetupListener_hook(Il2CppObject* _this) 
	{
		Logger::Info(SECTION_NAME, L"InvokeSetupListener called");
		reinterpret_cast<decltype(InvokeSetupListener_hook)*>(InvokeSetupListener_orig)(_this);
		Logger::Info(SECTION_NAME, L"InvokeSetupListener call end");
	}

	void* SetupMasterData_orig;
	il2cpp::IEnumerator* SetupMasterData_hook(Il2CppObject* _this, Il2CppDelegate* onFail) {
		Logger::Info(SECTION_NAME, L"SetupMasterData called");
		auto ret = reinterpret_cast<decltype(SetupMasterData_hook)*>(SetupMasterData_orig)(_this, onFail);

		//--set master char data
		//auto get_masterCharaData = reinterpret_cast<Il2CppObject * (*)(Il2CppObject * _this)>(il2cpp_symbols::get_method_pointer("umamusume.dll", "Gallop", "MasterDataManager", "get_masterCharaData", 0));
		//auto masterCharaData = get_masterCharaData(_this);
		//auto Get = reinterpret_cast<Il2CppObject* (*)(Il2CppObject * _this, int id)>(il2cpp_symbols::get_method_pointer("umamusume.dll", "Gallop", "MasterCharaData", "Get", 1));
		//Logger::Debug(SECTION_NAME, L"Get ptr=%p", Get);
		//auto d = Get(masterCharaData, 1001);
		////Il2CppString* name = 
		//Logger::Debug(SECTION_NAME, L"MasterCharaData_CharaData test charId=%d", ((MasterCharaData_CharaData*)d->klass)->Id);
		//--end
		return ret;

	}

	void Init() 
	{
		Logger::Info(SECTION_NAME, L"Init");
		auto InvokeSetupListener_addr = il2cpp_symbols::get_method_pointer(
				"umamusume.dll", "Gallop",
				"MasterDataManager", "InvokeSetupListener", 0
			);
		EnableHook(InvokeSetupListener_addr, &InvokeSetupListener_hook, &InvokeSetupListener_orig, L"MasterDataManager_InvokeSetupListener");

		auto SetupMasterData_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"MasterDataManager", "SetupMasterData", 1
		);
		EnableHook(SetupMasterData_addr, &SetupMasterData_hook, &SetupMasterData_orig, L"MasterDataManager_SetupMasterData");
	}
}