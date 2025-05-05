#include "../../stdinclude.h"
#include "../Unity/il2cpp/il2cpp-tools.hpp"
#include "../Unity/il2cpp/il2cpp-hook.h"
#include "../Plugins/libNative.h"
#include "../../Global.h"
#include "../hook-helper.h"
#include <winternl.h>  
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

void WinHook_init();