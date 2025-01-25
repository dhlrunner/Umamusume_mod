#include "Live.Cutt.h"

using namespace Unity;
namespace Gallop::Live::Cutt 
{
	void* AlterUpdate_orig = nullptr;
	void AlterUpdate_hook(void* _this, float liveTime) {
		//printf("AlterUpdate time=%.2f \n", liveTime);
		if (!Settings::Local->stopLiveCam) {
			return reinterpret_cast<decltype(AlterUpdate_hook)*>
				(AlterUpdate_orig)(_this, liveTime);
		}
	}

	void* AlterUpdate_CameraLookAt_orig = nullptr;
	void AlterUpdate_CameraLookAt_hook(void* _this, void* sheet, int currentFrame, float currentTime, Vector3_t* outLookAt) {
		if (!Settings::Local->stopLiveCam) {
			reinterpret_cast<decltype(AlterUpdate_CameraLookAt_hook)*>
				(AlterUpdate_CameraLookAt_orig)(_this, sheet, currentFrame, currentTime, outLookAt);
		}
		//liveCam_Lookat = *outLookAt;
		//printf("AlterUpdate_CameraLookAt x=%.2f y=%.2f z=%.2f CurrentFrame=%d\n", outLookAt->x, outLookAt->y, outLookAt->z, currentFrame);

	}

	void* AlterUpdate_CameraPos_orig = nullptr;
	void AlterUpdate_CameraPos_hook(void* _this, void* sheet, int currentFrame, float currentTime, int sheetIndex, bool isUseCameraMotion) {
		if (!Settings::Local->stopLiveCam) {
			return reinterpret_cast<decltype(AlterUpdate_CameraPos_hook)*>
				(AlterUpdate_CameraPos_orig)(_this, sheet, currentFrame, currentTime, sheetIndex, isUseCameraMotion);
		}
		//printf("AlterUpdate_CameraPos sheetIndex=%d, CurrentFrame=%d\n",sheetIndex, currentFrame);

	}

	void* AlterUpdate_CameraSwitcher_orig = nullptr;
	void AlterUpdate_CameraSwitcher_hook(void* _this, void* sheet, int currentFrame) {
		if (!Settings::Local->stopLiveCam) {
			return reinterpret_cast<decltype(AlterUpdate_CameraSwitcher_hook)*>
				(AlterUpdate_CameraSwitcher_orig)(_this, sheet, currentFrame);
		}
		//printf("AlterUpdate_CameraSwitcher CurrentFrame=%d\n", currentFrame);

	}

	void* AlterUpdate_CameraLayer_orig = nullptr;
	//void AlterUpdate_CameraLayer_hook(void* _this, void* sheet, int currentFrame, Vector3_t* offsetMaxPosition, Vector3_t* offsetMinPosition) {
	void AlterUpdate_CameraLayer_hook(void* _this, void* sheet, int currentFrame) {
		if (!Settings::Local->stopLiveCam) {
			return reinterpret_cast<decltype(AlterUpdate_CameraLayer_hook)*>
				(AlterUpdate_CameraLayer_orig)(_this, sheet, currentFrame);
		}
		/*printf("AlterUpdate_CameraLayer CurrentFrame=%d minPos x=%.2f y=%.2f z=%.2f maxPos x=%.2f y=%.2f z=%.2f\n",
			currentFrame,
		offsetMinPosition->x,offsetMinPosition->y,offsetMinPosition->z,
			offsetMaxPosition->x, offsetMaxPosition->y, offsetMaxPosition->z );*/

	}

	void* AlterUpdate_CameraMotion_orig = nullptr;
	void AlterUpdate_CameraMotion_hook(void* _this, void* sheet, int currentFrame) {
		//printf("AlterUpdate_CameraMotion CurrentFrame=%d\n", currentFrame);
		if (!Settings::Local->stopLiveCam) {
			return reinterpret_cast<decltype(AlterUpdate_CameraMotion_hook)*>
				(AlterUpdate_CameraMotion_orig)(_this, sheet, currentFrame);
		}

	}

	void* AlterUpdate_CameraRoll_orig = nullptr;
	void AlterUpdate_CameraRoll_hook(void* _this, void* sheet, int currentFrame) {
		//printf("AlterUpdate_CameraRoll CurrentFrame=%d\n", currentFrame);
		if (!Settings::Local->stopLiveCam) {
			return reinterpret_cast<decltype(AlterUpdate_CameraRoll_hook)*>
				(AlterUpdate_CameraRoll_orig)(_this, sheet, currentFrame);
		}

	}

