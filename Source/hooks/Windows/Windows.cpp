// Description: Windows API hooks.
#include "Windows.hpp"


using namespace std;


void* LoadLibraryW_orig = nullptr;
HMODULE WINAPI __stdcall LoadLibraryW__hook(const wchar_t* path) {
	//MessageBoxW(NULL, path, L"LoadLibraryW", MB_OK);
	if (path == L"cri_ware_unity.dll"s) {
		//auto h = GetModuleHandle(L"GameAssembly.dll");
		//Logger::Debug(L"HOOK", L"GameAssembly handle=%p", h);
		//pedump(h, "umamusume.exe.local\\GameAssembly.dumped.dll");
		static bool loaded = false;
		if (!loaded) {
			/*auto h = GetModuleHandle(L"GameAssembly.dll");
			Logger::Debug(L"HOOK", L"Dumping GameAssembly handle=%p", h);
			pedump(h, "umamusume.exe.local\\GameAssembly.dumped.dll");*/
			//while (true) {}
			InitHooks_AfterIl2cppInit();
			loaded = true;

		}
	}
	else if (path == L"GameAssembly.dll"s) {
		Logger::Info(L"HOOK", L"Loading GameAssembly.dll");
		HMODULE module = reinterpret_cast<decltype(LoadLibraryW)*>(LoadLibraryW_orig)(path);
		Logger::Debug(L"HOOK", L"GameAssembly handle=%p", module);
		il2cpp_symbols::init(module);
		il2cpphook_init(module);
		Global::currenthWnd = GetActiveWindow();
		return module;
		//Utils::RemoveProtection(module);
		//Utils::RemoveProtection(GetModuleHandle(L"umamusume.exe"));
	}
	return reinterpret_cast<decltype(LoadLibraryW)*>(LoadLibraryW_orig)(path);
}


//void* LoadLibraryExW_orig = nullptr;
//HMODULE WINAPI __stdcall LoadLibraryExW__hook(const wchar_t* path, HANDLE hFile, DWORD dwFlags) {
//	Logger::Debug(L"HOOK", L"LoadLibraryExW called with path=%s, hFile=%p, dwFlags=%d", path, hFile, dwFlags);
//	MessageBoxW(NULL, path, L"LoadLibraryExW", MB_OK);
//	if (path == L"cri_ware_unity.dll"s) {
//		//auto h = GetModuleHandle(L"GameAssembly.dll");
//		//Logger::Debug(L"HOOK", L"GameAssembly handle=%p", h);
//		//pedump(h, "umamusume.exe.local\\GameAssembly.dumped.dll");
//		static bool loaded = false;
//		if (!loaded) {
//			/*auto h = GetModuleHandle(L"GameAssembly.dll");
//			Logger::Debug(L"HOOK", L"Dumping GameAssembly handle=%p", h);
//			pedump(h, "umamusume.exe.local\\GameAssembly.dumped.dll");*/
//			//while (true) {}
//			InitHooks_AfterIl2cppInit();
//			loaded = true;
//
//		}
//	}
//	else if (path == L"GameAssembly.dll"s) {
//		Logger::Info(L"HOOK", L"Loading GameAssembly.dll");
//		HMODULE module = reinterpret_cast<decltype(LoadLibraryExW)*>(LoadLibraryExW_orig)(path,hFile,dwFlags);
//		Logger::Debug(L"HOOK", L"GameAssembly handle=%p", module);
//		il2cpp_symbols::init(module);
//		il2cpphook_init(module);
//		Global::currenthWnd = GetActiveWindow();
//		return module;
//		//Utils::RemoveProtection(module);
//		//Utils::RemoveProtection(GetModuleHandle(L"umamusume.exe"));
//	}
//	return reinterpret_cast<decltype(LoadLibraryExW)*>(LoadLibraryExW_orig)(path, hFile, dwFlags);
//}

void LoadLibraryProc(const wchar_t* path) {
	
}

void* PathFileExistsW_orig = nullptr;
BOOL WINAPI PathFileExistsW_hook(LPCWSTR lpPathName)
{
	//MessageBoxW(NULL, lpPathName, L"PathFileExistsW_hook", MB_OK);
	printf("Called PathFileExistsW (P1=%ls)\n", lpPathName);
	if (Utils::StrEndsWith(lpPathName, L".local"))
	{
		printf("[PreSetup] Return ERROR_FILE_NOT_FOUND\n");
		//Just once
		//MH_DisableHook(&PathFileExistsW);
		//MH_Uninitialize();
		SetLastError(ERROR_FILE_NOT_FOUND);
		return 0;
	}

	return PathFileExistsW(lpPathName);
}
void* PathIsDirectoryW_orig = nullptr;
BOOL WINAPI PathIsDirectoryW_hook(LPCWSTR pszPath)
{
	//MessageBoxW(NULL, pszPath, L"PathIsDirectoryW_hook", MB_OK);
	printf("Called PathIsDirectoryW (P1=%ls)\n", pszPath);
	if (Utils::StrEndsWith(pszPath, L".local"))
	{
		printf("[PreSetup] Return FALSE\n");
		//Just once
		//MH_DisableHook(&PathFileExistsW);
		//MH_Uninitialize();
		return FALSE;
	}
	return PathIsDirectoryW(pszPath);
}

