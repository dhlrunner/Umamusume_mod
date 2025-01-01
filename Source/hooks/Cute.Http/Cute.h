#pragma once
#include "..\..\tools\Logger.hpp"
#include "..\..\Settings.h"
#include "..\Unity\il2cpp\il2cpp_symbols.hpp"
#include "..\..\deps\minhook\include\MinHook.h"

#include "WWWRequest.h"

#define SECTION_NAME L"CUTEHOOK"

namespace Cute {
	void Init();
}