	void* AlterUpdate_MultiCameraSwitcher_orig = nullptr;
	void AlterUpdate_MultiCameraSwitcher_hook(void* _this, void* sheet, void* curData, void* nextData, int currentFrame, int keyIndex, bool isFading) {
		Logger::Debug(SECTION_NAME, L"AlterUpdate_MultiCameraSwitcher CurrentFrame=%d, keyindex=%d\n", currentFrame, keyIndex);
		return reinterpret_cast<decltype(AlterUpdate_CameraRoll_hook)*>
			(AlterUpdate_CameraRoll_orig)(_this, sheet, currentFrame);
	}

	/*void* AlterUpdate_MultiCamera_orig = nullptr;
	void AlterUpdate_MultiCamera_hook(void* _this, void* sheet, int currentFrame) {
		printf("AlterUpdate_MultiCamera CurrentFrame=%d \n", currentFrame);
		return reinterpret_cast<decltype(AlterUpdate_MultiCamera_hook)*>
			(AlterUpdate_MultiCamera_orig)(_this, sheet,currentFrame);
	}*/

	void* AlterUpdate_CameraFov_orig = nullptr;
	void AlterUpdate_CameraFov_hook(void* _this, void* sheet, int currentFrame) {
		//printf("AlterUpdate_CameraFov CurrentFrame=%d \n", currentFrame);
		if (!Settings::Local->stopLiveCam) {
			return reinterpret_cast<decltype(AlterUpdate_CameraFov_hook)*>
				(AlterUpdate_CameraFov_orig)(_this, sheet, currentFrame);
		}

	}

	void* AlterLateUpdate_CameraMotion_orig = nullptr;
	bool AlterLateUpdate_CameraMotion_hook(void* _this, void* sheet, int currentFrame) {
		/*bool ret = reinterpret_cast<decltype(AlterLateUpdate_CameraMotion_hook)*>
			(AlterLateUpdate_CameraMotion_orig)(_this, sheet, currentFrame);*/

			//printf("AlterLateUpdate_CameraMotion CurrentFrame=%d, ret=%d\n", currentFrame,ret);
		if (!Settings::Local->stopLiveCam) {
			return reinterpret_cast<decltype(AlterLateUpdate_CameraMotion_hook)*>
				(AlterLateUpdate_CameraMotion_orig)(_this, sheet, currentFrame);
		}

		return true;


	}

	void* AlterUpdate_EyeCameraLookAt_orig = nullptr;
	void AlterUpdate_EyeCameraLookAt_hook(void* _this, void* sheet, int currentFrame, float currentTime) {
		//printf("AlterUpdate_EyeCameraLookAt CurrentFrame=%d \n", currentFrame);
		if (!Settings::Local->stopLiveCam) {
			return reinterpret_cast<decltype(AlterUpdate_EyeCameraLookAt_hook)*>
				(AlterUpdate_EyeCameraLookAt_orig)(_this, sheet, currentFrame, currentTime);
		}

	}

	void* AlterUpdate_EyeCameraPosition_orig = nullptr;
	void AlterUpdate_EyeCameraPosition_hook(void* _this, void* sheet, int currentFrame, float currentTime) {
		//printf("AlterUpdate_EyeCameraLookAt CurrentFrame=%d \n", currentFrame);
		if (!Settings::Local->stopLiveCam) {
			return reinterpret_cast<decltype(AlterUpdate_EyeCameraPosition_hook)*>
				(AlterUpdate_EyeCameraPosition_orig)(_this, sheet, currentFrame, currentTime);
		}

	}

	

	void* AlterUpdate_MultiCameraLookAt_orig = nullptr;
	void AlterUpdate_MultiCameraLookAt_hook(void* _this, void* sheet, int currentFrame, float currentTime) {
		//printf("AlterUpdate_MultiCameraLookAt currentFrame=%d \n", currentFrame);
		if (!Settings::Local->stopLiveCam) {
			return reinterpret_cast<decltype(AlterUpdate_MultiCameraLookAt_hook)*>
				(AlterUpdate_MultiCameraLookAt_orig)(_this, sheet, currentFrame, currentTime);
		}
	}

