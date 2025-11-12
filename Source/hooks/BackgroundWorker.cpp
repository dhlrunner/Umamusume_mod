#include "BackgroundWorker.h"

using namespace std;
using namespace UnityEngine::InputLegacyModule;
using namespace UnityEngine::CoreModule;
using namespace Global;

namespace BackgroundWorker
{

	struct KeyTracker {
		std::array<unsigned char, 256> prev{}; //이전 프레임 눌림여부
		std::array<unsigned char, 256> curr{}; //현재 프레임 눌림여부
		bool chordLatched = false;             //연속눌림방지용

		static inline bool IsDownVK(int vk) {
			//최상위 비트로 현재 눌림 확인
			return (GetAsyncKeyState(vk) & 0x8000) != 0;
		}

		void Update() {
			prev = curr;
			for (int vk = 0; vk < 256; ++vk) {
				curr[vk] = IsDownVK(vk) ? 1 : 0;
			}
		}

		bool DownEdge(int vk)  const { return curr[vk] && !prev[vk]; }
		bool UpEdge(int vk)    const { return !curr[vk] && prev[vk]; }
		bool IsDown(int vk)    const { return curr[vk] != 0; }

		int CountKeysDown() const {
			return (int)std::count(curr.begin(), curr.end(), (unsigned char)1);
		}
	};

	static KeyTracker g_keys;

	bool IsChordTriggered(std::initializer_list<int> chord,
		bool strict = false,
		bool requireAllReleasedToReset = true)
	{
		//모든 조합키가 현재 눌림상태인지
		bool allDown = true;
		for (int vk : chord) {
			if (!g_keys.IsDown(vk)) { allDown = false; break; }
		}

		//strict 모드면 조합 외 다른 키가 눌려있으면 무효
		if (strict && allDown) {
			if (g_keys.CountKeysDown() != (int)chord.size()) {
				allDown = false;
			}
		}

		//이미 래치된 상태에서 재트리거 방기
		if (g_keys.chordLatched) {
			//래치 해제 조건
			//조합의 모든 키가 올라오거나
			//키가 하나라도 올라오면 해제
			if (requireAllReleasedToReset) {
				bool anyDown = false;
				for (int vk : chord) if (g_keys.IsDown(vk)) { anyDown = true; break; }
				if (!anyDown) g_keys.chordLatched = false;
			}
			else {
				bool anyUp = false;
				for (int vk : chord) if (g_keys.UpEdge(vk)) { anyUp = true; break; }
				if (anyUp) g_keys.chordLatched = false;
			}
			return false;
		}

		//방금 조합이 성립했을 때만 트리거함
		if (allDown) {
			//조합을 구성하는 키 중 하나라도 다운엣지가 있으면 트리거로
			bool anyDownEdge = false;
			for (int vk : chord) { if (g_keys.DownEdge(vk)) { anyDownEdge = true; break; } }
			if (anyDownEdge) {
				g_keys.chordLatched = true;
				return true;
			}
		}

		return false;
	}

