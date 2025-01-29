#pragma once
#include "../../Global.h"
#include "..\..\tools\Logger.hpp"
#include "..\Unity\il2cpp\il2cpp_symbols.hpp"
#include "..\Unity\il2cpp\il2cpp-tabledefs.h"
#include "..\..\Settings.h"
#include "..\..\Utils.h"
#include "..\hook-helper.h"
#include "..\Unity\UnityStructs.h"
#include "GallopStructs.h"


#define SECTION_NAME L"GAMESYSTEM"

namespace Gallop::GameSystem
{
	void Init();
}
