#include "UnityEngine.Application.h"

namespace UnityEngine::Application {

	void* set_targetFrameRate_orig = nullptr;
	void set_targetFrameRate_hook(int value)
	{
		if (Settings::Global->autoFpsSet) {
			Settings::Global->maxFps = Utils::GetCurrentDisplayHz();
			Logger::Info(L"UNITYHOOK", L"Auto fps limit setted : %d fps", Settings::Global->maxFps);
		}
		else {
			Logger::Info(L"UNITYHOOK", L"fps limit setted : %d fps", Settings::Global->maxFps);
		}
		value = Settings::Global->maxFps;
		return reinterpret_cast<decltype(set_targetFrameRate_hook)*>(set_targetFrameRate_orig)(value);

	}


	void Init() {
		Logger::Info(L"UNITYHOOK", L"UnityEngine.Application Hook Init");

		auto set_fps_addr = il2cpp_resolve_icall("UnityEngine.Application::set_targetFrameRate(System.Int32)");
		EnableHook(set_fps_addr, &set_targetFrameRate_hook, &set_targetFrameRate_orig, L"set_targetFrameRate");
		
	}
}