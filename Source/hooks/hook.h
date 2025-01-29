#pragma once
#include "../hooks/Plugins/libNative.h"
#include "../hooks/Gallop/Gallop.h"
#include "../hooks/Unity/Unity.h"
#include "../hooks/Windows/Windows.hpp"
#include "../hooks/Cute/Cute.h"
#include "../hooks/Cyan/Cyan.h"

#include "../../tools/Logger.hpp"
#include "../../tools/imgui/ImguiWindows.hpp"
#include "../../Settings.h"
#include "../../deps/minhook/include/MinHook.h"

#include "Unity/il2cpp/il2cpp_dump.h"

#include "BackgroundWorker.h"

bool InitHooks_DLLMain();
void InitHooks_BeforeBoot();
void InitHooks_AfterIl2cppInit();