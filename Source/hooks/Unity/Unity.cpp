#include "Unity.h"

namespace Unity {

	void HookInit() {
		Logger::Info(L"UNITYHOOK", L"Unity Hook Init");
		UnityEngine::Application::Init();
	}
}