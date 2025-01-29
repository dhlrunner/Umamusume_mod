#include "BackgroundWorker.h"

using namespace std;
using namespace UnityEngine::InputLegacyModule;
using namespace UnityEngine::CoreModule;
using namespace Global;

namespace BackgroundWorker
{
	void ResetGame() {
		LoadSceneParameters p = { 0 };
		p.LoadSceneMode = 0; //Single
		p.LocalPhysicsMode = 0;
		LoadScene(il2cpp_string_new(string("_Boot").data()), &p);
	}

	void keyDownCheckThread() {
		printf("KeyDownCheckThread IN!!!\n");

		while (true) {
			bool ret = GetKeyDown(KeyCode::S); //S
			bool ctrl = GetKey(KeyCode::LeftControl); //LCtrl
			bool alt = GetKey(KeyCode::LeftAlt);
			bool f12 = GetKeyDown(KeyCode::F12);
			bool f10 = GetKeyDown(KeyCode::F10);
			bool f11 = GetKeyDown(KeyCode::F11);
			bool f9 = GetKeyDown(KeyCode::F9);
			if (ret) {
				printf("S is Pressed!!!!\n");
				while (GetKeyDown(KeyCode::S)) {}

				Settings::Local->stopLiveCam = !Settings::Local->stopLiveCam;
				printf("LiveCam Stop %s.\n", Settings::Local->stopLiveCam ? "Enabled" : "Disabled");
				if (Settings::Local->stopLiveCam) {
					//toastImGui = true;
					//toastMessage = (char*)"라이브 카메라를 정지했습니다.";
					GallopDialog::ShowToast(L"라이브 카메라를 정지했습니다.");
				}
				else {
					//toastImGui = true;
					//toastMessage = (char*)"라이브 카메라를 다시 움직입니다.";
					GallopDialog::ShowToast(L"라이브 카메라를 다시 움직입니다.");
				}

			}
			if (ctrl) {
				printf("LCtrl is pressed!!!!!\n");
				while (ctrl) {
					//printf("check R\n");
					if (GetKeyDown(KeyCode::R)) {
						printf("Lctrl + R pressed, reset game\n");
						ResetGame();
						while (GetKey(KeyCode::R));
						break;
					} //R
					else if (GetKeyDown(KeyCode::P)) { //P
						if (get_TimeScale() <= 0.0) {
							set_TimeScale(1.0);
						}
						else {
							set_TimeScale(0.0);
						}
						printf("Lctrl + P pressed, Set game TimeScale to %.2f\n", get_TimeScale());
						while (GetKey(KeyCode::P));
						break;
					}
					else if (GetKey(KeyCode::PageUp)) {
						set_TimeScale(get_TimeScale() + 0.05);
						printf("Set Timescale %.2f\n", get_TimeScale());
						Sleep(100);
						//while (GetKey(KeyCode::PageUp));
						//break;
					}
					else if (GetKey(KeyCode::PageDown)) {
						set_TimeScale(get_TimeScale() - 0.05);
						printf("Set Timescale %.2f\n", get_TimeScale());
						Sleep(100);
						//while (GetKey(KeyCode::PageDown));
						//break;
					}
					else if (GetKeyDown(KeyCode::End)) {
						set_TimeScale(1.0);
						printf("Reset Timescale to %.2f\n", get_TimeScale());
						//toastImGui = true;
						//toastMessage = (char*)"배속을 1.0으로 초기화했습니다.";
						GallopDialog::ShowToast(L"배속을 1.0으로 초기화했습니다.");
						while (GetKey(KeyCode::PageDown));
						break;
					}
					else if (GetKey(KeyCode::LeftArrow)) {
						if (!Settings::Local->isLiveTimeManual) {
							Settings::Local->isLiveTimeManual = true;
							//toastImGui = true;
							//toastMessage = (char*)"라이브 타임라인 수동 조작이 활성화 되었습니다.";
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
					else if (GetKey(KeyCode::RightArrow)) {
						if (!Settings::Local->isLiveTimeManual) {
							Settings::Local->isLiveTimeManual = true;
							//toastImGui = true;
							//toastMessage = (char*)"라이브 타임라인 수동 조작이 활성화 되었습니다.";
							GallopDialog::ShowToast(L"라이브 타임라인 수동 조작이 활성화 되었습니다.");
						}
						liveTimeSec = liveTimeSec + liveTimelineManualScale;
						printf("set liveTime Second to %.4f\n", liveTimeSec);
						Sleep(1);
					}
					ctrl = GetKey(KeyCode::LeftControl);
				}
			}
			if (f12) {
				printf("F12 is Pressed!!!!\n");
				while (GetKeyDown(KeyCode::F12)) {}
				GallopDialog::ShowToast(L"F12 is Pressed!!!!");
				//bool b = ShowWindow(imguiWnd, imguiShow ? SW_HIDE : SW_SHOW);
				//imguiShow = !imguiShow;
				imgui_settingwnd_open = !imgui_settingwnd_open;
				printf("Show setting screen \n");
			}
			if (f10) {
				printf("F10 is Pressed!!!!\n");
				while (GetKeyDown(KeyCode::F10)) {}
				Settings::Global->isShowLivePerfInfo = !Settings::Global->isShowLivePerfInfo;
				//printf("%d\n", Settings::Global->isShowLivePerfInfo);
			}
			if (f11) {
				printf("F11 is Pressed!!!!\n");
				while (GetKeyDown(KeyCode::F11)) {}
				Settings::Global->isShowLiveFPSGraph = !Settings::Global->isShowLiveFPSGraph;
			}
			if (f9) {
				while (GetKeyDown(KeyCode::F9)) {}
				Settings::Local->isLiveTimeManual = !Settings::Local->isLiveTimeManual;
				if(Settings::Local->isLiveTimeManual)
					GallopDialog::ShowToast(L"라이브 타임라인 수동 조작이 활성화 되었습니다.");
				else
					GallopDialog::ShowToast(L"라이브 타임라인 수동 조작이 비활성화 되었습니다.");
			}
			/*else if (alt) {
				printf("LAlt is pressed!!!!!\n");
				while (alt) {

					alt = GetKey(KeyCode::LeftAlt);
				}

			}*/
			//std::this_thread::sleep_for(std::chrono::milliseconds(5));
			if (gameTerminating) 
			{
				Logger::Info(SECTION_NAME, L"Game Terminating.. Exit loop");
				break;
			}
		}
	}

	void Init()
	{
		Logger::Info(SECTION_NAME, L"Init");
		Logger::Info(SECTION_NAME, L"Starting thread");

		auto t = thread([]() {
			auto tr = il2cpp_thread_attach(il2cpp_domain_get());
			keyDownCheckThread();
			il2cpp_thread_detach(tr);
		});
		
		Logger::Info(SECTION_NAME, L"Thread ID: %d", t.get_id());
		t.detach();

	}
}