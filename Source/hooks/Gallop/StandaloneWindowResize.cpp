#include "StandaloneWindowResize.h"

namespace Gallop::StandaloneWindowResize
{
	bool (*get_IsVirt)() = nullptr;

	void Init()
	{
		Logger::Info(SECTION_NAME, L"Init");

		get_IsVirt = reinterpret_cast<bool(*)()>(
			il2cpp_symbols::get_method_pointer(
				"umamusume.dll", "Gallop",
				"StandaloneWindowResize", "get_IsVirt", 0
		));
	}
}