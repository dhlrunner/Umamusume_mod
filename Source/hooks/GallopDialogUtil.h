#pragma once
#include "..\..\tools\Logger.hpp"

#include "Unity\il2cpp\il2cpp_symbols.hpp"
#include "Unity\il2cpp\il2cpp-tabledefs.h"
#include "Unity\il2cpp\il2cpp-tools.hpp"
#include "..\..\Settings.h"
#include "..\Global.h"
#include "Gallop/GallopStructs.h"
#include "Gallop/GallopUtil.h"

using namespace std;
namespace GallopDialog 
{
	void ShowTextDialog(wstring title, wstring text);
	void ShowToast(wstring text);
}