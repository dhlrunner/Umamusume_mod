#pragma once
#include "..\..\tools\Logger.hpp"
#include "..\Unity\il2cpp\il2cpp_symbols.hpp"
#include "LiveTheaterInfo.h"
#include "RaceResultScene.h"
#include "RaceResultCutInHelper.h"
#include "Live.h"
#include "Live.Cutt.h"
#include "Live.Cutt.LiveTimelineControl.h"
#include "CutIn.h"
#include "CharacterBuildInfo.h"
#include "StoryCharacter3D.h"
#include "GallopUtil.h"
#include "MasterEventMotionData.h"
#include "ModelController.h"
#include "Screen.h"
#include "SceneManager.h"
#include "GraphicSettings.h"
#include "CutInModelController.h"
#include "ResourcePath.h"
#include "RaceUIFinishOrderFlash.h"
#include "CameraController.h"
#include "SingleModeStartResultCharaViewer.h"
#include "GameSystem.h"
#include "CySpringUpdater.h"

#define SECTION_NAME L"GALLOPHOOK_MAIN"

namespace Gallop {
	void Init();
}