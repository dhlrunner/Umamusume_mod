#include "LibNative.Runtime.h"

namespace LibNative::Runtime
{
	void Init() {
		LibNative::Sqlite3::Init();
		LibNative::Log::Init();
	}
}