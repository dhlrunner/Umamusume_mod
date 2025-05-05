#include <Windows.h>
#include "../../tools/Logger.hpp"

extern void* UnityMain_orig;
__int64 __stdcall UnityMain_hook();