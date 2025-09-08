#include "Gallop.h"

namespace Gallop
{
	void Init() {
		Logger::Info(SECTION_NAME, L"Init");
		StandaloneWindowResize::Init();
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
		Model::Component::CySpringUpdater::Init();
		WorkDressData::Init();
		CySpringNative::Init();
		MasterDataManager::Init();
		ModelLoader::Init();
		EditableCharacterBuildInfo::Init();
		CutIn::CutInCharacter::Init();
		UIManager::Init();
		MasterLiveFixMemberData::Init();
		MasterLiveData::Init();
		MasterDressData_::Init();
		ResourceManager::Init();
	}
}