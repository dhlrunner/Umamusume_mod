#include "Cyan.Loader.h"

using namespace std;
//namespace fs = std::filesystem;
namespace Cyan::Loader::AssetLoader
{
	void* LoadOne_orig;
	bool LoadOne_hook(Il2CppObject* _this, void* handle, AssetRequest* request) {
		//printf("LoadOne Hook\n");
		//il2cpp_unha
		//Il2CppString* ()();
		//
		// wchar_t* basePath = unityengine_get_persistentDataPath_hook()->start_char;
		//wprintf(L"Base=%s\n", unityengine_get_persistentDataPath_addr()->start_char);
		//wprintf(L"Path=%s\n", request->path->start_char);
		wstring modFullPath(wstring(UnityEngine::Application::get_persistentDataPath_hook()->chars) + L"/dat_mod/" + wstring(request->path->chars));

		//wprintf(L"Modded full path=%s\n", modFullPath.c_str());
		if (std::filesystem::is_regular_file(modFullPath)) {
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

	void* Exists_orig;
	bool Exists_hook(Il2CppObject* _this, Il2CppString* path, bool isLowerCase) {
		bool ret = reinterpret_cast<decltype(Exists_hook)*>(Exists_orig)(_this, path, isLowerCase);
		//Logger::Info(SECTION_NAME, L"Exists_hook: path=%s ret=%d", path->chars, ret);
		if (!ret) {
			wstring modFullPath(wstring(UnityEngine::Application::get_persistentDataPath_hook()->chars) + L"/dat_mod/" + path->chars);
			if (std::filesystem::is_regular_file(modFullPath)) {
				Logger::Info(SECTION_NAME, L"Exists modded asset : %s", modFullPath.c_str());
				
				return true;
			}
		}
		return ret;
	}

	void* GetOrCreateLoadRequests_orig;
	Il2CppArray* GetOrCreateLoadRequests_hook(Il2CppObject* _this, Il2CppString* path, bool isLowerCase, bool createTutorialAssetRequest) {
		//Logger::Info(SECTION_NAME, L"GetOrCreateLoadRequests_hook: path=%s", path->chars);
		auto ret = reinterpret_cast<decltype(GetOrCreateLoadRequests_hook)*>(GetOrCreateLoadRequests_orig)(_this, path, isLowerCase, createTutorialAssetRequest);

		if (ret == nullptr) {
			wstring modFullPath(wstring(UnityEngine::Application::get_persistentDataPath_hook()->chars) + L"/dat_mod/" + path->chars);
			if (std::filesystem::is_regular_file(modFullPath)) {
				Logger::Info(SECTION_NAME, L"Exists modded asset : %s, creating new AssetRequests", modFullPath.c_str());

				Il2CppArraySize_t<Il2CppObject*>* arr =
					il2cpp_array_new_type<Il2CppObject*>(
						il2cpp_symbols::get_global_class("_Cyan.dll", "AssetRequest"),
						1
					);

				Il2CppObject* newRequest = il2cpp_object_new(il2cpp_symbols::get_global_class("_Cyan.dll", "AssetRequest"));
				char kind = 0;
				char state = 1;
				Il2CppString* hname = il2cpp_string_new_utf16(L"aaa", 0);

				il2cpp_field_set_value(newRequest, il2cpp_class_get_field_from_name(newRequest->klass, "kind"), &kind);
				il2cpp_field_set_value(newRequest, il2cpp_class_get_field_from_name(newRequest->klass, "state"), &state);
				il2cpp_field_set_value(newRequest, il2cpp_class_get_field_from_name(newRequest->klass, "hname"), hname);
				il2cpp_field_set_value(newRequest, il2cpp_class_get_field_from_name(newRequest->klass, "path"), path);

				il2cpp_array_setref(arr, 0, newRequest);

				//remove from missingNames list
				auto missingNames = reinterpret_cast<Il2CppObject*>(
					il2cpp_field_get_value_object(
						il2cpp_class_get_field_from_name(_this->klass, "missingNames"),
						_this
					)
					);

				//Excute 
				//excute .Remove()
				auto result = il2cpp_class_get_method_from_name_type<bool(*)(Il2CppObject*, Il2CppString* ,const MethodInfo*)>(missingNames->klass, "Remove", 1)->methodPointer(
					missingNames,
					path,
					il2cpp_class_get_method_from_name(missingNames->klass, "Remove", 1)
				);

				if (result) {
					Logger::Info(SECTION_NAME, L"Removed %s from missingNames", path->chars);
				}
				else {
					Logger::Info(SECTION_NAME, L"%s not found in missingNames", path->chars);
				}

				return arr;
				
			}
		}
		return ret;
	}

	void Init() 
	{
		Logger::Info(SECTION_NAME, L"Init");
		auto LoadOne_addr = reinterpret_cast<bool(*)(void*, AssetRequest*)>(il2cpp_symbols::get_method_pointer(
			"_Cyan.dll", "Cyan.Loader",
			"AssetLoader", "LoadOne", 2
		));
		EnableHook(LoadOne_addr, &LoadOne_hook, &LoadOne_orig, L"LoadOne");

		auto Exists_addr = reinterpret_cast<bool(*)(void*, Il2CppString*, bool)>(il2cpp_symbols::get_method_pointer(
			"_Cyan.dll", "Cyan.Loader",
			"AssetLoader", "Exists", 2
		));
		EnableHook(Exists_addr, &Exists_hook, &Exists_orig, L"Exists");

		auto GetOrCreateLoadRequests_addr = reinterpret_cast<Il2CppArray * (*)(void*, Il2CppString*, bool)>(il2cpp_symbols::get_method_pointer(
			"_Cyan.dll", "Cyan.Loader",
			"AssetLoader", "GetOrCreateLoadRequests", 3
		));
		EnableHook(GetOrCreateLoadRequests_addr, &GetOrCreateLoadRequests_hook, &GetOrCreateLoadRequests_orig, L"GetOrCreateLoadRequests");
	}
}