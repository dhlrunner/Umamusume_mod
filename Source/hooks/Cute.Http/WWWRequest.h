#pragma once
#include "..\..\tools\Logger.hpp"
#include "..\..\Settings.h"
#include "..\Unity\il2cpp\il2cpp_symbols.hpp"
#include "..\..\deps\minhook\include\MinHook.h"

#include "..\..\tools\http\url.hpp"

namespace Cute::Http::WWWRequest {
	extern Url CurrentUrl;
	extern Url LastUrl;

	void Init();
}