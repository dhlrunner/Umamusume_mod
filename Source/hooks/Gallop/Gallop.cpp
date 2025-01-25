#include "Gallop.h"

namespace Gallop
{
	void Init() {
		Logger::Info(L"GALLOPHOOK_MAIN", L"Init");

		Live::Init();
		Live::Cutt::Init();
		LiveTheaterInfo::Init();
		RaceResultScene::Init();
		RaceResultCutInHelper::Init();
		CutIn::Init();
		CharacterBuildInfo_::Init();
		StoryCharacter3D::Init();
		GallopUtil::Init();
		MasterEventMotionData::Init();
		ModelController::Init();
		Screen::Init();

	}
}