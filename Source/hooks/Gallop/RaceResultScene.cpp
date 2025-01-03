#include "RaceResultScene.h"

namespace Gallop::RaceResultScene
{
	void* GetMotionVariationId_orig = nullptr;
	int GetMotionVariationId_hook(int charaId) {
		Logger::Info(SECTION_NAME, L"GetMotionVariationId : charaId=%d", charaId);
		if (Settings::Local->raceResultCutinMotionChara > -1) {
			charaId = Settings::Local->raceResultCutinMotionChara;
			//dress->CharaId = c_raceResultCutinMotionChara;
		}
		return reinterpret_cast<decltype(GetMotionVariationId_hook)*>
			(GetMotionVariationId_orig)(charaId);
	}

	void* PlayFinishOrderAnim_orig = nullptr;
	void PlayFinishOrderAnim_hook(void* _this, void* onPlayed) {
		Logger::Info(SECTION_NAME, L"RaceResultScene_PlayFinishOrderAnim called");
		return reinterpret_cast<decltype(PlayFinishOrderAnim_hook)*>
			(PlayFinishOrderAnim_orig)(_this, onPlayed);
	}


	void Init() {
		auto GetMotionVariationId_addr = reinterpret_cast<int(*)(int)>(
			il2cpp_symbols::get_method_pointer(
				"umamusume.dll", "Gallop",
				"RaceResultScene", "GetMotionVariationId", 1
			)
			);
		EnableHook(GetMotionVariationId_addr, &GetMotionVariationId_hook, &GetMotionVariationId_orig, L"GetMotionVariationId");

		auto PlayFinishOrderAnim_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"RaceResultScene", "PlayFinishOrderAnim", 1
		);
		EnableHook(PlayFinishOrderAnim_addr, &PlayFinishOrderAnim_hook, &PlayFinishOrderAnim_orig, L"PlayFinishOrderAnim");

	}
}