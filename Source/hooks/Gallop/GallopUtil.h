#pragma once
#include "..\..\tools\Logger.hpp"
#include "..\Unity\il2cpp\il2cpp_symbols.hpp"
#include "..\Unity\il2cpp\il2cpp-tabledefs.h"
#include "..\..\Settings.h"
#include "..\..\Utils.h"
#include "..\hook-helper.h"
#include "..\Unity\UnityStructs.h"
#include "GallopStructs.h"

#include <string>

#define SECTION_NAME L"GALLOPUTIL"

namespace Gallop::GallopUtil
{
	void Init();
}