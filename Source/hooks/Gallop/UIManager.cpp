#include "UIManager.h"

using namespace Unity;
using namespace UnityEngine::CoreModule;
using namespace UnityEngine::UI;

namespace Gallop::UIManager
{
	void* (*GetCanvasScalerList)(void*);

	void* change_resize_ui_for_pc_orig;
	void change_resize_ui_for_pc_hook(void* _this, int width, int height)
	{
		float scale = Settings::Global->uiScale;
		Resolution_t r;
		get_resolution_stub(&r);

		if (Settings::Global->forceLandscape && (Settings::Global->uiScale > 0.5))
			scale = Settings::Global->uiScale - 0.5;



		reinterpret_cast<decltype(change_resize_ui_for_pc_hook)*>(change_resize_ui_for_pc_orig)(_this, width, height);

		const auto canvasScalerList = GetCanvasScalerList(_this);
		il2cpp_symbols::iterate_IEnumerable(canvasScalerList, [&](void* canvasScaler)
			{
				set_scaleFactor(canvasScaler, max(1.0f, r.width / 1920.f) * scale);
			});



	}

	void Init() 
	{
		auto ChangeResizeUIForPC_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"UIManager", "ChangeResizeUIForPC", 2
		);
		//EnableHook(ChangeResizeUIForPC_addr, &change_resize_ui_for_pc_hook, &change_resize_ui_for_pc_orig, L"Gallop_UIManager_ChangeResizeUIForPC");

		GetCanvasScalerList = reinterpret_cast<decltype(GetCanvasScalerList)>(il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"UIManager", "GetCanvasScalerList", -1
		));
	}
}