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

#pragma pack(push, 4)          /* Unity/IL2CPP 기본 4-byte alignment */

	typedef struct AudienceBuildInfo
	{
		/*0x10*/ int32_t  faceKindId;
		/*0x14*/ int32_t  hairKindId;
		/*0x18*/ int32_t  hairColorId;
		/*0x1C*/ int32_t  dressColorId;   /* 주의: C# 필드명은 대문자 D */

		/* 생성자∙메서드는 IL2CPP 변환 후 별도 함수이므로
		   본 구조체에는 포함되지 않습니다 */
	} AudienceBuildInfo;

#pragma pack(pop)

	/* ─── Instance-layout (x86_64 IL2CPP) ───────────────────────────────── */
#pragma pack(push, 4)               /* 4-byte alignment like Mono/IL2CPP */

	typedef struct CharacterBuildInfo
	{
		/*0x10*/ int32_t      _cardId;
		/*0x14*/ int32_t      _charaId;
		/*0x18*/ int32_t      _mobId;
		/*0x1C*/ int32_t      _audienceId;

		/*0x20*/ int32_t      _headModelSubId;
		/*0x24*/ bool         _isUseDressDataHeadModelSubId;
		uint8_t      _pad24[3];                /* →0x28 */

		/*0x28*/ int32_t      _bodyModelSubId;
		/*0x2C*/ int32_t      _motionBodyModelSubId;
		/*0x30*/ int32_t      _dressId;
		/*0x34*/ int32_t      _motionDressId;
		/*0x38*/ int32_t      _controllerType;          /* enum */
		/*0x3C*/ int32_t      _zekken;

		/*0x40*/ Il2CppString* _name;
		/*0x48*/ int32_t      _genderType;              /* enum */
		/*0x4C*/ int32_t      _heightType;              /* enum */
		/*0x50*/ int32_t      _bodySize;                /* enum */
		/*0x54*/ int32_t      _bustType;                /* enum */
		/*0x58*/ float        _height;
		/*0x5C*/ int32_t      _skinType;                /* enum */
		/*0x60*/ int32_t      _socksType;               /* enum */
		/*0x64*/ int32_t      _defaultPersonalityType;
		/*0x68*/ int32_t      _raceGateInPersonalityType;
		/*0x6C*/ int32_t      _raceRunPersonalityType;
		/*0x70*/ int32_t      _raceOverRunPersonalityType;
		/*0x74*/ int32_t      _raceRunningType;
		/*0x78*/ int32_t      _zekkenColor;             /* enum */
		/*0x7C*/ int32_t      _zekkenFontColor;         /* enum */
		/*0x80*/ int32_t      _zekkenFontStyle;         /* enum */
		uint8_t      _pad84[4];                /* →0x88 */

		/*0x88*/ Il2CppArray* _wetTextureArray;         /* Texture[] */
		/*0x90*/ Il2CppArray* _dirtTextureArray;        /* Texture[] */
		/*0x98*/ void* _sweatLocator;
		/*0xA0*/ void* _sweatObject;

		/*0xA8*/ int32_t      _frameColor;              /* enum */
		/*0xAC*/ int32_t      _popularity;
		/*0xB0*/ int32_t      _npcType;                 /* enum */
		uint8_t      _padB4[4];                /* →0xB8 */

		/*0xB8*/ void* _charaBuildPathInfo;
		/*0xC0*/ void* _clothBuildPathInfo;
		/*0xC8*/ void* _dressElement;

		/*0xD0*/ int32_t      _backDancerColorId;
		/*0xD4*/ int32_t      _attachmentModelId;
		/*0xD8*/ bool         _isAttachmentModel;
		uint8_t      _padD9[3];                /* →0xDC */

		/*0xDC*/ MobBuildInfo* _mobInfo;
		uint8_t      _padE4[0x10];             /* reserve to 0xF4 */

		/*0xF4*/ AudienceBuildInfo* _audienceInfo;
		uint8_t      _padFC[0x8];              /* →0x104 */

		/*0x104*/ bool         _isPersonalDress;
		uint8_t      _pad105[3];               /* →0x108 */

		/*0x108*/ int32_t      _miniMobTailId;
		/*0x10C*/ int32_t      _miniMobParentCharaId;
		/*0x110*/ int32_t      _overrideClothCategory;   /* enum */
		/*0x114*/ void* _loadHashKey;

		/*0x118*/ bool         _isPreCreatedLoadHashKey;
		/*0x119*/ bool         _isEnableModelCache;
		uint8_t      _pad11A[2];               /* →0x11C */

		/*0x11C*/ int32_t      _charaDressColorSetId;
		/*0x120*/ bool         _initialized;
		uint8_t      _pad121[3];               /* →0x124 */
	} CharacterBuildInfo;

