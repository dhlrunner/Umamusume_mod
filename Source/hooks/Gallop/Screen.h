#pragma once
#include "..\..\tools\Logger.hpp"
#include "..\Unity\il2cpp\il2cpp_symbols.hpp"
#include "..\Unity\il2cpp\il2cpp-tabledefs.h"
#include "..\Unity\il2cpp\il2cpp-tools.hpp"
#include "..\..\Settings.h"
#include "..\..\Utils.h"
#include "..\hook-helper.h"
#include "..\Unity\UnityEngine.CoreModule.h"
#include "GallopStructs.h"


#define SECTION_NAME L"GALLOP_SCREEN"

namespace Gallop::Screen
{
	Il2CppObject* ChangeScreenOrientation_hook(ScreenOrientation targetOrientation, bool isForce);
	void Init();
}