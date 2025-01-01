#include "Utils.h"

namespace Utils {
	DWORD GetCurrentDisplayHz() {
		DEVMODE devmode;
		memset(&devmode, 0, sizeof(DEVMODE));
		devmode.dmSize = sizeof(DEVMODE);
		devmode.dmFields = DM_DISPLAYFREQUENCY;
		EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devmode);
		return devmode.dmDisplayFrequency;
	}
}