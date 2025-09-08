#include "Cyan.LocalFile.h"

namespace Cyan::LocalFile
{
	void* LocalFileHelper_GetPath_orig = nullptr;
	Il2CppString* LocalFileHelper_GetPath_hook(Il2CppObject* _this, Il2CppString* name)
	{
		Logger::Info(SECTION_NAME, L"LocalFileHelper_GetPath_hook: name=%S", Utils::ConvertWstringToUTF8(name->chars).c_str());
		Il2CppString* path = reinterpret_cast<decltype(LocalFileHelper_GetPath_hook)*>(LocalFileHelper_GetPath_orig)(_this, name);
		
		return path;
	}

	void* LocalFileHelper_Exists_orig = nullptr;
	bool LocalFileHelper_Exists_hook(Il2CppObject* _this, Il2CppString* name)
	{
		Logger::Info(SECTION_NAME, L"LocalFileHelper_Exists_hook: name=%S", Utils::ConvertWstringToUTF8(name->chars).c_str());
		bool exists = reinterpret_cast<decltype(LocalFileHelper_Exists_hook)*>(LocalFileHelper_Exists_orig)(_this, name);

		return exists;
	}

	void Init() {
		Logger::Info(SECTION_NAME, L"Init");

		auto LocalFileHelper_GetPath_addr = il2cpp_symbols::get_method_pointer(
			"_Cyan.dll", "Cyan.LocalFile",
			"LocalFileHelper", "GetPath", 1
		);
		EnableHook(LocalFileHelper_GetPath_addr, &LocalFileHelper_GetPath_hook, &LocalFileHelper_GetPath_orig, L"LocalFileHelper_GetPath");

		auto LocalFileHelper_Exists_addr = il2cpp_symbols::get_method_pointer(
			"_Cyan.dll", "Cyan.LocalFile",
			"LocalFileHelper", "Exists", 1
		);
		EnableHook(LocalFileHelper_Exists_addr, &LocalFileHelper_Exists_hook, &LocalFileHelper_Exists_orig, L"LocalFileHelper_Exists");


	}
}