#include <Windows.h>
#include "../../tools/Logger.hpp"

extern void* UnityMain_orig;
int __stdcall UnityMain_hook(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd);