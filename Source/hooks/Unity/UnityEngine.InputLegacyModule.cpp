#include "UnityEngine.InputLegacyModule.h"

namespace UnityEngine::InputLegacyModule
{
	bool (*GetKeyDown)(KeyCode);
	bool (*GetKey)(KeyCode);

	void* GetKeyDown_orig = nullptr;
	bool GetKeyDown_hook(KeyCode key)
	{
		if(Global::blockInput)
			return false;

		return reinterpret_cast<decltype(GetKeyDown_hook)*>(GetKeyDown_orig)(key);
	}

	void* GetKey_orig = nullptr;
	bool GetKey_hook(KeyCode key)
	{
		if (Global::blockInput)
			return false;

		return reinterpret_cast<decltype(GetKey_hook)*>(GetKey_orig)(key);
	}

	void* QueueInputEvent_orig = nullptr;
	void QueueInputEvent_hook(void* inputEvent)
	{
		if (Global::blockInput)
			return;
		return reinterpret_cast<decltype(QueueInputEvent_hook)*>(QueueInputEvent_orig)(inputEvent);
	}

	void* Update_orig = nullptr;
	void Update_hook()
	{
		if (Global::blockInput)
			return;
		return reinterpret_cast<decltype(Update_hook)*>(Update_orig)();
	}

	void Init() 
	{
		GetKeyDown = reinterpret_cast<bool(*)(KeyCode)> (
			il2cpp_symbols::get_method_pointer(
				"UnityEngine.InputLegacyModule.dll", "UnityEngine",
				"Input", "GetKeyDown", 1
			)
			);
		EnableHook(
			reinterpret_cast<void*>(GetKeyDown),
			&GetKeyDown_hook,
			&GetKeyDown_orig,
			L"Input_GetKeyDown"
		);

		GetKey = reinterpret_cast<bool(*)(KeyCode)> (
			il2cpp_symbols::get_method_pointer(
				"UnityEngine.InputLegacyModule.dll", "UnityEngine",
				"Input", "GetKey", 1
			)
			);
		EnableHook(
			reinterpret_cast<void*>(GetKey),
			&GetKey_hook,
			&GetKey_orig,
			L"Input_GetKey"
		);

		auto QueueInputEvent_addr = il2cpp_resolve_icall("UnityEngineInternal.Input.NativeInputSystem::QueueInputEvent(System.IntPtr)");	
		EnableHook(QueueInputEvent_addr, &QueueInputEvent_hook, &QueueInputEvent_orig, L"QueueInputEvent");

		auto Update_addr = il2cpp_resolve_icall("UnityEngineInternal.Input.NativeInputSystem::Update(UnityEngineInternal.Input.NativeInputUpdateType)");
		EnableHook(Update_addr, &Update_hook, &Update_orig, L"Input_Update");
	}
}