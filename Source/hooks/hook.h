#pragma once
#include "../hooks/Plugins/libNative.h"
#include "../hooks/Gallop/Gallop.h"
#include "../hooks/Unity/Unity.h"
#include "../hooks/Windows/Windows.hpp"
#include "../hooks/Cute.Http/Cute.h"

#include "../../tools/Logger.hpp"
#include "../../tools/imgui/ImguiWindows.hpp"
#include "../../Settings.h"
#include "../../deps/minhook/include/MinHook.h"

bool InitHooks_DLLMain();
void InitHooks_AfterIl2cppInit();