#pragma once
#include "..\..\tools\Logger.hpp"
#include "il2cpp\il2cpp_symbols.hpp"
#include "il2cpp\il2cpp-tabledefs.h"
#include "..\..\Settings.h"
#include "..\..\Utils.h"
#include "../../Global.h"
#include "..\hook-helper.h"

#define SECTION_NAME L"UNITYEVENTSYST"

namespace UnityEngine::EventSystems
{
	void Init();
}