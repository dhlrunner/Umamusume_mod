#include "Gallop.h"

namespace Gallop
{
	void Init() {
		Logger::Info(SECTION_NAME, L"Init");
		Gallop::StandaloneWindowResize::Init();
		Live::Init();
		Live::Cutt::Init();
		Live::Cutt::LiveTimelineControl::Init();
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
		SceneManager::Init();
		GraphicSettings::Init();
		CutInModelController::Init();
		ResourcePath::Init();
		RaceUIFinishOrderFlash::Init();
		CameraController::Init();
		SingleModeStartResultCharaViewer::Init();
		GameSystem::Init();
		Gallop::Model::Component::CySpringUpdater::Init();
		Gallop::WorkDressData::Init();
		Gallop::CySpringNative::Init();
		Gallop::MasterDataManager::Init();
	}
}