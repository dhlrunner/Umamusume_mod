#pragma once
#include <wtypes.h>
#include <vector>
#include "hooks/Unity/il2cpp/il2cpp_symbols.hpp"
#include "hooks/Unity/il2cpp/il2cppDictionary.hpp"
#include "hooks/Gallop/GallopStructs.h"

namespace Global 
{
	enum class GameType
	{
		UMAMUSUME_DMM_JP,
		UMAMUSUME_STEAM,
		UMAMUSUME_STEAM_JP,
		UMAMUSUME_STEAM_CN,
		UMAMUSUME_STEAM_KR
	};

	//레이스 결과 화면에서 착순 아이콘 플래시 표시 여부
	extern bool showFinishOrderFlash;

	extern int liveTimeLineFPS;
	extern float liveTimeSec;
	extern float liveTotalTimeSec;
	extern float oldLiveTime;
	extern float liveTimelineManualScale;
	extern bool showFinishOrderFlash;
	extern bool isShowingSeekbar;
	//extern int currSceneID;
	extern Il2CppString* currSceneName;
	//수고하셨습니다. 기무라 유이토씨
	//extern bool isKimuraChallenge;

	extern bool settingUpImageEffect;

	extern bool toastImGui;
	extern char* toastMessage;
	extern bool imgui_settingwnd_open;
	extern bool imgui_gameobjectwnd_open;

	extern bool gameTerminating;

	extern HWND currenthWnd;

	extern bool Game_HookFinished;
	extern std::vector<Gallop::MasterCharaData_CharaData*> MasterCharaData;

	extern bool isNeedFullscreen;

	//Race
	extern int raceHorseCount;
	extern Il2CppObject* raceManager;
	extern Gallop::HorseData* playerHorseData;
	extern float raceHorseSpeed;

	extern GameType gameType;

	extern std::vector <Gallop::LiveFixMemberData*> customLiveFixMemberData;

	extern bool blockInput; //imgui 창 열리면 입력 차단

}