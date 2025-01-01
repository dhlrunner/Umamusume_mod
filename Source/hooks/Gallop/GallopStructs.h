#pragma once
#include "..\Unity\il2cpp\il2cpp_symbols.hpp"

namespace Gallop 
{
	//Gallop Structs
	//Gallop.CharaDressIdSet
	struct __declspec(align(8)) CharaDressIdSet {
	public:
		long dummy1;
		long dummy2;
		bool _IsMob_k__BackingField;
		int32_t _DressColorId_k__BackingField;
		int32_t _DressColorId2_k__BackingField;
		//struct System_Func_int__o* _getRandomMob;
		int dummy3;
		int32_t _charaId;
		int32_t _dressId;
		int32_t _dressId2;
	};

	//Gallop.MasterDressData
	struct MasterDressData {
	public:
		//long dummy1;
		//long dummy2;
		char dummy[0x10];
		int32_t Id;
		int32_t ConditionType;
		bool HaveMini;
		int32_t GeneralPurpose;
		int32_t CharaId;
		int32_t UseGender;
		int32_t BodyType;
		int32_t BodyTypeSub;
		int32_t BodySetting;
		int32_t UseRace;
		int32_t UseLive;
		int32_t UseLiveTheater;
		int32_t UseHome;
		int32_t IsWet;
		int32_t IsDirt;
		int32_t HeadSubId;
		int32_t UseSeason;
		char dummy1[4];
		Il2CppString* DressColorMain;
		Il2CppString* DressColorSub;
		int32_t ColorNum;
		int32_t DispOrder;
		int32_t TailModelId;
		int32_t TailModelSubId;
		int64_t StartTime;
		int64_t EndTime;
		int32_t _getCondition;
	};

}