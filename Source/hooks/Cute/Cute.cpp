#include "Cute.h"

namespace Cute {
	void Init() {
		Logger::Info(SECTION_NAME, L"Init");
		
		//Init Cute.Http
		Http::WWWRequest::Init();
		Core::Device::Init();
	}
}	