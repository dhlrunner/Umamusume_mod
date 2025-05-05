#include "UnityPlayer.hpp"

void* UnityMain_orig = nullptr;
__int64 __stdcall UnityMain_hook()
{
	Logger::Debug(L"UNITYPLAYER", L"UnityMain_hook()");
	return reinterpret_cast<decltype(UnityMain_hook)*>(UnityMain_orig)();
}

