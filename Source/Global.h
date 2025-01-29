#pragma once

namespace Global 
{
	//레이스 결과 화면에서 착순 아이콘 플래시 표시 여부
	extern bool showFinishOrderFlash;

	extern int liveTimeLineFPS;
	extern float liveTimeSec;
	extern float liveTotalTimeSec;
	extern float oldLiveTime;
	extern float liveTimelineManualScale;
	

	extern bool settingUpImageEffect;

	extern bool toastImGui;
	extern char* toastMessage;
	extern bool imgui_settingwnd_open;

	extern bool gameTerminating;

}