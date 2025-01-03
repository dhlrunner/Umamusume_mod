#include "RaceResultCutInHelper.h"

namespace Gallop::RaceResultCutInHelper
{
	void* LoadBodyMotion_orig = nullptr;
	void* LoadBodyMotion_hook(int characterId, MasterDressData* dress, int personalityType, int rank, int grade, int raceType, void* resultSwapData, void* resultSwapMotionData) {

		Logger::Info(SECTION_NAME, L"LoadBodyMotion: charaId=%d,dressid=%d,rank=%d,grade=%d", characterId, dress->Id, rank, grade);
		if (Settings::Global->winMotion564) {
			characterId = 1007;
			dress->CharaId = 1007;
			dress->Id = 100701;
			grade = 200;
			//c_raceResultCutinMotionRank = rank;
		}
		else {
			if (Settings::Local->raceResultCutinMotionChara > -1) {
				characterId = Settings::Local->raceResultCutinMotionChara;
				dress->CharaId = Settings::Local->raceResultCutinMotionChara;
			}
			if (Settings::Local->raceResultCutinMotionDress > -1) {
				dress->Id = Settings::Local->raceResultCutinMotionDress;
			}
			if (Settings::Local->raceResultCutinMotionGrade > -1) {
				grade = Settings::Local->raceResultCutinMotionGrade;
			}
			if (Settings::Local->raceResultCutinMotionRank > -1) {
				rank = Settings::Local->raceResultCutinMotionRank;
			}
		}



		//return nullptr;
		return reinterpret_cast<decltype(LoadBodyMotion_hook)*>
			(LoadBodyMotion_orig)(characterId, dress, personalityType, rank, grade, raceType, resultSwapData, resultSwapMotionData);
	}

	void* LoadCameraMotion_orig = nullptr;
	void* LoadCameraMotion_hook(int characterId, MasterDressData* dress, int personalityType, int rank, int grade, int raceType, void* resultSwapData, void* resultSwapMotionData) {
		//printf("LoadCameraMotion: charaId=%d,dressid=%d,rank=%d,grade=%d\n", characterId, dress->Id, rank, grade);
		printf("characterId: %d\n", characterId);
		printf("dress:\n");
		printf("\tId: %d\n", dress->Id);
		printf("\tConditionType: %d\n", dress->ConditionType);
		printf("\tHaveMini: %d\n", dress->HaveMini);
		printf("\tGeneralPurpose: %d\n", dress->GeneralPurpose);
		printf("\tCharaId: %d\n", dress->CharaId);
		printf("\tUseGender: %d\n", dress->UseGender);
		printf("\tBodyType: %d\n", dress->BodyType);
		printf("\tBodyTypeSub: %d\n", dress->BodyTypeSub);
		printf("\tBodySetting: %d\n", dress->BodySetting);
		printf("\tUseRace: %d\n", dress->UseRace);
		printf("\tUseLive: %d\n", dress->UseLive);
		printf("\tUseLiveTheater: %d\n", dress->UseLiveTheater);
		printf("\tUseHome: %d\n", dress->UseHome);
		printf("\tIsWet: %d\n", dress->IsWet);
		printf("\tIsDirt: %d\n", dress->IsDirt);
		printf("\tHeadSubId: %d\n", dress->HeadSubId);
		printf("\tUseSeason: %d\n", dress->UseSeason);
		printf("\tDressColorMain: %p\n", (void*)dress->DressColorMain);
		printf("\tDressColorSub: %p\n", (void*)dress->DressColorSub);
		printf("\tColorNum: %d\n", dress->ColorNum);
		printf("\tDispOrder: %d\n", dress->DispOrder);
		printf("\tTailModelId: %d\n", dress->TailModelId);
		printf("\tTailModelSubId: %d\n", dress->TailModelSubId);
		printf("\tStartTime: %lld\n", dress->StartTime);
		printf("\tEndTime: %lld\n", dress->EndTime);
		printf("\t_getCondition: %d\n", dress->_getCondition);
		printf("personalityType: %d\n", personalityType);
		printf("rank: %d\n", rank);
		printf("grade: %d\n", grade);
		printf("raceType: %d\n", raceType);
		//return nullptr;
		if (Settings::Global->winMotion564) {
			characterId = 1007;
			dress->CharaId = 1007;
			dress->Id = 100701;
			grade = 200;
			//c_raceResultCutinMotionRank = rank;
		}
		else {
			if (Settings::Local->raceResultCutinMotionChara > -1) {
				characterId = Settings::Local->raceResultCutinMotionChara;
				dress->CharaId = Settings::Local->raceResultCutinMotionChara;
			}
			if (Settings::Local->raceResultCutinMotionDress > -1) {
				dress->Id = Settings::Local->raceResultCutinMotionDress;
			}
			if (Settings::Local->raceResultCutinMotionGrade > -1) {
				grade = Settings::Local->raceResultCutinMotionGrade;
			}
			if (Settings::Local->raceResultCutinMotionRank > -1) {
				rank = Settings::Local->raceResultCutinMotionRank;
			}
		}

		void* ret = reinterpret_cast<decltype(LoadCameraMotion_hook)*>
			(LoadCameraMotion_orig)(
				characterId, dress, personalityType, rank, grade, raceType, resultSwapData, resultSwapMotionData
				);
		printf("LoadCameraMotion ret=%p\n", ret);
		return ret;
	}