//hook NTQueryValueKey
static const wchar_t SPOOF_SZ[] = L"EDK II - 10000"; //test
void* NtQueryValueKey_orig;
NTSTATUS NTAPI NtQueryValueKey_hook(
	HANDLE KeyHandle,
	PUNICODE_STRING ValueName,
	KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
	PVOID KeyValueInformation,
	ULONG Length,
	PULONG ResultLength
) {
	printf("Called NtQueryValueKey path=%ls\n", (ValueName && ValueName->Buffer) ? ValueName->Buffer : L"(null)");
	//원본호출후 실패면 그대로 반환
	NTSTATUS status = reinterpret_cast<decltype(NtQueryValueKey_hook)*>(NtQueryValueKey_orig)(KeyHandle, ValueName, KeyValueInformationClass,
		KeyValueInformation, Length, ResultLength);
	printf("NtQueryValueKey original status=0x%X val=%ls\n", status, (wchar_t*)((KEY_VALUE_PARTIAL_INFORMATION_WIN*)KeyValueInformation)->Data);
	if (!NT_SUCCESS(status) || ValueName == nullptr || ValueName->Buffer == nullptr) {
		return status;
	}

	std::wstring name(ValueName->Buffer, ValueName->Length / sizeof(wchar_t));
	if (_wcsicmp(name.c_str(), L"SystemBiosVersion") != 0) {
		return status;
	}

	if (KeyValueInformationClass == KeyValuePartialInformation && KeyValueInformation != nullptr) {

		auto p = reinterpret_cast<KEY_VALUE_PARTIAL_INFORMATION_WIN*>(KeyValueInformation);
		
		//문자열 타입일때만 값 바꿔치기
		if (p->Type == REG_SZ || p->Type == REG_MULTI_SZ) {
			SIZE_T bytesNeeded = (wcslen(SPOOF_SZ) + 1) * sizeof(wchar_t);
			if (bytesNeeded <= p->DataLength) {

				printf("Spoofing smbios value from '%ls' to '%ls'\n", (wchar_t*)p->Data, SPOOF_SZ);
				memcpy(p->Data, SPOOF_SZ, bytesNeeded);
				p->DataLength = (ULONG)bytesNeeded;
				if (ResultLength) *ResultLength = (ULONG)(FIELD_OFFSET(KEY_VALUE_PARTIAL_INFORMATION_WIN, Data) + bytesNeeded);
				
				return STATUS_SUCCESS;
			}
			else {
				if (ResultLength) *ResultLength = (ULONG)(FIELD_OFFSET(KEY_VALUE_PARTIAL_INFORMATION_WIN, Data) + bytesNeeded);
				return STATUS_BUFFER_OVERFLOW;
			}
		}
	}
	return status;
}


//void* FindFirstFileW_orig = nullptr;
//HANDLE WINAPI FindFirstFileW_hook(LPCWSTR lpPathName, LPWIN32_FIND_DATAW lpFindFileData)
//{
//	MessageBoxW(NULL, lpPathName, L"FindFirstFileW_hook", MB_OK);
//	printf("Called FindFirstFileW (P1=%ls)\n", lpPathName);
//	if (Utils::StrEndsWith(lpPathName, L".local"))
//	{
//		printf("[PreSetup] Return ERROR_FILE_NOT_FOUND\n");
//		//Just once
//		//MH_DisableHook(&PathFileExistsW);
//		//MH_Uninitialize();
//		SetLastError(ERROR_FILE_NOT_FOUND);
//		return 0;
//	}
//
//	return FindFirstFileW(lpPathName, lpFindFileData);
//}

//void* FindFirstFileExW_orig = nullptr;
//HANDLE WINAPI FindFirstFileExW_hook(LPCWSTR lpFileName, FINDEX_INFO_LEVELS fInfoLevelId, LPVOID lpFindFileData,
//	FINDEX_SEARCH_OPS fSearchOp, LPVOID lpSearchFilter, DWORD dwAdditionalFlags)
//{
//	//MessageBoxW(NULL, lpFileName, L"FindFirstFileExW_hook", MB_OK);
//	printf("Called FindFirstFileExW (P1=%ls)\n", lpFileName);
//	if (Utils::StrEndsWith(lpFileName, L".local"))
//	{
//		printf("[PreSetup] Return ERROR_FILE_NOT_FOUND\n");
//		//Just once
//		//MH_DisableHook(&PathFileExistsW);
//		//MH_Uninitialize();
//		SetLastError(ERROR_FILE_NOT_FOUND);
//		return 0;
//	}
//	return FindFirstFileExW(lpFileName, fInfoLevelId, lpFindFileData, fSearchOp, lpSearchFilter, dwAdditionalFlags);
//}

