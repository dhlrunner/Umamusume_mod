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
		il2cpphook_init(GetProcAddress(module, il2cpp_symbols::GetObsfucatedFnName("il2cpp_init")));
		Global::currenthWnd = GetActiveWindow();
		return module;
		//Utils::RemoveProtection(module);
		//Utils::RemoveProtection(GetModuleHandle(L"umamusume.exe"));
	}
	return reinterpret_cast<decltype(LoadLibraryW)*>(LoadLibraryW_orig)(path);
}

void* PathFileExistsW_orig = nullptr;
BOOL WINAPI PathFileExistsW_hook(LPCWSTR lpPathName)
{
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



void WinHook_init() {
	Logger::Info(L"HOOK", L"Windows API hook initializing");
	/*MH_CreateHook(RegQueryValueA, RegQueryValueA_hook, &RegQueryValueA_orig);
	MH_EnableHook(RegQueryValueA);
	MH_CreateHook(RegQueryValueExA, RegQueryValueExA_hook, &RegQueryValueExA_orig);
	MH_EnableHook(RegQueryValueExA);*/

	if (!EnableHookApi(L"kernelbase.dll", "LoadLibraryW",
		LoadLibraryW__hook, &LoadLibraryW_orig, L"LoadLibraryW"))
		MessageBox(nullptr, L"Hook LoadLibraryW failed", L"MinHook", MB_OK);

	if (!EnableHookApi(L"shlwapi.dll", "PathFileExistsW",
		PathFileExistsW_hook, &PathFileExistsW_orig , L"PathFileExistsW"))
		MessageBox(nullptr, L"Hook PathFileExistsW failed", L"MinHook", MB_OK);

	Logger::Info(L"HOOK", L"Windows API hook initialize completed");
}