#pragma pack(pop)

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

	struct HorseData {
		//IL2CPP
		char _0x00[0x10];

		//fields
		int horseIndex;						//0x10
		int postNumber;						//0x14
		int HorseNumber;					//0x18
		int charaId;						//0x1C
		Il2CppString* charaName;			//0x20
		int FinishOrder;					//0x28
		float FinishTimeRaw;				//0x2C
		float FinishTimeScaled;				//0x30
		float FinishDiffTimeFromPrev;		//0x34
		void* raceParam;					//0x38 IRaceParameter
		void* responseHorseData;			//0x40 _this
		int Popularity;						//0x48
		int PopularityRankLeft;				//0x4C
		int PopularityRankCenter;			//0x50
		int PopularityRankRight;			//0x54
		int gateInPopularity;				//0x58
		int Rarity;							//0x5C enum
		Il2CppString* TrainerName;			//0x60
		bool IsGhost;						//0x68
		bool isRunningStyleExInitialized;	//0x69
		char pad_0x6A[0x2];					//0x6A~0x6B alignment
		int runningStyleEx;					//0x6C
		int Defeat;							//0x70
		int RaceDressId;					//0x74
		int RaceDressIdWithOption;			//0x78
		int RunningType;					//0x7C
		int ActiveProperDistance;			//0x80
		int ActiveProperGroundType;			//0x84
		int MobId;							//0x88
		void* raceRecord;					//0x90 IRaceRecord*
		int FinishOrderRawScore;			//0x98
		int* TrainedCharaData;				//0xA0
	};

	// IL2CPP는 C#의 sealed class를 C++에서 final class로 처리할 수 있지만,
	// 데이터 전용 클래스이므로 간단한 struct로 표현하는 것이 일반적입니다.
	// IL2CPP 내부적으로는 클래스 메타데이터와 함께 관리됩니다.

	// C#의 Int32는 C++의 int32_t에 해당합니다.
	struct LiveFixMemberData : Il2CppObject
	{
		// Fields (readonly in C# -> const in C++ with constructor initialization)
		const int32_t Id;
		const int32_t MusicId;
		const int32_t Order;
		const int32_t CharaId;
		const int32_t DressId1;
		const int32_t DressId2;
		const int32_t DressColor1;
		const int32_t DressColor2;

		// Constructor (C# .ctor -> C++ constructor)
		// RVA 및 VA 주석은 IL2CPP 런타임 내부 주소이므로 C++ 코드에는 직접 포함되지 않습니다.
		LiveFixMemberData(
			int32_t id,
			int32_t musicId,
			int32_t order,
			int32_t charaId,
			int32_t dressId1,
			int32_t dressId2,
			int32_t dressColor1,
			int32_t dressColor2
		) :
			Id(id),
			MusicId(musicId),
			Order(order),
			CharaId(charaId),
			DressId1(dressId1),
			DressId2(dressId2),
			DressColor1(dressColor1),
			DressColor2(dressColor2)
		{
		}

	};


	struct List_1_Fields {
		Il2CppArray* _items;
		int32_t _size;
		int32_t _version;
		Il2CppObject* _syncRoot;
	};

	struct List_1_LiveFixMemberData : Il2CppObject {
		List_1_Fields fields;
	};
}

