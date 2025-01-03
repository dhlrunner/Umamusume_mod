#include "Gallop.h"

namespace Gallop
{
	void Init() {
		Logger::Info(L"GALLOPHOOK_MAIN", L"Init");
		LiveTheaterInfo::Init();
		RaceResultScene::Init();
		RaceResultCutInHelper::Init();
	}
}