void* CheckRemoteDebuggerPresent_orig = nullptr;
BOOL WINAPI CheckRemoteDebuggerPresent_hook(HANDLE hProcess, PBOOL pbDebuggerPresent)
{
	Logger::Debug(L"HOOK", L"CheckRemoteDebuggerPresent called");
	//MessageBoxW(NULL, L"CheckRemoteDebuggerPresent_hook", L"CheckRemoteDebuggerPresent", MB_OK);
	if (pbDebuggerPresent)
	{
		*pbDebuggerPresent = FALSE; // Always return false to prevent detection1
	}

	return TRUE; //reinterpret_cast<decltype(CheckRemoteDebuggerPresent)*>(CheckRemoteDebuggerPresent_orig)(hProcess, pbDebuggerPresent);
}

void* IsDebuggerPresent_orig = nullptr;
BOOL WINAPI IsDebuggerPresent_hook()
{
	Logger::Debug(L"HOOK", L"IsDebuggerPresent called");
	return FALSE; // Always return false to prevent detection
}


void WinHook_init() {
	Logger::Info(L"HOOK", L"Windows API hook initializing");
	/*MH_CreateHook(RegQueryValueA, RegQueryValueA_hook, &RegQueryValueA_orig);
	MH_EnableHook(RegQueryValueA);
	MH_CreateHook(RegQueryValueExA, RegQueryValueExA_hook, &RegQueryValueExA_orig);
	MH_EnableHook(RegQueryValueExA);*/

	if (!EnableHookApi(L"kernelbase.dll", "LoadLibraryW",
		LoadLibraryW__hook, &LoadLibraryW_orig, L"LoadLibraryW"))
		MessageBox(nullptr, L"Hook LoadLibraryW failed", L"MinHook", MB_OK);

	//if (!EnableHookApi(L"kernelbase.dll", "LoadLibraryExW",
	//	LoadLibraryExW__hook, &LoadLibraryExW_orig, L"LoadLibraryExW"))
	//	MessageBox(nullptr, L"Hook LoadLibraryExW failed", L"MinHook", MB_OK);

	////Hook FindFirstFileExW
	//if (!EnableHookApi(L"kernelbase.dll", "FindFirstFileExW",
	//	FindFirstFileExW_hook, &FindFirstFileExW_orig, L"FindFirstFileExW"))
	//	MessageBox(nullptr, L"Hook FindFirstFileExW failed", L"MinHook", MB_OK);
	//Hook PathIsDirectoryW
	if (!EnableHookApi(L"shlwapi.dll", "PathIsDirectoryW",
		PathIsDirectoryW_hook, &PathIsDirectoryW_orig, L"PathIsDirectoryW"))
		MessageBox(nullptr, L"Hook PathIsDirectoryW failed", L"MinHook", MB_OK);

	if (!EnableHookApi(L"shlwapi.dll", "PathFileExistsW",
		PathFileExistsW_hook, &PathFileExistsW_orig , L"PathFileExistsW"))
		MessageBox(nullptr, L"Hook PathFileExistsW failed", L"MinHook", MB_OK);

	//hook CheckRemoteDebuggerPresent
	if (!EnableHookApi(L"kernel32.dll", "CheckRemoteDebuggerPresent",
		CheckRemoteDebuggerPresent_hook, &CheckRemoteDebuggerPresent_orig, L"CheckRemoteDebuggerPresent"))
		MessageBox(nullptr, L"Hook CheckRemoteDebuggerPresent failed", L"MinHook", MB_OK);

	//hook IsDebuggerPresent
	if (!EnableHookApi(L"kernel32.dll", "IsDebuggerPresent",
		IsDebuggerPresent_hook, &IsDebuggerPresent_orig, L"IsDebuggerPresent"))
		MessageBox(nullptr, L"Hook IsDebuggerPresent failed", L"MinHook", MB_OK);
	/*
	if (!EnableHookApi(L"ntdll.dll", "NtQueryValueKey",
		NtQueryValueKey_hook, &NtQueryValueKey_orig, L"NtQueryValueKey"))
		MessageBox(nullptr, L"Hook NtQueryValueKey failed", L"MinHook", MB_OK);*/


	//if (!EnableHookApi(L"kernel32.dll", "FindFirstFileW",
	//	FindFirstFileW_hook, &FindFirstFileW_orig, L"FindFirstFileW"))
	//	MessageBox(nullptr, L"Hook FindFirstFileW failed", L"MinHook", MB_OK);
	//MessageBoxW(NULL, L"Windows API hook initialized", L"Info", MB_OK | MB_ICONINFORMATION);
	Logger::Info(L"HOOK", L"Windows API hook initialize completed");
}