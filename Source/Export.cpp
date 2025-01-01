#include "stdinclude.h"
using namespace std;

extern "C" __declspec(dllexport) int __stdcall UnityMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
	try
	{

		copy_file(filesystem::current_path().append(L"UnityPlayer.dll"), L"umamusume.exe.local\\UnityPlayer.orig.dll", filesystem::copy_options::update_existing);
	}
	catch (...)
	{

	}

	auto unity = LoadLibraryW(L"UnityPlayer.orig.dll");

	UnityMain_orig = GetProcAddress(unity, "UnityMain");

	return UnityMain_hook(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
}