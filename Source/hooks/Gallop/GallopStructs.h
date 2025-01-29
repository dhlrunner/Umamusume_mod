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

	//Gallop.CutIn.CutInCharacterCreateInfo
	struct CutInCharacterCreateInfo
	{
		LPVOID unknown1; //0x00
		LPVOID unknown2; //0x08
		int _characterType; // 0x10
		int _charaIndex; // 0x14
		LPVOID _parent; // 0x18
		int _charaId; // 0x20
		int _clothId; // 0x24
		int _headId; // 0x28
		int IsUseDressDataHeadModelSubId; // 0x2C
		int _zekkenNo; // 0x30
		bool _isWet; // 0x34
		bool _isDirt; // 0x35
		short unknown3; // 0x36
		int OverrideClothCategory; // 0x38
	};

	//Gallop.CutIn.Cutt.TimelineKeyCharacterType
	enum class TimelineKeyCharacterType
	{
		User,
		Target,
		FixRank,
		FixCharaId,
		CardId,
		Mob
	};

	//Gallop.MobBuildInfo
	struct MobBuildInfo {
	public:
		int32_t faceKindId;
		int32_t hairKindId;
		int32_t hairColorId;
		int32_t DressColorId;
		float HairCutoff;
		int32_t AttachmentModelId;
	};


	//Gallop.CharacterBuildInfo
	struct CharacterBuildInfo {
	public:
		char dummy[0x10];
		int32_t _cardId;
		int32_t _charaId;
		int32_t _mobId;
		int32_t _headModelSubId;
		bool _isUseDressDataHeadModelSubId;
		int32_t _bodyModelSubId;
		int32_t _dressId;
		int32_t _controllerType;
		int32_t _zekken;
		int dummy5;
		Il2CppString* _name;
		int32_t _genderType;
		int32_t _heightType;
		int32_t _bodySize;
		int32_t _bustType;
		float _height;
		int32_t _skinType;
		int32_t _socksType;
		int32_t _defaultPersonalityType;
		int32_t _raceGateInPersonalityType;
		int32_t _raceRunPersonalityType;
		int32_t _raceOverRunPersonalityType;
		int32_t _raceRunningType;
		int32_t _zekkenColor;
		int32_t _zekkenFontColor;
		int32_t _zekkenFontStyle;
		void* _wetTextureArray;
		void* _dirtTextureArray;
		void* _sweatLocator;
		void* _sweatObject;

		int32_t _frameColor;
		int32_t _popularity;
		int32_t _npcType;
		void* _charaBuildPathInfo;
		void* _clothBuildPathInfo;
		MasterDressData* _dressElement;
		int32_t _backDancerColorId;
		struct MobBuildInfo _mobInfo;
		bool _isPersonalDress;
		int32_t _miniMobTailId;
		int32_t _miniMobParentCharaId;
		int32_t _overrideClothCategory;
		int32_t _loadHashKey;
		bool _isPreCreatedLoadHashKey;
		bool _initialized;


	};

	//Gallop.CySpringDataContainer.Category
	namespace CySpringDataContainer {
		enum class Category {
			Invalid = -1,
			Live,
			Race,
			Story,
			Home,
			Training
		};
	}

	//Gallop.ModelLoader.ZekkenColor
	enum class ZekkenColor {
		DeepBlue,
		DeepRed,
		DeepGreen,
		Black,
		White,
		Count,
		Default = 3
	};

	//Gallop.ModelLoader.ZekkenFontColor
	enum class ZekkenFontColor
	{
		Black,
		White,
		Yellow,
		Count,
		Default = 1
	};

	//Gallop.ModelLoader.ControllerType
	enum class ControllerType
	{
		Default,
		Race,
		Training,
		EventTimeline,
		Live,
		HomeStand,
		HomeTalk,
		HomeWalk,
		CutIn,
		TrainingTop,
		SingleRace,
		Simple,
		Mini,
		Paddock,
		Champions
	};

	//Gallop.ModelLoader.TrackSuitColor
	enum class TrackSuitColor
	{
		White,
		Black,
		Red,
		Blue,
		Yellow,
		Green,
		Orange,
		Peach
	};

	struct CutInModelController_Context {
		int CardId;
		int CharaId;
		int DressId;
		int HeadId;
		int ZekkenNo;
		ZekkenColor ZekkenColor;
		ZekkenFontColor ZekkenFontColor;
		TrackSuitColor FrameColor;
		ControllerType ControllerType;
		bool IsWet;
		bool IsDirt;
		CySpringDataContainer::Category  _overrideClothCategory;
		bool IsUseDressDataHeadModelSubId;
	};

	
}