	void* LoadEarMotion_orig = nullptr;
	void* LoadEarMotion_hook(int characterId, MasterDressData* dress, int personalityType, int rank, int grade, int raceType) {
		Logger::Info(SECTION_NAME, L"LoadEarMotion: charaId=%d,dressid=%d,rank=%d,grade=%d", characterId, dress->Id, rank, grade);
		//return nullptr;
		if (Settings::Global->winMotion564) {
			characterId = 1007;
			dress->CharaId = 1007;
			dress->Id = 100701;
			grade = 200;
			//c_raceResultCutinMotionRank = rank;
		}
		else {
			if (Settings::Local->raceResultCutinMotionChara > -1) {
				characterId = Settings::Local->raceResultCutinMotionChara;
				dress->CharaId = Settings::Local->raceResultCutinMotionChara;
			}
			if (Settings::Local->raceResultCutinMotionDress > -1) {
				dress->Id = Settings::Local->raceResultCutinMotionDress;
			}
			if (Settings::Local->raceResultCutinMotionGrade > -1) {
				grade = Settings::Local->raceResultCutinMotionGrade;
			}
			if (Settings::Local->raceResultCutinMotionRank > -1) {
				rank = Settings::Local->raceResultCutinMotionRank;
			}
		}

		return reinterpret_cast<decltype(LoadEarMotion_hook)*>
			(LoadEarMotion_orig)(characterId, dress, personalityType, rank, grade, raceType);
	}

	void* LoadFacialMotion_orig = nullptr;
	void* LoadFacialMotion_hook(int characterId, MasterDressData* dress, int personalityType, int rank, int grade, int raceType) {
		Logger::Info(SECTION_NAME, L"LoadFacialMotion: charaId=%d,dressid=%d,rank=%d,grade=%d", characterId, dress->Id, rank, grade);
		//return nullptr;
		if (Settings::Global->winMotion564) {
			characterId = 1007;
			dress->CharaId = 1007;
			dress->Id = 100701;
			grade = 200;
			//c_raceResultCutinMotionRank = rank;
		}
		else {
			if (Settings::Local->raceResultCutinMotionChara > -1) {
				characterId = Settings::Local->raceResultCutinMotionChara;
				dress->CharaId = Settings::Local->raceResultCutinMotionChara;
			}
			if (Settings::Local->raceResultCutinMotionDress > -1) {
				dress->Id = Settings::Local->raceResultCutinMotionDress;
			}
			if (Settings::Local->raceResultCutinMotionGrade > -1) {
				grade = Settings::Local->raceResultCutinMotionGrade;
			}
			if (Settings::Local->raceResultCutinMotionRank > -1) {
				rank = Settings::Local->raceResultCutinMotionRank;
			}
		}

		return reinterpret_cast<decltype(LoadFacialMotion_hook)*>
			(LoadFacialMotion_orig)(characterId, dress, personalityType, rank, grade, raceType);
	}

	void Init() {
		Logger::Info(SECTION_NAME, L"Init");

		auto LoadBodyMotion_addr = reinterpret_cast<void* (*)(int, MasterDressData*, int, int, int, int)>(
			il2cpp_symbols::get_method_pointer(
				"umamusume.dll", "Gallop",
				"RaceResultCutInHelper", "LoadBodyMotion", 8
			)
			);
		EnableHook(LoadBodyMotion_addr, LoadBodyMotion_hook, reinterpret_cast<void**>(&LoadBodyMotion_orig), L"RaceResultCutInHelper_LoadBodyMotion");

		auto LoadCameraMotion_addr = reinterpret_cast<void* (*)(int, MasterDressData*, int, int, int, int)>(
			il2cpp_symbols::get_method_pointer(
				"umamusume.dll", "Gallop",
				"RaceResultCutInHelper", "LoadCameraMotion", 8
			)
			);
		EnableHook(LoadCameraMotion_addr, LoadCameraMotion_hook, reinterpret_cast<void**>(&LoadCameraMotion_orig), L"RaceResultCutInHelper_LoadCameraMotion");

		auto LoadEarMotion_addr = reinterpret_cast<void* (*)(int, MasterDressData*, int, int, int, int)>(
			il2cpp_symbols::get_method_pointer(
				"umamusume.dll", "Gallop",
				"RaceResultCutInHelper", "LoadEarMotion", 6
			)
			);
		EnableHook(LoadEarMotion_addr, LoadEarMotion_hook, reinterpret_cast<void**>(&LoadEarMotion_orig), L"RaceResultCutInHelper_LoadEarMotion");

		auto LoadFacialMotion_addr = reinterpret_cast<void* (*)(int, MasterDressData*, int, int, int, int)>(
			il2cpp_symbols::get_method_pointer(
				"umamusume.dll", "Gallop",
				"RaceResultCutInHelper", "LoadFacialMotion", 6
			)
			);
		EnableHook(LoadFacialMotion_addr, LoadFacialMotion_hook, reinterpret_cast<void**>(&LoadFacialMotion_orig), L"RaceResultCutInHelper_LoadFacialMotion");
	}
}