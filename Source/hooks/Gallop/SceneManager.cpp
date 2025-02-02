#include "SceneManager.h"

namespace Gallop::SceneManager
{
	void* LoadScene_orig = nullptr;
	void* LoadScene_hook(void* _this, int sceneId) {
		//currSceneID = sceneId;
		Logger::Info(SECTION_NAME, L"LoadScene id=%d", sceneId);

		if (Settings::Global->forceLandscape && (sceneId == 1)) {
			auto ienum = new il2cpp::IEnumerator(reinterpret_cast<Il2CppObject * (*)()>(il2cpp_symbols::get_method_pointer(
				"umamusume.dll",
				"Gallop",
				"Screen", "ChangeScreenOrientationLandscapeAsync", -1))());
			
			ienum->MoveNext();

			UnityEngine::CoreModule::Screen_set_orientation_hook(ScreenOrientation::Landscape);
			Gallop::Screen::ChangeScreenOrientation_hook(ScreenOrientation::Landscape, true);
			//printf("Boot_Awake runned\n");
			//landscape();
		}


		//rpc->setScene(sceneId);

		if (!Settings::Global->isTapEffectEnabled) {
			UnityEngine::CoreModule::GameObject_SetActive("Gallop.GameSystem/SystemManagerRoot/SystemSingleton/UIManager/SystemCanvas/TapEffectCanvas", false);
		}
		return reinterpret_cast<decltype(LoadScene_hook)*>(LoadScene_orig)(_this, sceneId);
	}

	void* LoadView_orig = nullptr;
	void* LoadView_hook(int viewId) 
	{
		//printf("LoadView id=%d\n", viewId);
		return reinterpret_cast<decltype(LoadView_hook)*>(LoadView_hook)(viewId);
	}

	void* ChangeView_orig = nullptr;
	void ChangeView_hook(
		void* _this, 
		int nextViewId, 
		void* viewInfo, 
		Il2CppDelegate* callbackOnChangeViewCancel,
		Il2CppDelegate* callbackOnChangeViewAccept,
		bool forceChange)
	{
		Logger::Info(SECTION_NAME, L"ChangeView nextViewId=%d", nextViewId);
		return reinterpret_cast<decltype(ChangeView_hook)*>(ChangeView_hook)(_this, nextViewId, viewInfo, callbackOnChangeViewCancel, callbackOnChangeViewAccept, forceChange);
	}

	void Init()
	{
		Logger::Info(SECTION_NAME, L"Init");

		auto LoadScene_addr = reinterpret_cast<void* (*)(void*, int)>(il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"SceneManager", "LoadScene", 1
		));
		EnableHook(LoadScene_addr, &LoadScene_hook, &LoadScene_orig, L"SceneManager_LoadScene");

		auto LoadView_addr = reinterpret_cast<void* (*)(int)>(il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"SceneManager", "LoadView", 1
		));
		//EnableHook(LoadView_addr, &LoadView_hook, &LoadView_orig, L"SceneManager_LoadView");


		auto ChangeView_addr = reinterpret_cast<void (*)(void*, int, void*, Il2CppDelegate*, Il2CppDelegate*, bool) > (il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"SceneManager", "ChangeView", 5
		));
		//EnableHook(ChangeView_addr, &ChangeView_hook, &ChangeView_orig, L"SceneManager_ChangeView");
	}
}