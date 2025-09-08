#pragma once
#include "../../tools/http/httplib.h"
#include "../../deps/lz4/lz4.h"
#include "../../tools/Logger.hpp"
#include "../../tools/http/url.hpp"
#include "../../Settings.h"
#include "../hook-helper.h"
#include "../Unity/il2cpp/il2cpp-tools.hpp"
#include "../Cute/Http.WWWRequest.h"
#include "../../Utils.h"

#include <string>


namespace libnative {
	void Init(HWND currentHWND);
}