	void* AlterUpdate_MultiCameraPosition_orig = nullptr;
	void AlterUpdate_MultiCameraPosition_hook(void* _this, void* sheet, int currentFrame, float currentTime) {
		//printf("AlterUpdate_MultiCameraPosition currentFrame=%d \n", currentFrame);
		if (!Settings::Local->stopLiveCam) {
			return reinterpret_cast<decltype(AlterUpdate_MultiCameraPosition_hook)*>
				(AlterUpdate_MultiCameraPosition_orig)(_this, sheet, currentFrame, currentTime);
		}
	}

	void* AlterUpdate_MultiCameraTiltShift_orig = nullptr;
	void AlterUpdate_MultiCameraTiltShift_hook(void* _this, void* sheet, int currentFrame) {
		//printf("AlterUpdate_MultiCameraTiltShift currentFrame=%d \n", currentFrame);
		if (!Settings::Local->stopLiveCam) {
			return reinterpret_cast<decltype(AlterUpdate_MultiCameraTiltShift_hook)*>
				(AlterUpdate_MultiCameraTiltShift_orig)(_this, sheet, currentFrame);
		}
	}

	void* AlterUpdate_PostEffect_DOF_orig = nullptr;
	void AlterUpdate_PostEffect_DOF_hook(void* _this, void* sheet, int currentFrame, Vector3_t* cameraLookAt) {

		//printf("AlterUpdate_PostEffect_DOF currentFrame=%d pos x=%.2f y=%.2f z=%.2f \n", currentFrame,
			//cameraLookAt->x,cameraLookAt->y,cameraLookAt->z);
		if (!Settings::Local->stopLiveCam) {
			return reinterpret_cast<decltype(AlterUpdate_PostEffect_DOF_hook)*>
				(AlterUpdate_PostEffect_DOF_orig)(_this, sheet, currentFrame, cameraLookAt);
		}
	}


	void Init() 
	{
		Logger::Info(SECTION_NAME, L"Init");

		auto AlterUpdate_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop.Live.Cutt",
			"LiveTimelineControl", "AlterUpdate", 1
		);
		EnableHook(AlterUpdate_addr, &AlterUpdate_hook, &AlterUpdate_orig, L"AlterUpdate");

