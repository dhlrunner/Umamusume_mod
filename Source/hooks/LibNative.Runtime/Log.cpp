#include "Log.h"


namespace LibNative::Log {

	void* Info_orig = nullptr;
	void Info_hook(Il2CppString* text) {
		wprintf(L"[LibNative::Log::Info] %s\n", text->chars);
		return reinterpret_cast<decltype(Info_hook)*>(Info_orig)(text);
	}

	void* Warning_orig = nullptr;
	void Warning_hook(Il2CppString* text) {
		wprintf(L"[LibNative::Log::Warning] %s\n", text->chars);
		return reinterpret_cast<decltype(Warning_hook)*>(Warning_orig)(text);
	}

	void* Error_orig = nullptr;
	void Error_hook(Il2CppString* text) {
		wprintf(L"[LibNative::Log::Error] %s\n", text->chars);
		return reinterpret_cast<decltype(Error_hook)*>(Error_orig)(text);
	}

	void Init() {
		Logger::Info(SECTION_NAME, L"Init");
		auto Info_addr = il2cpp_symbols::get_method_pointer(
			"libnative.Runtime.dll", "LibNative",
			"Log", "Info", 1
		);
		EnableHook(Info_addr, &Info_hook, &Info_orig, L"LibNative::Log::Info");

		auto Warning_addr = il2cpp_symbols::get_method_pointer(
			"libnative.Runtime.dll", "LibNative",
			"Log", "Warning", 1
		);
		EnableHook(Warning_addr, &Warning_hook, &Warning_orig, L"LibNative::Log::Warning");

		auto Error_addr = il2cpp_symbols::get_method_pointer(
			"libnative.Runtime.dll", "LibNative",
			"Log", "Error", 1
		);
		EnableHook(Error_addr, &Error_hook, &Error_orig, L"LibNative::Log::Error");

	}
}