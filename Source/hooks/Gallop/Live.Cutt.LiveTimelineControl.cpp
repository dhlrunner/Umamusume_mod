#include "Live.Cutt.LiveTimelineControl.h"

namespace Gallop::Live::Cutt::LiveTimelineControl
{
	
	void* AlterUpdate_orig = nullptr;
	void AlterUpdate_hook(void* _instance, float liveTime) {

		float target_frame_time = 1000.0f / static_cast<float>(Global::liveTimeLineFPS);
		float remaining_time = target_frame_time - liveTime;

		if (Settings::Local->isLiveTimeManual) {
			liveTime = Global::liveTimeSec;
		}
		else {
			Global::liveTimeSec = liveTime;
		}
		if (Global::liveTimeLineFPS > 0) {

			/*	if (remaining_time > 0) {
					return reinterpret_cast<decltype(Live_Cutt_LiveTimelineControl_AlterUpdate_hook)*>(Live_Cutt_LiveTimelineControl_AlterUpdate_orig)(_instance, liveTime);

				}*/
			if ((liveTime - Global::oldLiveTime) >= (1.0f / static_cast<float>(Global::liveTimeLineFPS))) {
				Global::oldLiveTime = liveTime;
			}
			liveTime = Global::oldLiveTime;
		}

		Global::oldLiveTime = liveTime;
		return reinterpret_cast<decltype(AlterUpdate_hook)*>(AlterUpdate_orig)(_instance, liveTime);
	}

	void Init() 
	{
		Logger::Info(SECTION_NAME, L"Init");
		auto AlterUpdate_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop.Live.Cutt",
			"LiveTimelineControl", "AlterUpdate", 1
		);
		EnableHook(AlterUpdate_addr, &AlterUpdate_hook, &AlterUpdate_orig, L"LiveTimelineControl_AlterUpdate");

	}
}