	void keyDownCheckThread() {
		Logger::Debug(SECTION_NAME, L"KeyDownCheckThread IN!!!");

		while (true) {
			g_keys.Update();
			if (imgui_gameobjectwnd_open || imgui_settingwnd_open)
				blockInput = true;
			else
				blockInput = false;

			//Control + S
			if (IsChordTriggered({VK_CONTROL, 'S'})) {
				printf("S is Pressed!!!!\n");

				Settings::Local->stopLiveCam = !Settings::Local->stopLiveCam;
				printf("LiveCam Stop %s.\n", Settings::Local->stopLiveCam ? "Enabled" : "Disabled");
				if (Settings::Local->stopLiveCam) {
					GallopDialog::ShowToast(L"라이브 카메라를 정지했습니다.");
				}
				else {
					GallopDialog::ShowToast(L"라이브 카메라를 다시 움직입니다.");
				}

			}

			//Control+R
			if (IsChordTriggered({ VK_CONTROL, 'R' })) {
				printf("LCtrl + R pressed, reset game\n");
				ResetGame();
			}

			//Control+P
			if (IsChordTriggered({ VK_CONTROL, 'P' })) {
				if (get_TimeScale() <= 0.0) {
					set_TimeScale(1.0);
				}
				else {
					set_TimeScale(0.0);
				}
				printf("Lctrl + P pressed, Set game TimeScale to %.2f\n", get_TimeScale());
			}

			//Control + PageUp
			if (IsChordTriggered({ VK_CONTROL, VK_PRIOR })) {
				set_TimeScale(get_TimeScale() + 0.05);
				printf("Set Timescale %.2f\n", get_TimeScale());
			}

			//Control + PageDown
			if (IsChordTriggered({ VK_CONTROL, VK_NEXT })) {
				set_TimeScale(get_TimeScale() - 0.05);
				printf("Set Timescale %.2f\n", get_TimeScale());
			}

			//Control + End
			if (IsChordTriggered({ VK_CONTROL, VK_END })) {
				set_TimeScale(1.0);
				printf("Reset Timescale to %.2f\n", get_TimeScale());
				GallopDialog::ShowToast(L"배속을 1.0으로 초기화했습니다.");
			}

			//Control + LeftArrow
			if (IsChordTriggered({ VK_CONTROL, VK_LEFT })) {
				if (!Settings::Local->isLiveTimeManual) {
					Settings::Local->isLiveTimeManual = true;
					GallopDialog::ShowToast(L"라이브 타임라인 수동 조작이 활성화 되었습니다.");
				}

				if (liveTimeSec <= 0.0)
				{
					liveTimeSec = 0.0;
				}
				else {
					liveTimeSec = liveTimeSec - liveTimelineManualScale;
				}

				printf("set liveTime Second to %.4f\n", liveTimeSec);
				Sleep(1);
			}

			//Control + RightArrow
			if (IsChordTriggered({ VK_CONTROL, VK_RIGHT })) {
				if (!Settings::Local->isLiveTimeManual) {
					Settings::Local->isLiveTimeManual = true;
					GallopDialog::ShowToast(L"라이브 타임라인 수동 조작이 활성화 되었습니다.");
				}
				liveTimeSec = liveTimeSec + liveTimelineManualScale;
				printf("set liveTime Second to %.4f\n", liveTimeSec);
				Sleep(1);
			}

			//Control + G
			if (IsChordTriggered({ VK_CONTROL, 'G' })) {
				GallopDialog::ShowToast(L"Toggling GameObject Window");
				imgui_gameobjectwnd_open = !imgui_gameobjectwnd_open;
				blockInput = imgui_gameobjectwnd_open;
				printf("Toggle GameObject Window %s\n", imgui_gameobjectwnd_open ? "Opened" : "Closed");

			}

			
			if (IsChordTriggered({ VK_F12 })) {
				printf("F12 is Pressed!!!!\n");
				GallopDialog::ShowToast(L"Opening setting window");
				imgui_settingwnd_open = !imgui_settingwnd_open;
				blockInput = imgui_settingwnd_open;
				printf("Show setting screen \n");
			}

			if (IsChordTriggered({ VK_F11 })) {
				printf("F11 is Pressed!!!!\n");
				Settings::Global->isShowLiveFPSGraph = !Settings::Global->isShowLiveFPSGraph;
			}

			if (IsChordTriggered({ VK_F10 })) {
				printf("F10 is Pressed!!!!\n");
				Settings::Global->isShowLivePerfInfo = !Settings::Global->isShowLivePerfInfo;
			}
			
			if (IsChordTriggered({ VK_F9 })) {
				Settings::Local->isLiveTimeManual = !Settings::Local->isLiveTimeManual;
				if(Settings::Local->isLiveTimeManual)
					GallopDialog::ShowToast(L"라이브 타임라인 수동 조작이 활성화 되었습니다.");
				else
					GallopDialog::ShowToast(L"라이브 타임라인 수동 조작이 비활성화 되었습니다.");
			}
			if (IsChordTriggered({ VK_F8 })) {
				printf("Dump il2cpp start");
				auto dialog = GallopDialog::ShowTextDialog(L"Dump il2cpp", L"Please wait...", false);
				auto h = GetModuleHandle(L"GameAssembly.dll");
				GallopDialog::SetDialogMessage(dialog, L"Dumping GameAssembly.dll ...");
				pedump(h, "umamusume.exe.local\\GameAssembly.dumped.dll");
				il2cpp_dump(dialog);
				Sleep(1000);
				GallopDialog::CloseDialog(dialog);
			}
			
			if (gameTerminating) 
			{
				Logger::Debug(SECTION_NAME, L"Game Terminating.. Exit loop");
				break;
			}
		}
	}

