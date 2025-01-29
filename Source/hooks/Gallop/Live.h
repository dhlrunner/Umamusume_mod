#pragma once
#include "..\..\Global.h"
#include "..\..\tools\Logger.hpp"
#include "..\Unity\il2cpp\il2cpp_symbols.hpp"
#include "..\Unity\il2cpp\il2cpp-tabledefs.h"
#include "..\..\Settings.h"
#include "..\..\Utils.h"
#include "..\hook-helper.h"

#define SECTION_NAME L"GALLOP_LIVE"

namespace Gallop::Live
{
	void Init();
}