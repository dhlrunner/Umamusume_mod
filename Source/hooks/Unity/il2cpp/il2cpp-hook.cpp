#include "il2cpp-hook.h"

void* il2cpp_init_orig = nullptr;
bool __stdcall il2cpp_init_hook(const char* domain_name) {
	Logger::Info(L"IL2CPP", L"il2cpp_init called");

	const auto result = reinterpret_cast<decltype(il2cpp_init_hook)*>(il2cpp_init_orig)(domain_name);
	InitHooks_BeforeBoot();
	//il2cpp_symbols::init(GetModuleHandle(L"GameAssembly.dll"));
	return true;
}

void* il2cpp_unhandled_exception_orig = nullptr;
void __stdcall il2cpp_unhandled_exception_hook(Il2CppException* exception) {
	//Log all exceptions
	Logger::Error(L"IL2CPP", L"Unhandled exception: %s", exception->message->chars ? exception->message->chars : L"(no message)");
	Logger::Error(L"IL2CPP", L"Stack trace: %s", exception->stack_trace->chars ? exception->stack_trace->chars : L"(no stack trace)");
	Logger::Error(L"IL2CPP", L"Exception type: %S", exception->klass->name ? exception->klass->name : "(no type name)");
	Logger::Error(L"IL2CPP", L"Exception klass: %p", exception->klass);

	reinterpret_cast<decltype(il2cpp_unhandled_exception_hook)*>(il2cpp_unhandled_exception_orig)(exception);
}

void* il2cpp_raise_exception_orig = nullptr;
Il2CppObject* __stdcall il2cpp_raise_exception_hook(Il2CppException* exception) {
	//Log all exceptions
	Logger::Error(L"IL2CPP", L"Exception raised: %s", exception->message->chars ? exception->message->chars : L"(no message)");
	//Logger::Error(L"IL2CPP", L"Stack trace: %S", exception->stack_trace->chars ? Utils::ConvertWstringToUTF8(exception->stack_trace->chars) : "(no stack trace)");
	Logger::Error(L"IL2CPP", L"Exception type: %S", exception->klass->name ? exception->klass->name : "(no type name)");
	Logger::Error(L"IL2CPP", L"Exception klass: %p", exception->klass);
	return reinterpret_cast<decltype(il2cpp_raise_exception_hook)*>(il2cpp_raise_exception_orig)(exception);
}

void il2cpphook_init(HMODULE il2cpp_module) {
	//GetProcAddress(module, il2cpp_symbols::GetObsfucatedFnName("il2cpp_init"))
	Logger::Debug(L"IL2CPP", L"Hooking il2cpp_init");
	auto init_addr = GetProcAddress(il2cpp_module, il2cpp_symbols::GetObsfucatedFnName("il2cpp_init"));
	EnableHook(init_addr, il2cpp_init_hook, &il2cpp_init_orig, L"il2cpp_init");

	//hook il2cpp_unhandled_exception
	auto unhandled_exception_addr = GetProcAddress(il2cpp_module, il2cpp_symbols::GetObsfucatedFnName("il2cpp_unhandled_exception"));
	EnableHook(unhandled_exception_addr, il2cpp_unhandled_exception_hook, &il2cpp_unhandled_exception_orig, L"il2cpp_unhandled_exception");

	//hook il2cpp_exception_raise
	auto exception_raise_addr = GetProcAddress(il2cpp_module, il2cpp_symbols::GetObsfucatedFnName("il2cpp_raise_exception"));
	EnableHook(exception_raise_addr, il2cpp_raise_exception_hook, &il2cpp_raise_exception_orig, L"il2cpp_raise_exception");
	
	
}
