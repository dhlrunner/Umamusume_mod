#include "Core.Device.h"

namespace Cute::Core::Device
{
	void* GetPersistentDataPath_orig = nullptr;
	Il2CppString* GetPersistentDataPath_hook() {

		Il2CppString* ret = reinterpret_cast<decltype(GetPersistentDataPath_hook)*>
			(GetPersistentDataPath_orig)();

		if (strlen(Settings::Global->customDataPath) > 0) {
			Il2CppString* custompath = il2cpp_string_new(Settings::Global->customDataPath);
			Logger::Info(SECTION_NAME, L"originalpersistentpath=%s, replacedpersistentpath=%s", ret->chars, custompath->chars);
			return custompath;
		}

		return ret;
	}

	void Init()
	{
		Logger::Info(SECTION_NAME, L"Init");

		auto GetPersistentDataPath_addr = reinterpret_cast<Il2CppString * (*)()>(
			il2cpp_symbols::get_method_pointer(
				"Cute.Core.Assembly.dll", "Cute.Core",
				"Device", "GetPersistentDataPath", 0
		));
		EnableHook(GetPersistentDataPath_addr, &GetPersistentDataPath_hook, &GetPersistentDataPath_orig, L"GetPersistentDataPath");
	}
}