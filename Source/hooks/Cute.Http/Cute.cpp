#include "Cute.h"

namespace Cute {
	void Init() {
		Logger::Info(L"CUTEHOOK", L"Init");
		
		//Init Cute.Http
		Http::WWWRequest::Init();
	}
}	