#include "Global.h"

namespace Global
{
	//글로벌 변수값 초기화
	bool showFinishOrderFlash = true;
	int liveTimeLineFPS = 0;
	float liveTimeSec = 0.0f;
	float liveTotalTimeSec = 0.0f;
	float liveTimelineManualScale = 0.1;
	float oldLiveTime = 0.0f;
	bool settingUpImageEffect = false;
	bool toastImGui = false;
	char* toastMessage = nullptr;

	bool imgui_settingwnd_open = false;

	bool gameTerminating = false;

	bool isShowingSeekbar = false;
	//int currSceneID = -1;
	Il2CppString* currSceneName;

	//수고하셨습니다. 기무라 유이토씨
	//bool isKimuraChallenge = false;
	HWND currenthWnd = NULL;
	bool Game_HookFinished = false;

	std::vector<Gallop::MasterCharaData_CharaData*> MasterCharaData;

	bool isNeedFullscreen = false;
	GameType gameType = GameType::UMAMUSUME_DMM_JP;

	//race
	int raceHorseCount = 0;
	Il2CppObject* raceManager = nullptr;
	Gallop::HorseData* playerHorseData = nullptr;
	float raceHorseSpeed = 0.0f;

	std::vector <Gallop::LiveFixMemberData*> customLiveFixMemberData;
}