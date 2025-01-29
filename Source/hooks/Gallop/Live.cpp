#include "Live.h"

namespace Gallop::Live 
{
	void* FadeGui_SetAlpha_orig = nullptr;
	void FadeGui_SetAlpha_hook(Il2CppObject* _this, float alpha) {

		if (!Settings::Global->showLiveTitleWindow) {
			alpha = 0.0f;
		}

		return reinterpret_cast<decltype(FadeGui_SetAlpha_hook)*>
			(FadeGui_SetAlpha_orig)(_this, alpha);
	}

	void* LiveTimelineCamera_AlterUpdate_orig = nullptr;
	void LiveTimelineCamera_AlterUpdate_hook(void* _this, float liveTime) {
		//printf("Livecam AlterUpdate time=%.5f\n",liveTime);
		if (!Settings::Local->stopLiveCam) {
			return reinterpret_cast<decltype(LiveTimelineCamera_AlterUpdate_hook)*>
				(LiveTimelineCamera_AlterUpdate_orig)(_this, liveTime);
		}

	}

	void* Director_get_LiveTotalTime_orig = nullptr;
	float Director_get_LiveTotalTime_hook(Il2CppObject* _instance) {
		float ret = reinterpret_cast<decltype(Director_get_LiveTotalTime_hook)*>(Director_get_LiveTotalTime_orig)(_instance);
		Global::liveTotalTimeSec = ret;
		if (Settings::Local->isLiveTimeManual) {
			ret = 9999.9;
		}
		return ret;
	}

	void Init()
	{
		Logger::Info(SECTION_NAME, L"Init");
		auto FadeGui_SetAlpha_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop.Live",
			"FadeGui", "SetAlpha", 1
		);
		EnableHook(FadeGui_SetAlpha_addr, &FadeGui_SetAlpha_hook, &FadeGui_SetAlpha_orig, L"Live_FadeGui_SetAlpha");

		auto LiveTimelineCamera_AlterUpdate_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop.Live",
			"LiveTimelineCamera", "AlterUpdate", 1
		);
		EnableHook(LiveTimelineCamera_AlterUpdate_addr, &LiveTimelineCamera_AlterUpdate_hook, &LiveTimelineCamera_AlterUpdate_orig, L"LiveTimelineCamera_AlterUpdate");

		auto Director_get_LiveTotalTime_addr = reinterpret_cast<float(*)()>(il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop.Live",
			"Director", "get_LiveTotalTime", 0
		));
		EnableHook(Director_get_LiveTotalTime_addr, &Director_get_LiveTotalTime_hook, &Director_get_LiveTotalTime_orig, L"Director_get_LiveTotalTime");


	}
}