		auto AlterUpdate_CameraLookAt_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop.Live.Cutt",
			"LiveTimelineControl", "AlterUpdate_CameraLookAt", 4
		);
		EnableHook(AlterUpdate_CameraLookAt_addr, &AlterUpdate_CameraLookAt_hook, &AlterUpdate_CameraLookAt_orig, L"AlterUpdate_CameraLookAt");

		auto AlterUpdate_CameraPos_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop.Live.Cutt",
			"LiveTimelineControl", "AlterUpdate_CameraPos", 5
		);
		EnableHook(AlterUpdate_CameraPos_addr, &AlterUpdate_CameraPos_hook, &AlterUpdate_CameraPos_orig, L"AlterUpdate_CameraPos");

		auto AlterUpdate_CameraSwitcher_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop.Live.Cutt",
			"LiveTimelineControl", "AlterUpdate_CameraSwitcher", 2
		);
		EnableHook(AlterUpdate_CameraSwitcher_addr, &AlterUpdate_CameraSwitcher_hook, &AlterUpdate_CameraSwitcher_orig, L"AlterUpdate_CameraSwitcher");

		auto AlterUpdate_CameraLayer_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop.Live.Cutt",
			"LiveTimelineControl", "AlterUpdate_CameraLayer", 2
		);
		EnableHook(AlterUpdate_CameraLayer_addr, &AlterUpdate_CameraLayer_hook, &AlterUpdate_CameraLayer_orig, L"AlterUpdate_CameraLayer");

		auto AlterUpdate_CameraMotion_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop.Live.Cutt",
			"LiveTimelineControl", "AlterUpdate_CameraMotion", 2
		);
		EnableHook(AlterUpdate_CameraMotion_addr, &AlterUpdate_CameraMotion_hook, &AlterUpdate_CameraMotion_orig, L"AlterUpdate_CameraMotion");

		auto AlterUpdate_CameraRoll_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop.Live.Cutt",
			"LiveTimelineControl", "AlterUpdate_CameraRoll", 2
		);
		EnableHook(AlterUpdate_CameraRoll_addr, &AlterUpdate_CameraRoll_hook, &AlterUpdate_CameraRoll_orig, L"AlterUpdate_CameraRoll");

		auto AlterUpdate_MultiCameraSwitcher_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop.Live.Cutt",
			"LiveTimelineControl", "AlterUpdate_MultiCameraSwitcher", 6
		);
		EnableHook(AlterUpdate_MultiCameraSwitcher_addr, &AlterUpdate_MultiCameraSwitcher_hook, &AlterUpdate_MultiCameraSwitcher_orig, L"AlterUpdate_MultiCameraSwitcher");

		/*auto AlterUpdate_MultiCamera_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop.Live.Cutt",
			"LiveTimelineControl", "AlterUpdate_MultiCamera", 2
		);*/

		auto AlterUpdate_EyeCameraPosition_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop.Live.Cutt",
			"LiveTimelineControl", "AlterUpdate_EyeCameraPosition", 3
		);
		EnableHook(AlterUpdate_EyeCameraPosition_addr, &AlterUpdate_EyeCameraPosition_hook, &AlterUpdate_EyeCameraPosition_orig, L"AlterUpdate_EyeCameraPosition");

		auto AlterUpdate_EyeCameraLookAt_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop.Live.Cutt",
			"LiveTimelineControl", "AlterUpdate_EyeCameraLookAt", 3
		);
		EnableHook(AlterUpdate_EyeCameraLookAt_addr, &AlterUpdate_EyeCameraLookAt_hook, &AlterUpdate_EyeCameraLookAt_orig, L"AlterUpdate_EyeCameraLookAt");

		auto AlterLateUpdate_CameraMotion_addr = reinterpret_cast<bool(*)(void*, void*, int)> (
			il2cpp_symbols::get_method_pointer(
				"umamusume.dll", "Gallop.Live.Cutt",
				"LiveTimelineControl", "AlterLateUpdate_CameraMotion", 2
			)
			);
		EnableHook(AlterLateUpdate_CameraMotion_addr, &AlterLateUpdate_CameraMotion_hook, &AlterLateUpdate_CameraMotion_orig, L"AlterLateUpdate_CameraMotion");	

		auto AlterUpdate_MultiCameraLookAt_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop.Live.Cutt",
			"LiveTimelineControl", "AlterUpdate_MultiCameraLookAt", 3
		);
		EnableHook(AlterUpdate_MultiCameraLookAt_addr, &AlterUpdate_MultiCameraLookAt_hook, &AlterUpdate_MultiCameraLookAt_orig, L"AlterUpdate_MultiCameraLookAt");

		auto AlterUpdate_MultiCameraPosition_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop.Live.Cutt",
			"LiveTimelineControl", "AlterUpdate_MultiCameraPosition", 3
		);
		EnableHook(AlterUpdate_MultiCameraPosition_addr, &AlterUpdate_MultiCameraPosition_hook, &AlterUpdate_MultiCameraPosition_orig, L"AlterUpdate_MultiCameraPosition");

		auto AlterUpdate_MultiCameraTiltShift_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop.Live.Cutt",
			"LiveTimelineControl", "AlterUpdate_MultiCameraTiltShift", 2
		);
		EnableHook(AlterUpdate_MultiCameraTiltShift_addr, &AlterUpdate_MultiCameraTiltShift_hook, &AlterUpdate_MultiCameraTiltShift_orig, L"AlterUpdate_MultiCameraTiltShift");

		auto AlterUpdate_PostEffect_DOF_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop.Live.Cutt",
			"LiveTimelineControl", "AlterUpdate_PostEffect_DOF", 3
		);
		EnableHook(AlterUpdate_PostEffect_DOF_addr, &AlterUpdate_PostEffect_DOF_hook, &AlterUpdate_PostEffect_DOF_orig, L"AlterUpdate_PostEffect_DOF");

		auto AlterUpdate_CameraFov_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop.Live.Cutt",
			"LiveTimelineControl", "AlterUpdate_CameraFov", 2
		);
		EnableHook(AlterUpdate_CameraFov_addr, &AlterUpdate_CameraFov_hook, &AlterUpdate_CameraFov_orig, L"AlterUpdate_CameraFov");
	}
}