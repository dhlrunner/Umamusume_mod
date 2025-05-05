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
				//auto get_masterCharaData = reinterpret_cast<Il2CppObject * (*)(Il2CppObject * _this)>(il2cpp_symbols::get_method_pointer("umamusume.dll", "Gallop", "MasterDataManager", "get_masterCharaData", 0));
				//auto masterCharaData = get_masterCharaData(il2cpp::GetSingletonInstance(il2cpp_symbols::get_class("umamusume.dll", "Gallop", "MasterDataManager")));
				////auto Get = reinterpret_cast<Il2CppObject * (*)(Il2CppObject * _this, int id)>(il2cpp_symbols::get_method_pointer("umamusume.dll", "Gallop", "MasterCharaData", "Get", 1));
				////Logger::Debug(SECTION_NAME, L"Get ptr=%p", Get);
				////auto d = Get(masterCharaData, 1001);
				////auto name = il2cpp_class_get_method_from_name_type<Il2CppString * (*)(Il2CppObject * _this)>(d->klass, "get_Name", 0)->methodPointer(d);
				//Il2CppDictionary<int, Il2CppObject*>* dict = il2cpp_class_get_method_from_name_type<Il2CppDictionary<int, Il2CppObject*> * (*)(Il2CppObject * _this)>(masterCharaData->klass, "get_dictionary", 0)->methodPointer(masterCharaData);
				//for (int i = 0; i < dict->count; i++) {
				//	auto name = il2cpp_class_get_method_from_name_type<Il2CppString * (*)(Il2CppObject * _this)>(dict->get_Values()[i]->klass, "get_Name", 0)->methodPointer(dict->get_Values()[i]);
				//	int id;
				//	il2cpp_field_get_value(dict->get_Values()[i],il2cpp_class_get_field_from_name(dict->get_Values()[i]->klass, "Id"), &id);
				//	wprintf(L"MasterCharaData_CharaData test name=%S, id=%d\n", Utils::ConvertWstringToUTF8(name->chars).c_str(), id);
				//}
				//
				//Il2CppString* name = get_Name(d);
				//wprintf(L"MasterCharaData_CharaData test name=%S\n", Utils::ConvertWstringToUTF8( name->chars).c_str());
				//MessageBoxW(0, name->chars, L"", 0);

				// 1. 필요한 클래스 참조를 얻음

				Il2CppClass* gameObjectClass = il2cpp_symbols::get_class("UnityEngine.CoreModule.dll", "UnityEngine", "GameObject");
				Il2CppClass* canvasClass = il2cpp_symbols::get_class("UnityEngine.UIModule.dll", "UnityEngine", "Canvas");
				Il2CppClass* canvasScalerClass = il2cpp_symbols::get_class("UnityEngine.UI.dll", "UnityEngine.UI", "CanvasScaler");
				Il2CppClass* graphicRaycasterClass = il2cpp_symbols::get_class("UnityEngine.UI.dll", "UnityEngine.UI", "GraphicRaycaster");
				Il2CppClass* textClass = il2cpp_symbols::get_class("UnityEngine.UI.dll", "UnityEngine.UI", "Text");
				Il2CppClass* rectTransformClass = il2cpp_symbols::get_class("UnityEngine.CoreModule.dll", "UnityEngine", "RectTransform");

				// 2. Canvas GameObject 생성 (생성자: GameObject(string name))
				void* ctorArgs[1];
				ctorArgs[0] = il2cpp_string_new("Canvas");
				Il2CppObject* canvasGO = il2cpp_object_new(gameObjectClass);
				const MethodInfo* gameObjectCtor = il2cpp_class_get_method_from_name(gameObjectClass, ".ctor", 1);
				il2cpp_runtime_invoke(gameObjectCtor, canvasGO, ctorArgs, nullptr);

				// 3. Canvas 및 관련 컴포넌트 추가 (AddComponent 호출 시 System.Type 전달)
				const MethodInfo* addComponentMethod = il2cpp_class_get_method_from_name(gameObjectClass, "AddComponent", 1);
				void* addArgs[1];

				// Canvas 추가
				const Il2CppType* canvasIl2CppType = il2cpp_class_get_type(canvasClass);
				Il2CppObject* canvasTypeObj = il2cpp_type_get_object(canvasIl2CppType);
				addArgs[0] = canvasTypeObj;
				Il2CppObject* canvasComponent = il2cpp_runtime_invoke(addComponentMethod, canvasGO, addArgs, nullptr);

				// CanvasScaler 추가
				const Il2CppType* scalerIl2CppType = il2cpp_class_get_type(canvasScalerClass);
				Il2CppObject* scalerTypeObj = il2cpp_type_get_object(scalerIl2CppType);
				addArgs[0] = scalerTypeObj;
				Il2CppObject* scalerComponent = il2cpp_runtime_invoke(addComponentMethod, canvasGO, addArgs, nullptr);

				// GraphicRaycaster 추가
				const Il2CppType* raycasterIl2CppType = il2cpp_class_get_type(graphicRaycasterClass);
				Il2CppObject* raycasterTypeObj = il2cpp_type_get_object(raycasterIl2CppType);
				addArgs[0] = raycasterTypeObj;
				Il2CppObject* raycasterComponent = il2cpp_runtime_invoke(addComponentMethod, canvasGO, addArgs, nullptr);

				// 4. Text GameObject 생성
				ctorArgs[0] = il2cpp_string_new("Text");
				Il2CppObject* textGO = il2cpp_object_new(gameObjectClass);
				il2cpp_runtime_invoke(gameObjectCtor, textGO, ctorArgs, nullptr);

				// 5. Text GameObject의 부모를 Canvas로 설정
				// 각 GameObject는 transform 컴포넌트를 가지므로 get_transform 호출
				const MethodInfo* getTransformMethod = il2cpp_class_get_method_from_name(gameObjectClass, "get_transform", 0);
				Il2CppObject* canvasTransform = il2cpp_runtime_invoke(getTransformMethod, canvasGO, nullptr, nullptr);
				Il2CppObject* textTransform = il2cpp_runtime_invoke(getTransformMethod, textGO, nullptr, nullptr);

				// textTransform.SetParent(canvasTransform) 호출 (SetParent는 Transform 클래스에 있으나 RectTransform 상속)
				const MethodInfo* setParentMethod = il2cpp_class_get_method_from_name(rectTransformClass, "SetParent", 1);
				void* setParentArgs[1];
				setParentArgs[0] = canvasTransform;
				il2cpp_runtime_invoke(setParentMethod, textTransform, setParentArgs, nullptr);

				// 6. Text 컴포넌트 추가 및 프로퍼티 설정
				const Il2CppType* textIl2CppType = il2cpp_class_get_type(textClass);
				Il2CppObject* textTypeObj = il2cpp_type_get_object(textIl2CppType);
				addArgs[0] = textTypeObj;
				Il2CppObject* textComponent = il2cpp_runtime_invoke(addComponentMethod, textGO, addArgs, nullptr);

				// 텍스트 문자열 설정: textComponent.text = "출력할 텍스트";
				const MethodInfo* setTextMethod = il2cpp_class_get_method_from_name(textClass, "set_text", 1);
				void* setTextArgs[1];
				setTextArgs[0] = il2cpp_string_new16(L"Test Text 출력할 텍스트");
				il2cpp_runtime_invoke(setTextMethod, textComponent, setTextArgs, nullptr);

				// 글자 크기 설정: textComponent.fontSize = 24;
				const MethodInfo* setFontSizeMethod = il2cpp_class_get_method_from_name(textClass, "set_fontSize", 1);
				int fontSize = 24;
				void* setFontSizeArgs[1] = { &fontSize };
				il2cpp_runtime_invoke(setFontSizeMethod, textComponent, setFontSizeArgs, nullptr);

				// 7. RectTransform을 통해 위치 및 크기 설정
				// GetComponent 호출 시에도 System.Type 객체를 사용해야 함
				const MethodInfo* getComponentMethod = il2cpp_class_get_method_from_name(gameObjectClass, "GetComponent", 1);
				//void* getComponentArgs[1];
				//const Il2CppType* rectTransformIl2CppType = il2cpp_class_get_type(rectTransformClass);
				//Il2CppObject* rectTransformTypeObj = il2cpp_type_get_object(rectTransformIl2CppType);
				//getComponentArgs[0] = rectTransformTypeObj;
				//Il2CppObject* rectTransform = il2cpp_runtime_invoke(getComponentMethod, textGO, getComponentArgs, nullptr);


				// 7. RectTransform을 통해 위치 및 크기 설정 (수정본)
				const Il2CppType* rectTransformIl2CppType = il2cpp_class_get_type(rectTransformClass);
				Il2CppObject* rectTransformTypeObj = il2cpp_type_get_object(rectTransformIl2CppType);
				void* getComponentArgs[1] = { rectTransformTypeObj };
				Il2CppObject* rectTransform = il2cpp_runtime_invoke(getComponentMethod, textGO, getComponentArgs, nullptr);

				// 앵커 최소값 설정: (0, 1) - 화면 좌측 상단
				const MethodInfo* setAnchorMinMethod = il2cpp_class_get_method_from_name(rectTransformClass, "set_anchorMin", 1);
				Vector2_t anchorMin = { 0.0f, 1.0f };
				void* setAnchorMinArgs[1] = { &anchorMin };
				il2cpp_runtime_invoke(setAnchorMinMethod, rectTransform, setAnchorMinArgs, nullptr);

				// 앵커 최대값 설정: (0, 1)
				const MethodInfo* setAnchorMaxMethod = il2cpp_class_get_method_from_name(rectTransformClass, "set_anchorMax", 1);
				Vector2_t anchorMax = { 0.0f, 1.0f };
				void* setAnchorMaxArgs[1] = { &anchorMax };
				il2cpp_runtime_invoke(setAnchorMaxMethod, rectTransform, setAnchorMaxArgs, nullptr);

				// 피벗 설정: (0, 1)
				const MethodInfo* setPivotMethod = il2cpp_class_get_method_from_name(rectTransformClass, "set_pivot", 1);
				Vector2_t pivot = { 0.0f, 1.0f };
				void* setPivotArgs[1] = { &pivot };
				il2cpp_runtime_invoke(setPivotMethod, rectTransform, setPivotArgs, nullptr);

				// 위치(anchoredPosition) 설정: (0, 0) - 앵커가 상단 왼쪽이므로 0,0이 캔버스 상단 왼쪽 위치임
				const MethodInfo* setAnchoredPosMethod = il2cpp_class_get_method_from_name(rectTransformClass, "set_anchoredPosition", 1);
				Vector2_t anchoredPos = { 0.0f, 0.0f };
				void* setAnchoredPosArgs[1] = { &anchoredPos };
				il2cpp_runtime_invoke(setAnchoredPosMethod, rectTransform, setAnchoredPosArgs, nullptr);

				// sizeDelta 설정 (원하는 크기에 맞게 조정)
				const MethodInfo* setSizeDeltaMethod = il2cpp_class_get_method_from_name(rectTransformClass, "set_sizeDelta", 1);
				Vector2_t sizeDelta = { 200.0f, 30.0f };
				void* setSizeDeltaArgs[1] = { &sizeDelta };
				il2cpp_runtime_invoke(setSizeDeltaMethod, rectTransform, setSizeDeltaArgs, nullptr);

				// textTransform을 최상위로 이동 (다른 UI 요소보다 앞쪽에 렌더링)
				const MethodInfo* setAsLastSiblingMethod = il2cpp_class_get_method_from_name(textTransform->klass, "SetAsLastSibling", 0);
				if (setAsLastSiblingMethod != nullptr) {
					il2cpp_runtime_invoke(setAsLastSiblingMethod, textTransform, nullptr, nullptr);
				}

				
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