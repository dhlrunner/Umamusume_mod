#pragma once
#include "..\..\tools\Logger.hpp"
#include "Unity\il2cpp\il2cpp_symbols.hpp"
#include "Unity\UnityEngine.InputLegacyModule.h"
#include "Unity\UnityEngine.CoreModule.h"
#include "Unity\UnityStructs.h"
#include "..\..\Settings.h"
#include "..\Global.h"
#include "Gallop/GallopStructs.h"
#include "Gallop/GallopUtil.h"
#include "GallopDialogUtil.h"

#include <thread>
#include <string>

#define SECTION_NAME L"BACKGNDWORK"

namespace BackgroundWorker
{
	void Init();
}