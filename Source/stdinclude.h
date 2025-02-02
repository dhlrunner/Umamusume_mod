#pragma once
#define NOMINMAX

#include "tools/stb_image.h"



#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include "stdio.h"
#include "tools/PEDump/PEDump.h"

#include <locale>
#include <filesystem>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <format>
#include <functional>


#include "imgui.h"
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_dx11.h"
#include "imgui_internal.h"
#include "imgui_notify.h"


#include "d3d11.h"
#include <wincodec.h>

#include "deps/minhook/include/MinHook.h"
#pragma comment(lib, "lib/Debug/libMinHook.x64.lib")

#include "tools/kiero/kiero.h"

//Logger
#include "tools/Logger.hpp"

//UnityPlayer
#include "hooks/Unity/UnityPlayer.hpp"

//Hooks
#include "hooks/hook.h"
#include "hooks/Windows/Windows.hpp"
#include "tools/imgui/imguiwindows.h"
#include "hooks/Unity/il2cpp/il2cpp_symbols.hpp"
#include "hooks/Unity/il2cpp/SymbolMapGenerator.hpp"
#include "hooks/Unity/Unity.h"

#include "tools/http/url.hpp"
#include "Settings.h"

#pragma comment(lib, "d3d11.lib")


