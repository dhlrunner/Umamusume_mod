#include "ResourceManager.h"

namespace Gallop::ResourceManager
{
	void* Load_orig;
	//private T Load<T>(string path, int hash, bool isLowerCase = false) where T : UnityEngine.Object
	Il2CppObject* Load_hook(Il2CppObject* _this, Il2CppString* path, int hash, bool isLowerCase) {
		Logger::Info(SECTION_NAME, L"ResourceManager::Load_hook: path=%s hash=%d isLowerCase=%d type=%s", path->chars, hash, isLowerCase);
		Il2CppObject* ret = reinterpret_cast<decltype(Load_hook)*>(Load_orig)(_this, path, hash, isLowerCase);
		/*if (ret == nullptr) {
			wstring modFullPath(wstring(UnityEngine::Application::get_persistentDataPath_hook()->chars) + L"/dat_mod/" + wstring(path->chars));
			if (std::filesystem::is_regular_file(modFullPath)) {
				Logger::Info(SECTION_NAME, L"Loading modded asset : %s", modFullPath.c_str());
				ret = UnityEngine::Resources::Load(il2cpp_string_new_utf16(modFullPath.c_str(), modFullPath.length()), type);
				if (ret != nullptr) {
					Logger::Info(SECTION_NAME, L"Loaded modded asset : %s", modFullPath.c_str());
				}
				else {
					Logger::Error(SECTION_NAME, L"Failed to load modded asset : %s", modFullPath.c_str());
				}
			}
		}*/
		return ret;
	}

	//public static bool LoadAssetBundle
	void* LoadAssetBundle_orig = nullptr;
	bool LoadAssetBundle_hook(Il2CppString* path) {
		Logger::Info(SECTION_NAME, L"ResourceManager::LoadAssetBundle_hook: path=%s", path->chars);
		bool ret = reinterpret_cast<decltype(LoadAssetBundle_hook)*>(LoadAssetBundle_orig)(path);
		return ret;
	}

	//public static bool IsExistInAssetBundle(string filePath, bool isLowerCase = false)
	void* IsExistInAssetBundle_orig = nullptr;
	bool IsExistInAssetBundle_hook(Il2CppString* filePath, bool isLowerCase) {
		//Logger::Info(SECTION_NAME, L"ResourceManager::IsExistInAssetBundle_hook: filePath=%s isLowerCase=%d", filePath->chars, isLowerCase);
		bool ret = reinterpret_cast<decltype(IsExistInAssetBundle_hook)*>(IsExistInAssetBundle_orig)(filePath, isLowerCase);
		return ret;
	}

	//public static bool IsExistLocalFile(string filePath)
	void* IsExistLocalFile_orig = nullptr;
	bool IsExistLocalFile_hook(Il2CppString* filePath) {
		Logger::Info(SECTION_NAME, L"ResourceManager::IsExistLocalFile_hook: filePath=%s", filePath->chars);
		bool ret = reinterpret_cast<decltype(IsExistLocalFile_hook)*>(IsExistLocalFile_orig)(filePath);
		return ret;
	}

	void Init() {
		Logger::Info(SECTION_NAME, L"Init");
		auto Load_addr = reinterpret_cast<Il2CppObject * (*)(Il2CppObject*, Il2CppString*, int, bool)>(il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"ResourceManager", "Load", 3
		));
		EnableHook(Load_addr, &Load_hook, &Load_orig, L"ResourceManager::Load");

		auto LoadAssetBundle_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"ResourceManager", "LoadAssetBundle", 1
		);
		EnableHook(LoadAssetBundle_addr, &LoadAssetBundle_hook, &LoadAssetBundle_orig, L"ResourceManager::LoadAssetBundle");

		auto IsExistInAssetBundle_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"ResourceManager", "IsExistInAssetBundle", 2
		);
		EnableHook(IsExistInAssetBundle_addr, &IsExistInAssetBundle_hook, &IsExistInAssetBundle_orig, L"ResourceManager::IsExistInAssetBundle");

		auto IsExistLocalFile_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"ResourceManager", "IsExistLocalFile", 1
		);
		EnableHook(IsExistLocalFile_addr, &IsExistLocalFile_hook, &IsExistLocalFile_orig, L"ResourceManager::IsExistLocalFile");
	}
}