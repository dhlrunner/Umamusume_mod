#pragma once
#include "..\..\Global.h"
#include "..\..\tools\Logger.hpp"
#include "..\Unity\il2cpp\il2cpp_symbols.hpp"
#include "..\Unity\il2cpp\il2cpp-tabledefs.h"
#include "..\Unity\il2cpp\il2cpp-tools.hpp"
#include "..\..\Settings.h"
#include "..\..\Utils.h"
#include "..\hook-helper.h"
#include "GallopStructs.h"


#define SECTION_NAME L"GALLOP_RACEUIFINISH"

namespace Gallop::RaceUIFinishOrderFlash
{

	void Init();
}