#include "Cyan.Loader.h"

using namespace std;
//namespace fs = std::filesystem;
namespace Cyan::Loader::AssetLoader
{
	void* LoadOne_orig;
	bool LoadOne_hook(Il2CppObject* _this, void* handle, AssetRequest* request) {
		//printf("LoadOne Hook\n");

		//Il2CppString* ()();
		//
		// wchar_t* basePath = unityengine_get_persistentDataPath_hook()->start_char;
		//wprintf(L"Base=%s\n", unityengine_get_persistentDataPath_addr()->start_char);
		//wprintf(L"Path=%s\n", request->path->start_char);
		wstring modFullPath(wstring(UnityEngine::Application::get_persistentDataPath_hook()->chars) + L"/dat_mod/" + wstring(request->path->chars));

		//wprintf(L"Modded full path=%s\n", modFullPath.c_str());
		if (std::filesystem::exists(modFullPath)) {
			Logger::Info(SECTION_NAME, L"Loaded modded asset : %s", modFullPath.c_str());

			auto setAssetBundle = reinterpret_cast<void (*)(
				void* _this, void* assetBundle)>(il2cpp_symbols::get_method_pointer(
					"_Cyan.dll", "Cyan.Loader", "AssetHandle", "SetAssetBundle",
					1));

			auto get_IsLoaded = reinterpret_cast<bool(*)(
				void* _this)>(il2cpp_symbols::get_method_pointer(
					"_Cyan.dll", "Cyan.Loader", "AssetHandle", "get_IsLoaded",
					0));

			void* asset = UnityEngine::AssetBundle::LoadInternal(il2cpp_string_new_utf16(modFullPath.c_str(), modFullPath.length()), 0, 0);

			Logger::Info(SECTION_NAME, L"New assetBundle ptr=0x%p", asset);
			setAssetBundle(handle, asset);
			return get_IsLoaded(handle);

		}

		//wprintf(L"hash=%s\n", request->hname->start_char);
		//wprintf(L"path=%s\n", request->path->start_char);

		return reinterpret_cast<decltype(LoadOne_hook)*>(LoadOne_orig)(_this, handle, request);
	}

	void Init() 
	{
		Logger::Info(SECTION_NAME, L"Init");
		auto LoadOne_addr = reinterpret_cast<bool(*)(void*, AssetRequest*)>(il2cpp_symbols::get_method_pointer(
			"_Cyan.dll", "Cyan.Loader",
			"AssetLoader", "LoadOne", 2
		));
		EnableHook(LoadOne_addr, &LoadOne_hook, &LoadOne_orig, L"LoadOne");
	}
}