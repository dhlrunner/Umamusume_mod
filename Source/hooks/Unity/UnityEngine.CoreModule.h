#pragma once

#include "../../Global.h"
#include "..\..\tools\Logger.hpp"
#include <winhttp.h>
#include "../GallopDialogUtil.h"
#include "il2cpp\il2cpp_symbols.hpp"
#include "il2cpp\il2cpp-tabledefs.h"
#include "il2cpp/il2cpp-tools.hpp"
#include "..\..\Settings.h"
#include "..\..\Utils.h"
#include "..\hook-helper.h"
#include "UnityStructs.h"
#include "../Gallop/StandaloneWindowResize.h"
//#include "../rapidjson/document.h"

#include <thread>
#include <numeric>

#pragma comment(lib, "winhttp.lib")

#define SECTION_NAME L"UNITY_CORE"

using namespace Unity;

namespace UnityEngine::CoreModule
{

	typedef Il2CppObject* (*GameObject_get_transform_t)(void* gameObject);
	typedef Il2CppString* (*GameObject_get_name_t)(void* gameObject);
	typedef bool (*GameObject_get_activeSelf_t)(void* gameObject);
	typedef void (*GameObject_SetActive_t)(void* gameObject, bool value);

	typedef int (*Transform_get_childCount_t)(void* transform);
	typedef Il2CppObject* (*Transform_GetChild_t)(void* transform, int index);
	typedef Il2CppObject* (*Transform_get_parent_t)(void* transform);

	typedef Il2CppArraySize_t<Il2CppObject*>* (*SceneManager_GetActiveScene_GetRootGameObjects_t)();
	typedef Il2CppArraySize_t<Il2CppObject*>* (*Scene_GetRootGameObjects_t)(void* scene);
	typedef Il2CppObject* (*SceneManager_GetActiveScene_t)();
	typedef Il2CppObject* (*Transform_get_gameObject_t)(void* transform);

	extern Il2CppString* (*GetGraphicsDeviceName)();
	extern void* (*GameObject_Find)(Il2CppString*);
	extern void (*LoadScene)(Il2CppString*, LoadSceneParameters*);
	extern void (*set_TimeScale)(float);
	extern float (*get_TimeScale)();

	extern GameObject_get_transform_t GameObject_get_transform;
	extern GameObject_get_name_t GameObject_get_name;
	extern GameObject_get_activeSelf_t GameObject_get_activeSelf;
	extern Transform_get_childCount_t Transform_get_childCount;
	extern Transform_GetChild_t Transform_GetChild;
	extern Transform_get_parent_t Transform_get_parent;
	extern Scene_GetRootGameObjects_t Scene_GetRootGameObjects;
	extern SceneManager_GetActiveScene_t SceneManager_GetActiveScene;
	extern Transform_get_gameObject_t Transform_get_gameObject;

	void ResetGame();
	void GameObject_SetActive(const char* path, bool value);
	void GameObject_SetActive(Il2CppObject* _this, bool enable);
	void Screen_set_orientation_hook(ScreenOrientation orientation);
	void Init();
	void adjustScreenSize(int w = 0, int h = 0);
	void get_resolution_stub(Resolution_t* r);
	void set_antiAliasing_hook(int value);


}