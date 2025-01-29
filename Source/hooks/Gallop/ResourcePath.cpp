#include "ResourcePath.h"

namespace Gallop::ResourcePath
{

	void* GetRaceResultCuttPath_orig = nullptr;
	Il2CppString* GetRaceResultCuttPath_hook(int charaId, int subId, int cardId, int rank, int grade, int raceType) {
		if (Settings::Local->raceResultCutinMotionChara > -1) {
			charaId = Settings::Local->raceResultCutinMotionChara;
			// dress->CharaId = Settings::Local->raceResultCutinMotionChara;
		}
		if (Settings::Local->cardid > -1) {
			cardId = Settings::Local->cardid;
		}
		if (Settings::Local->raceResultCutinMotionGrade > -1) {
			grade = Settings::Local->raceResultCutinMotionGrade;
		}
		if (Settings::Local->raceResultCutinMotionRank > -1) {
			rank = Settings::Local->raceResultCutinMotionRank;
		}
		Logger::Info(SECTION_NAME, L"GetRaceResultCuttPath charaid=%d, subid=%d, cardid=%d,rank=%d, grade=%d, raceType=%d", charaId, subId, cardId, rank, grade, raceType);
		return reinterpret_cast<decltype(GetRaceResultCuttPath_hook)*>(GetRaceResultCuttPath_orig)(charaId, subId, cardId, rank, grade, raceType);
	}



	void Init()
	{
		Logger::Info(SECTION_NAME, L"Init");
		auto GetRaceResultCuttPath_addr = reinterpret_cast<Il2CppString * (*)(int, int, int, int, int, int)>(il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"ResourcePath", "GetRaceResultCuttPath", 6
		));
		EnableHook(GetRaceResultCuttPath_addr, &GetRaceResultCuttPath_hook, &GetRaceResultCuttPath_orig, L"GetRaceResultCuttPath");
	}
}