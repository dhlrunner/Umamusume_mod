#pragma once
#include "..\..\tools\Logger.hpp"
#include "..\..\Settings.h"
#include "..\Unity\il2cpp\il2cpp_symbols.hpp"
#include "..\hook-helper.h"

#include "..\..\tools\http\url.hpp"

#define SECTION_NAME L"CUTEHOOK"

namespace Cute::Http::WWWRequest {
	extern Url CurrentUrl;
	extern Url LastUrl;

	void Init();
}