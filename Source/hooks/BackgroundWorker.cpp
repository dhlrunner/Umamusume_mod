#include "BackgroundWorker.h"

using namespace std;
using namespace UnityEngine::InputLegacyModule;
using namespace UnityEngine::CoreModule;
using namespace Global;

namespace BackgroundWorker
{
	

	void keyDownCheckThread() {
		Logger::Debug(SECTION_NAME, L"KeyDownCheckThread IN!!!");

		while (true) {
			bool ret = GetKeyDown(KeyCode::S); //S
			bool ctrl = GetKey(KeyCode::LeftControl); //LCtrl
			bool alt = GetKey(KeyCode::LeftAlt);
			bool f12 = GetKeyDown(KeyCode::F12);
			bool f10 = GetKeyDown(KeyCode::F10);
			bool f11 = GetKeyDown(KeyCode::F11);
			bool f9 = GetKeyDown(KeyCode::F9);
			bool f8 = GetKeyDown(KeyCode::F8);
			bool f7 = GetKeyDown(KeyCode::F7);
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
				/*auto dialog = GallopDialog::ShowTextDialog(L"Test", L"Close in 3 sec", false);
				Sleep(1000);
				GallopDialog::SetDialogMessage(dialog, L"Close in 2 sec");
				Sleep(1000);
				GallopDialog::SetDialogMessage(dialog, L"Close in 1 sec");
				Sleep(1000);
				GallopDialog::CloseDialog(dialog);*/
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
			if (f8) {
				printf("Dump il2cpp start");
				while (GetKeyDown(KeyCode::F8)) {}
				auto dialog = GallopDialog::ShowTextDialog(L"Dump il2cpp", L"Please wait...", false);
				auto h = GetModuleHandle(L"GameAssembly.dll");
				GallopDialog::SetDialogMessage(dialog, L"Dumping GameAssembly.dll ...");
				pedump(h, "umamusume.exe.local\\GameAssembly.dumped.dll");
				il2cpp_dump(dialog);
				Sleep(1000);
				GallopDialog::CloseDialog(dialog);
			}
			if (f7) {
				while (GetKeyDown(KeyCode::F7)) {}
				//auto c = il2cpp_symbols::get_class("umamusume.dll", "Gallop", "StaticVariableDefine/Data/SQLiteSaveLoadHelper");
				////il2cpp_runtime_object_init(c);
				//printf("SQLiteSaveLoadHelper = %p\n", c);
				//FieldInfo* keyField = il2cpp_class_get_field_from_name(c->klass, "ENCODE_KEY_ARRAY");
				//Il2CppArraySize_t<unsigned char>* ENCODE_KEY_ARRAY;
				//il2cpp_field_static_get_value(keyField, &ENCODE_KEY_ARRAY);
				////il2cpp_field_static_get_value
				//printf("byte[] ENCODE_KEY_ARRAY = { ");
				//for (int i = 0; i < ENCODE_KEY_ARRAY->max_length; i++) {
				//	printf("%d,", ENCODE_KEY_ARRAY->vector[i]);
				//}
				//printf(" };\n");
				auto get_masterCharaData = reinterpret_cast<Il2CppObject * (*)(Il2CppObject * _this)>(il2cpp_symbols::get_method_pointer("umamusume.dll", "Gallop", "MasterDataManager", "get_masterCharaData", 0));
				auto masterCharaData = get_masterCharaData(il2cpp::GetSingletonInstance(il2cpp_symbols::get_class("umamusume.dll", "Gallop", "MasterDataManager")));
				//auto Get = reinterpret_cast<Il2CppObject * (*)(Il2CppObject * _this, int id)>(il2cpp_symbols::get_method_pointer("umamusume.dll", "Gallop", "MasterCharaData", "Get", 1));
				//Logger::Debug(SECTION_NAME, L"Get ptr=%p", Get);
				//auto d = Get(masterCharaData, 1001);
				//auto name = il2cpp_class_get_method_from_name_type<Il2CppString * (*)(Il2CppObject * _this)>(d->klass, "get_Name", 0)->methodPointer(d);
				Il2CppDictionary<int, Il2CppObject*>* dict = il2cpp_class_get_method_from_name_type<Il2CppDictionary<int, Il2CppObject*> * (*)(Il2CppObject * _this)>(masterCharaData->klass, "get_dictionary", 0)->methodPointer(masterCharaData);
				for (int i = 0; i < dict->count; i++) {
					auto name = il2cpp_class_get_method_from_name_type<Il2CppString * (*)(Il2CppObject * _this)>(dict->get_Values()[i]->klass, "get_Name", 0)->methodPointer(dict->get_Values()[i]);
					int id;
					il2cpp_field_get_value(dict->get_Values()[i],il2cpp_class_get_field_from_name(dict->get_Values()[i]->klass, "Id"), &id);
					wprintf(L"MasterCharaData_CharaData test name=%S, id=%d\n", Utils::ConvertWstringToUTF8(name->chars).c_str(), id);
				}
				
				//Il2CppString* name = get_Name(d);
				//wprintf(L"MasterCharaData_CharaData test name=%S\n", Utils::ConvertWstringToUTF8( name->chars).c_str());
				//MessageBoxW(0, name->chars, L"", 0);
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
				Logger::Debug(SECTION_NAME, L"Game Terminating.. Exit loop");
				break;
			}
		}
	}

	void Update() 
	{
		Logger::Debug(SECTION_NAME, L"Update thread in");
		while (!gameTerminating) {

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