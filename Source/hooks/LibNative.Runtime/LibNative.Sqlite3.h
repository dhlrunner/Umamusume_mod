#pragma once
#include "../../tools/Logger.hpp"
#include "../../Settings.h"
#include "../hook-helper.h"
#include "../Unity/il2cpp/il2cpp-tools.hpp"
#include "../../Utils.h"
#include <array>

#define SECTION_NAME L"LIBNATIVE_SQLITE3"

namespace LibNative::Sqlite3 {
	void Init();
}
