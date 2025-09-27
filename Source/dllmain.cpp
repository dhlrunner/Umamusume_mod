#define _CRT_SECURE_NO_WARNINGS 1
#include "stdinclude.h"

using namespace std;

void CreateConsole()
{
	if (!AttachConsole(ATTACH_PARENT_PROCESS)) {
		if (!AllocConsole()) {
			MessageBox(NULL, L"Failed to allocate console", L"Error", MB_OK | MB_ICONERROR);
			//return;
		}
	}

	//open stdout stream
	auto _ = freopen("CONOUT$", "w", stdout);
	_ = freopen("CONOUT$", "w", stderr);
	_ = freopen("CONIN$", "r", stdin);
	
	SetConsoleTitle(L"Umamusume - Debug Console");

	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD originalMode;
	GetConsoleMode(hInput, &originalMode);
	SetConsoleMode(hInput, originalMode & ENABLE_ECHO_INPUT
		| ENABLE_LINE_INPUT
		| ENABLE_PROCESSED_INPUT );

	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD outMode;
	GetConsoleMode(hOutput, &outMode);
	SetConsoleMode(hOutput, outMode & ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

	// set this to avoid turn japanese texts into question mark
	SetConsoleOutputCP(CP_UTF8);
	//_setmode(_fileno(stdout), _O_U16TEXT);
	std::locale::global(std::locale(""));

}

BOOL WINAPI DllMain(HINSTANCE h, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(h);
		//Logger::Info(L"HOOK", L"Modding DLL Attatched");
		CreateConsole();
		
		//detect exe
		wchar_t exePath[MAX_PATH];
		GetModuleFileNameW(NULL, exePath, MAX_PATH);

		//extract file name from patj
		wstring exeName = wstring(exePath);
		size_t pos = exeName.find_last_of(L"\\/");
		if (pos != wstring::npos) {
			exeName = exeName.substr(pos + 1);
		}
		Logger::Info(L"HOOK", L"Detected Executable: %s", exeName.c_str());

		if (exeName == L"umamusume.exe") {
			Logger::Info(L"HOOK", L"Detected Umamusume DMM JP");
			Global::gameType = Global::GameType::UMAMUSUME_DMM_JP;
		}
		else if (exeName == L"UmamusumePrettyDerby_Jpn.exe") {
			Logger::Info(L"HOOK", L"Detected Umamusume Steam JP");
			Global::gameType = Global::GameType::UMAMUSUME_STEAM_JP;
		}
		/*else if (exeName == L"UmamusumePrettyDerby_Cn.exe") {
			Logger::Info(L"HOOK", L"Detected Umamusume Steam CN");
			Global::gameType = Global::GameType::UMAMUSUME_STEAM_CN;
		}
		else if (exeName == L"UmamusumePrettyDerby_Kr.exe") {
			Logger::Info(L"HOOK", L"Detected Umamusume Steam KR");
			Global::gameType = Global::GameType::UMAMUSUME_STEAM_KR;
		}
		else if (exeName == L"UmamusumePrettyDerby.exe") {
			Logger::Info(L"HOOK", L"Detected Umamusume Steam");
			Global::gameType = Global::GameType::UMAMUSUME_STEAM;
		}*/
		else {
			Logger::Error(L"HOOK", L"Unknown Executable: %s", exeName.c_str());
			return FALSE;
		}
		//MessageBoxW(NULL, L"Umamusume Modding DLL Loaded", L"Info", MB_OK | MB_ICONINFORMATION);
		InitHooks_DLLMain(nullptr);
		
		/*HANDLE th = CreateThread(nullptr, 0, InitHooks_DLLMain, nullptr, 0, nullptr);
		if (th) CloseHandle(th);*/

		return TRUE;
	}
	else if (reason == DLL_PROCESS_DETACH) {
		Logger::Info(L"HOOK", L"Modding DLL Detatching");
		MH_Uninitialize();
	}

	return TRUE;
}