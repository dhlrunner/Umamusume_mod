#pragma once
#include "..\..\tools\Logger.hpp"
#include "..\Unity\il2cpp\il2cpp_symbols.hpp"
#include "..\Unity\il2cpp\il2cpp-tabledefs.h"
#include "..\Unity\il2cpp\il2cpp-tools.hpp"
#include "..\..\Settings.h"
#include "..\..\Utils.h"
#include "..\hook-helper.h"
#include "..\Unity\UnityEngine.CoreModule.h"
#include "Screen.h"
#include "GallopStructs.h"


#define SECTION_NAME L"GALLOP_SCENEMANAGER"

namespace Gallop::SceneManager
{
	void Init();
}