#include "CameraController.h"

namespace Gallop::CameraController 
{
	void* GetCanvasSize_orig = nullptr;
	Unity::Vector2_t GetCanvasSize_hook(void* _this) {
		auto ret = reinterpret_cast<decltype(GetCanvasSize_hook)*>(GetCanvasSize_orig)(_this);
		Logger::Info(SECTION_NAME, L"GetCanvasSize: %f, %f", ret.x, ret.y);
		if (Settings::Global->virtualResolutionMultiple != 1.0f) {
			ret.x /= Settings::Global->virtualResolutionMultiple;
			ret.y /= Settings::Global->virtualResolutionMultiple;
		}
		return ret;
	}

	void Init()
	{
		Logger::Info(SECTION_NAME, L"Init");
		auto GetCanvasSize_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"CameraController", "GetCanvasSize", 0
		);
		EnableHook(GetCanvasSize_addr, &GetCanvasSize_hook, &GetCanvasSize_orig, L"GetCanvasSize");
	}
}