	void Update() 
	{
		bool isRaceScene = false;

		Logger::Debug(SECTION_NAME, L"Update thread in");
		while (!gameTerminating) 
		{
			if(wcsncmp(Global::currSceneName->chars, L"Race", Global::currSceneName->length) == 0)
			{
				//Only run once when scene changed to Race
				if (!isRaceScene) {
					
					
					//Wait for initialization
					Logger::Info(SECTION_NAME, L"Wait for RaceManager initialization");
					while (Global::raceManager == nullptr) {
						Global::raceManager = il2cpp::GetSingletonInstance(il2cpp_symbols::get_class("umamusume.dll", "Gallop", "RaceManager"));
						Sleep(100);
					}
					Logger::Debug(SECTION_NAME, L"RaceManager ptr=%p", Global::raceManager);
					//Global::raceManager = raceManagerObj;
					while (!il2cpp_class_get_method_from_name_type<bool (*)(Il2CppObject * _this)>(Global::raceManager->klass, "get_IsInitialized", 0)->methodPointer(Global::raceManager)) {
						Sleep(100);
					}
					Logger::Info(SECTION_NAME, L"RaceManager is initialized");
					int num = il2cpp_class_get_method_from_name_type<int (*)(
						Il2CppObject * _this
						)>(Global::raceManager->klass, "GetHorseNumber", 0)->methodPointer(Global::raceManager);
					Logger::Debug(SECTION_NAME, L"RaceManager GetHorseNumber = %d", num);

					//Get player horsedata
					Global::playerHorseData = il2cpp_class_get_method_from_name_type<Gallop::HorseData * (*)(
						Il2CppObject * _this
						)>(Global::raceManager->klass, "GetPlayerHorseData", 0)->methodPointer(Global::raceManager);

					//Print all horse data structs
					printf("horseIndex: %d\n", playerHorseData->horseIndex);
					printf("postNumber: %d\n", playerHorseData->postNumber);
					printf("HorseNumber: %d\n", playerHorseData->HorseNumber);
					printf("charaId: %d\n", playerHorseData->charaId);
					printf("charaName: %s\n", playerHorseData->charaName ? Utils::ConvertWstringToUTF8( playerHorseData->charaName->chars).c_str() : "NULL");
					printf("FinishOrder: %d\n", playerHorseData->FinishOrder);
					printf("FinishTimeRaw: %f\n", playerHorseData->FinishTimeRaw);
					printf("FinishTimeScaled: %f\n", playerHorseData->FinishTimeScaled);
					printf("FinishDiffTimeFromPrev: %f\n", playerHorseData->FinishDiffTimeFromPrev);
					printf("raceParam: %p\n", playerHorseData->raceParam);
					printf("responseHorseData: %p\n", playerHorseData->responseHorseData);
					printf("Popularity: %d\n", playerHorseData->Popularity);
					printf("PopularityRankLeft: %d\n", playerHorseData->PopularityRankLeft);
					printf("PopularityRankCenter: %d\n", playerHorseData->PopularityRankCenter);
					printf("PopularityRankRight: %d\n", playerHorseData->PopularityRankRight);
					printf("gateInPopularity: %d\n", playerHorseData->gateInPopularity);
					printf("Rarity: %d\n", playerHorseData->Rarity);
					printf("TrainerName: %s\n", playerHorseData->TrainerName ? Utils::ConvertWstringToUTF8(playerHorseData->TrainerName->chars).c_str() : "NULL");
					printf("IsGhost: %d\n", playerHorseData->IsGhost);
					printf("isRunningStyleExInitialized: %d\n", playerHorseData->isRunningStyleExInitialized);
					printf("runningStyleEx: %d\n", playerHorseData->runningStyleEx);
					printf("Defeat: %d\n", playerHorseData->Defeat);
					printf("RaceDressId: %d\n", playerHorseData->RaceDressId);
					printf("RaceDressIdWithOption: %d\n", playerHorseData->RaceDressIdWithOption);
					printf("RunningType: %d\n", playerHorseData->RunningType);
					printf("ActiveProperDistance: %d\n", playerHorseData->ActiveProperDistance);
					printf("ActiveProperGroundType: %d\n", playerHorseData->ActiveProperGroundType);
					printf("MobId: %d\n", playerHorseData->MobId);
					printf("raceRecord: %p\n", playerHorseData->raceRecord);
					printf("FinishOrderRawScore: %d\n", playerHorseData->FinishOrderRawScore);
					printf("TrainedCharaData: %p\n", playerHorseData->TrainedCharaData);


					
					isRaceScene = true;
				}

				//Calculate horse speed (km/h)
				float oldDistance = 0.0f;
				float currentDistance = 0.0f;
				float timeScale = playerHorseData->FinishTimeScaled / playerHorseData->FinishTimeRaw; // 시간 스케일 계산
				while (1)
				{
					void* raceView = il2cpp_class_get_method_from_name_type<void* (*)(
						Il2CppObject * _this
						)>(Global::raceManager->klass, "get_RaceView", 0)->methodPointer(Global::raceManager);
					if (raceView == nullptr)
					{
						break;
					}
					currentDistance = il2cpp_class_get_method_from_name_type<float (*)(
						Il2CppObject * _this,
						int index
						)>(Global::raceManager->klass, "GetHorseDistanceByIndex", 1)->methodPointer(Global::raceManager, playerHorseData->horseIndex);
					//Calc speed and sleep 0.1 sec
					float adjustedDeltaTime = (0.5f * timeScale); // 조정된 시간 흐름 반영
					float speed = (currentDistance - oldDistance) / adjustedDeltaTime * 3.6f;
					//printf("Speed: %.2f km/h\n", speed);
					oldDistance = currentDistance;

					Global::raceHorseSpeed = speed;

					Sleep(500);
				}
				//Logger::Info(SECTION_NAME, L"Exit loop");
			}
			else
			{
				Global::raceManager = nullptr;
				Global::playerHorseData = nullptr;
				isRaceScene = false;
			}
		}

		Logger::Info(SECTION_NAME, L"Exit update thread");

	}

	void Init()
	{
		Logger::Info(SECTION_NAME, L"Init");
		Logger::Info(SECTION_NAME, L"Starting thread");

		auto t1 = thread([]() {
			auto tr = il2cpp_thread_attach(il2cpp_domain_get());
			keyDownCheckThread();
			il2cpp_thread_detach(tr);
		});
		
		Logger::Info(SECTION_NAME, L"Thread ID: %d", t1.get_id());
		t1.detach();

		auto t2 = thread([]() {
			auto tr = il2cpp_thread_attach(il2cpp_domain_get());
			Update();
			il2cpp_thread_detach(tr);
		});
		Logger::Info(SECTION_NAME, L"Thread ID: %d", t2.get_id());
		t2.detach();
	}
}