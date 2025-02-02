#include "GraphicSettings.h"

namespace Gallop::GraphicSettings
{
	void* ApplyGraphicsQuality_orig = nullptr;
	void ApplyGraphicsQuality_hook(Il2CppObject* thisObj, int quality, bool force) {
		Logger::Info(SECTION_NAME, L"setGraphicsQuality: %d -> %d", quality, Settings::Local->graphics_quality);
		return reinterpret_cast<decltype(ApplyGraphicsQuality_hook)*>(ApplyGraphicsQuality_orig)(thisObj,
			Settings::Local->graphics_quality == -1 ? quality : Settings::Local->graphics_quality,
			true);
	}

	void* GetVirtualResolution3D_orig;
	Unity::Vector2_Int_t GetVirtualResolution3D_hook(void* _this, bool isForcedWideAspect) {
		auto ret = reinterpret_cast<decltype(GetVirtualResolution3D_hook)*>(GetVirtualResolution3D_orig)(_this, isForcedWideAspect);
		//printf("GetVirtualResolution3D: %d, %d\n\n\n", ret.m_X, ret.m_Y);
		if (!Global::settingUpImageEffect && (Settings::Global->virtualResolutionMultiple != 1.0f)) {
			ret.m_X *= Settings::Global->virtualResolutionMultiple;
			ret.m_Y *= Settings::Global->virtualResolutionMultiple;
		}
		return ret;
	}

	void* GetVirtualResolution_orig;
	Unity::Vector2_t GetVirtualResolution_hook(void* _this) {
		auto ret = reinterpret_cast<decltype(GetVirtualResolution_hook)*>(GetVirtualResolution_orig)(_this);
		//printf("GetVirtualResolution: %d, %d\n", ret.x, ret.y);
		if (Settings::Global->virtualResolutionMultiple != 1.0f) {
			ret.x *= Settings::Global->virtualResolutionMultiple;
			ret.y *= Settings::Global->virtualResolutionMultiple;
		}
		return ret;
	}

	void* GetVirtualResolutionWidth3D_orig;
	int GetVirtualResolutionWidth3D_hook(void* _this) {
		auto ret = reinterpret_cast<decltype(GetVirtualResolutionWidth3D_hook)*>(GetVirtualResolutionWidth3D_orig)(_this);
		//printf("GetVirtualResolutionWidth3D: %d\n", ret);
		if (Settings::Global->virtualResolutionMultiple != 1.0f) {
			ret *= Settings::Global->virtualResolutionMultiple;
		}
		return ret;
	}

	void Init()
	{
		Logger::Info(SECTION_NAME, L"Init");
		auto ApplyGraphicsQuality_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"GraphicSettings", "ApplyGraphicsQuality", 2);
		EnableHook(ApplyGraphicsQuality_addr, &ApplyGraphicsQuality_hook, &ApplyGraphicsQuality_orig, L"ApplyGraphicsQuality");

		auto GetVirtualResolution3D_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"GraphicSettings", "GetVirtualResolution3D", 1
		);
		EnableHook(GetVirtualResolution3D_addr, &GetVirtualResolution3D_hook, &GetVirtualResolution3D_orig, L"GetVirtualResolution3D");

		auto GetVirtualResolution_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"GraphicSettings", "GetVirtualResolution", 0
		);
		EnableHook(GetVirtualResolution_addr, &GetVirtualResolution_hook, &GetVirtualResolution_orig, L"GetVirtualResolution");

		auto GetVirtualResolutionWidth3D_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"GraphicSettings", "GetVirtualResolutionWidth3D", 0
		);
		EnableHook(GetVirtualResolutionWidth3D_addr, &GetVirtualResolutionWidth3D_hook, &GetVirtualResolutionWidth3D_orig, L"GetVirtualResolutionWidth3D");


	}
}