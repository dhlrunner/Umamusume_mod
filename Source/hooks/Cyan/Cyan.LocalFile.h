#pragma once
#include "..\..\tools\Logger.hpp"
#include "../Unity\il2cpp\il2cpp_symbols.hpp"
#include "../Unity\il2cpp\il2cpp-tabledefs.h"
#include "../Unity/UnityEngine.Application.h"
#include "../Unity/UnityEngine.AssetBundleModule.h"
#include "../../Settings.h"
#include "../../Global.h"
#include "../Gallop/GallopStructs.h"
#include "../Gallop/GallopUtil.h"
#include "CyanStructs.h"

#include <filesystem>

#define SECTION_NAME L"CYAN_LOCALFILE"

namespace Cyan::LocalFile
{
	void Init();
}