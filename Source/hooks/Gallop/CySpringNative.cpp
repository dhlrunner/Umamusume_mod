#include "CySpringNative.h"

namespace Gallop::CySpringNative
{
	void* UpdateForce_orig;
	void UpdateForce_hook(void* clothWorking, 
		float stiffnessForceRate, 
		float dragForceRate, 
		float gravityRate, 
		Unity::Vector3_t windPower, 
		float windStrength, 
		Unity::Vector3_t positionDiff, 
		float frameScale)
	{
		printf("CySpringNative UpdateForce frameScale=%.2f\n", frameScale);
		return reinterpret_cast<decltype(UpdateForce_hook)*>(UpdateForce_orig)(
			clothWorking,
			stiffnessForceRate,
			dragForceRate,
			gravityRate,
			windPower,
			windStrength,
			positionDiff,
			frameScale);
	}

	void* UpdateNativeClothInternalMono_orig;
	void UpdateNativeClothInternalMono_hook(
		Il2CppObject* clothWorking,
		Il2CppArraySize_t<Il2CppObject*>* collisionArray,
		Il2CppArraySize_t<Il2CppObject*>* nativeRootParentArray,
		float stiffnessForceRate, 
		float dragForceRate,
		float gravityRate,
		Unity::Vector3_t windPower,
		float windStrength,
		bool bCollisionSwitch,
		float timescale,
		bool is60FPS,
		float moveRate,
		float addMoveRate,
		float springRate) 
	{
		printf("clothWorking: %p\n", clothWorking);
		printf("collisionArray: %p\n", collisionArray);
		printf("nativeRootParentArray: %p\n", nativeRootParentArray);
		printf("stiffnessForceRate: %f\n", stiffnessForceRate);
		printf("dragForceRate: %f\n", dragForceRate);
		printf("gravityRate: %f\n", gravityRate);
		printf("windPower: (%f, %f, %f)\n", windPower.x, windPower.y, windPower.z);
		printf("windStrength: %f\n", windStrength);
		printf("bCollisionSwitch: %s\n", bCollisionSwitch ? "true" : "false");
		printf("timescale: %f\n", timescale);
		printf("is60FPS: %s\n", is60FPS ? "true" : "false");
		printf("moveRate: %f\n", moveRate);
		printf("addMoveRate: %f\n", addMoveRate);
		printf("springRate: %f\n", springRate);
		return reinterpret_cast<decltype(UpdateNativeClothInternalMono_hook)*>(UpdateNativeClothInternalMono_orig)(
			clothWorking,
			collisionArray,
			nativeRootParentArray,
			stiffnessForceRate,
			dragForceRate,
			gravityRate,
			windPower,
			windStrength,
			bCollisionSwitch,
			timescale,
			is60FPS,
			moveRate,
			addMoveRate,
			springRate);
	}

	void* NativeClothSkirtUpdate_orig;
	void NativeClothSkirtUpdate_hook(
		void* cond,
		int32_t nCond,
		void* collisions,
		void* pWorking,
		void* pArg,
		void* pRootParentWork,
		float stiffnessForceRate,
		float dragForceRate,
		float gravityRate,
		float windX,
		float windY,
		float windZ,
		float windStrength,
		bool bCollisionSwitch,
		float timescale,
		bool is60FPS,
		float moveRate,
		float addMoveRate,
		float springRate
	) 
	{
		printf("NativeClothSkirtUpdate called with:\n");
		printf("  cond: %p\n", cond);
		printf("  nCond: %d\n", nCond);
		printf("  collisions: %p\n", collisions);
		printf("  pWorking: %p\n", pWorking);
		printf("  pArg: %p\n", pArg);
		printf("  pRootParentWork: %p\n", pRootParentWork);
		printf("  stiffnessForceRate: %f\n", stiffnessForceRate);
		printf("  dragForceRate: %f\n", dragForceRate);
		printf("  gravityRate: %f\n", gravityRate);
		printf("  windX: %f\n", windX);
		printf("  windY: %f\n", windY);
		printf("  windZ: %f\n", windZ);
		printf("  windStrength: %f\n", windStrength);
		printf("  bCollisionSwitch: %s\n", bCollisionSwitch ? "true" : "false");
		printf("  timescale: %f\n", timescale);
		printf("  is60FPS: %s\n", is60FPS ? "true" : "false");
		printf("  moveRate: %f\n", moveRate);
		printf("  addMoveRate: %f\n", addMoveRate);
		printf("  springRate: %f\n", springRate);
		reinterpret_cast<decltype(NativeClothSkirtUpdate_hook)*>(NativeClothSkirtUpdate_orig)(
			cond, nCond, collisions, pWorking, pArg, pRootParentWork, stiffnessForceRate, dragForceRate, gravityRate, windX, windY, windZ, windStrength, bCollisionSwitch, timescale, is60FPS, moveRate, addMoveRate, springRate
			);
	}

	void Init() 
	{
		Logger::Info(SECTION_NAME, L"Init");
		auto UpdateForce_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"CySpringNative", "UpdateForce", 8
		);
		EnableHook(UpdateForce_addr, &UpdateForce_hook, &UpdateForce_orig, L"CySpringNative_UpdateForce");

		auto UpdateNativeClothInternalMono_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"CySpringNative", "UpdateNativeClothInternalMono", 14
		);
		EnableHook(UpdateNativeClothInternalMono_addr, &UpdateNativeClothInternalMono_hook, &UpdateNativeClothInternalMono_orig, L"CySpringNative_UpdateNativeClothInternalMono");
	
		auto NativeClothSkirtUpdate_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"CySpringNative", "NativeClothSkirtUpdate", 19
		);
		EnableHook(NativeClothSkirtUpdate_addr, &NativeClothSkirtUpdate_hook, &NativeClothSkirtUpdate_orig, L"CySpringNative_NativeClothSkirtUpdate");
	}
}
