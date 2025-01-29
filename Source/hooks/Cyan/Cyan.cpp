#include "Cyan.h"


namespace Cyan
{
	void Init()
	{
		Logger::Info(SECTION_NAME, L"Init");
		Loader::AssetLoader::Init();
	}
}