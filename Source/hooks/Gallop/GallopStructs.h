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

	enum class SpringUpdateMode
	{
		// Token: 0x04015662 RID: 87650
		ModeNormal,
		// Token: 0x04015663 RID: 87651
		Mode60FPS,
		// Token: 0x04015664 RID: 87652
		SkipFrame,
		// Token: 0x04015665 RID: 87653
		SkipFramePostAlways
	};

	enum class CharacterClothMode
	{
		// Token: 0x0400F80C RID: 63500
		None = -1,
		// Token: 0x0400F80D RID: 63501
		Race,
		// Token: 0x0400F80E RID: 63502
		Live,
		// Token: 0x0400F80F RID: 63503
		LiveTheater,
		// Token: 0x0400F810 RID: 63504
		Home,
		// Token: 0x0400F811 RID: 63505
		All
	};

	//Gallop.MasterCharaData.CharaData
	struct MasterCharaData_CharaData {
		int32_t Id;                     // 0x10
		int32_t BirthYear;              // 0x14
		int32_t BirthMonth;             // 0x18
		int32_t BirthDay;               // 0x1C
		int32_t LastYear;               // 0x20
		int32_t Sex;                    // 0x24
		Il2CppString* ImageColorMain;     // 0x28
		Il2CppString* ImageColorSub;      // 0x30
		Il2CppString* UiColorMain;        // 0x38
		Il2CppString* UiColorSub;         // 0x40
		Il2CppString* UiTrainingColor1;   // 0x48
		Il2CppString* UiTrainingColor2;   // 0x50
		Il2CppString* UiBorderColor;      // 0x58
		Il2CppString* UiNumColor1;        // 0x60
		Il2CppString* UiNumColor2;        // 0x68
		Il2CppString* UiTurnColor;        // 0x70
		Il2CppString* UiWipeColor1;       // 0x78
		Il2CppString* UiWipeColor2;       // 0x80
		Il2CppString* UiWipeColor3;       // 0x88
		Il2CppString* UiSpeechColor1;     // 0x90
		Il2CppString* UiSpeechColor2;     // 0x98
		Il2CppString* UiNameplateColor1;  // 0xA0
		Il2CppString* UiNameplateColor2;  // 0xA8
		int32_t Height;                 // 0xB0
		int32_t Bust;                   // 0xB4
		int32_t Scale;                  // 0xB8
		int32_t Skin;                   // 0xBC
		int32_t Shape;                  // 0xC0
		int32_t Socks;                  // 0xC4
		int32_t PersonalDress;          // 0xC8
		int32_t TailModelId;            // 0xCC
		int32_t RaceRunningType;        // 0xD0
		int32_t EarRandomTimeMin;       // 0xD4
		int32_t EarRandomTimeMax;       // 0xD8
		int32_t TailRandomTimeMin;      // 0xDC
		int32_t TailRandomTimeMax;      // 0xE0
		int32_t StoryEarRandomTimeMin;  // 0xE4
		int32_t StoryEarRandomTimeMax;  // 0xE8
		int32_t StoryTailRandomTimeMin; // 0xEC
		int32_t StoryTailRandomTimeMax; // 0xF0
		int32_t AttachmentModelId;      // 0xF4
		int32_t MiniMayuShaderType;     // 0xF8
		int64_t StartDate;              // 0x100
		int32_t CharaCategory;          // 0x108
		int32_t LoveRankLimit;          // 0x10C

		Il2CppString* Name;
	};
}

