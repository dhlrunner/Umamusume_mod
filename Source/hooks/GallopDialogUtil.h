#pragma once
#include "..\..\tools\Logger.hpp"

#include "Unity\il2cpp\il2cpp_symbols.hpp"
#include "Unity\il2cpp\il2cpp-tabledefs.h"
#include "Unity\il2cpp\il2cpp-tools.hpp"
#include "..\..\Settings.h"
#include "..\Global.h"
#include "Gallop/GallopStructs.h"
#include "Gallop/GallopUtil.h"
#include "Unity/UnityStructs.h"

namespace GallopDialog 
{
	Il2CppObject* ShowTextDialog(std::wstring title, std::wstring text, bool canClose = true);
	void SetDialogMessage(Il2CppObject* targetDialogObj, std::wstring text);
	void CloseDialog(Il2CppObject* targetDialogObj);
	void ShowToast(std::wstring text);
}