#pragma once
#include "..\..\tools\Logger.hpp"
#include "il2cpp\il2cpp_symbols.hpp"
#include "il2cpp\il2cpp-tabledefs.h"
#include "..\..\Settings.h"
#include "..\..\Utils.h"
#include "..\hook-helper.h"
#include "UnityStructs.h"

#define SECTION_NAME L"UNITY_CORE"

using namespace Unity;
namespace UnityEngine::CoreModule
{
	void Screen_set_orientation_hook(ScreenOrientation orientation);
	void Init();
}