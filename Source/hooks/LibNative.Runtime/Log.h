#pragma once
#include "../../tools/Logger.hpp"
#include "../../Settings.h"
#include "../hook-helper.h"
#include "../Unity/il2cpp/il2cpp-tools.hpp"
#include "../../Utils.h"

#define SECTION_NAME L"LIBNATIVE_LOG"

namespace LibNative::Log {
	void Init();
}