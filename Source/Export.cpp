//#include "stdinclude.h"
//using namespace std;
//
//extern "C" __declspec(dllexport) __int64 __stdcall UnityMain()
//{
//	try
//	{
//
//		copy_file(filesystem::current_path().append(L"UnityPlayer.dll"), L"umamusume.exe.local\\UnityPlayer.orig.dll", filesystem::copy_options::update_existing);
//	}
//	catch (...)
//	{
//
//	}
//
//	auto unity = LoadLibraryW(L"UnityPlayer.orig.dll");
//
//	UnityMain_orig = GetProcAddress(unity, "UnityMain");
//
//	return UnityMain_hook();
//}