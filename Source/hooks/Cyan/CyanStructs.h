#pragma once
#include "../Unity/il2cpp/il2cpp-class-internals.h"

namespace Cyan
{
	//Cyan.Loader.AssetLoader+AssetRequest
	struct AssetRequest {
		char dummy[0xF];
		unsigned char kind;
		unsigned char state;
		char dummy1[0x7];
		Il2CppString* hname;
		Il2CppString* path;
	};
}