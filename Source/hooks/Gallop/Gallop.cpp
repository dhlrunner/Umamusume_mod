#include "Gallop.h"

namespace Gallop
{
	void Init() {
		Logger::Info(SECTION_NAME, L"Init");
		LiveTheaterInfo::Init();
		RaceResultScene::Init();
	}
}