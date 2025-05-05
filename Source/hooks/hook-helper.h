#pragma once
#include "../deps/minhook/include/MinHook.h"
#include "../tools/Logger.hpp"

#define DUMP(var) #var
#define SECTION_NAME L"HOOKHELP"

bool EnableHook(LPVOID pTarget, LPVOID pDetour, LPVOID* ppOriginal, const wchar_t* hookName);
bool EnableHookApi(LPCWSTR  moduleName,
	LPCSTR   procName,
	LPVOID   pDetour,
	LPVOID* ppOriginal,
	const wchar_t* hookName);