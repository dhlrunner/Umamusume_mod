#include "UnityPlayer.hpp"

void* UnityMain_orig = nullptr;
int __stdcall UnityMain_hook(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
	Logger::Debug(L"UNITYPLAYER", L"UnityMain_hook(%p, %p, %s, %d)", hInstance, hPrevInstance, lpCmdLine, nShowCmd);
	return reinterpret_cast<decltype(UnityMain_hook)*>(UnityMain_orig)(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
}

