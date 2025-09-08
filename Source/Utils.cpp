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

	std::vector <std::string> explode(const std::string& str,
		const char& ch) {
		std::string next;
		std::vector < std::string > result;

		// For each character in the string
		for (std::string::const_iterator it = str.begin(); it != str.end(); it++) {
			// If we've hit the terminal character
			if (*it == ch) {
				// If we have some characters accumulated
				if (!next.empty()) {
					// Add them to the result vector
					result.push_back(next);
					next.clear();
				}
			}
			else {
				// Accumulate the next character into the sequence
				next += *it;
			}
		}
		if (!next.empty())
			result.push_back(next);
		return result;
	}


	bool StrEndsWith(LPCWSTR path, LPCWSTR suffix)
	{
		if (!path || !suffix) return FALSE;

		size_t pathLen = wcslen(path);
		size_t suffixLen = wcslen(suffix);

		if (pathLen < suffixLen) return FALSE;

		return wcscmp(path + (pathLen - suffixLen), suffix) == 0;
	}

	bool StrEndsWith(std::string const& fullString, std::string const& ending) {
		if (fullString.length() >= ending.length()) {
			return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
		}
		else {
			return false;
		}
	}

	std::string StrReplaceAll(std::string str, const std::string& from, const std::string& to) {
		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
			str.replace(start_pos, from.length(), to);
			start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
		}
		return str;
	}

	std::string ConvertWstringToUTF8(const std::wstring& src)
	{
		if (src.empty()) {
			return std::string();
		}

		int size_needed = WideCharToMultiByte(CP_UTF8, 0, &src[0], (int)src.size(), NULL, 0, NULL, NULL);
		std::string result(size_needed, 0);
		WideCharToMultiByte(CP_UTF8, 0, &src[0], (int)src.size(), &result[0], size_needed, NULL, NULL);
		return result;
	}

	/// <summary>
	/// Get the current time in milliseconds since epoch
	/// </summary>
	/// <returns></returns>
	std::string GetCurrentTimeAsMS()
	{
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch());
		return std::to_string(ms.count());
	}

	/// <summary>
	/// Write a string to a file
	/// </summary>
	/// <param name="file_name"></param>
	/// <param name="buffer"></param>
	/// <param name="len"></param>
	void WriteStrToFile(std::string file_name, char* buffer, int len)
	{
		FILE* fp;
		fopen_s(&fp, file_name.c_str(), "wb");
		if (fp != nullptr) {
			fwrite(buffer, 1, len, fp);
			fclose(fp);
		}
	}

	void RemoveProtection(HMODULE module) 
	{
		if (module == NULL) {
			std::cerr << "GetModuleHandle failed: " << GetLastError() << std::endl;
		}
		MODULEINFO moduleInfo;
		if (!GetModuleInformation(GetCurrentProcess(), module, &moduleInfo, sizeof(moduleInfo))) {
			std::cerr << "GetModuleInformation failed: " << GetLastError() << std::endl;
		}
		SIZE_T moduleSize = moduleInfo.SizeOfImage;
		DWORD oldProtect;
		if (!VirtualProtect(module, moduleSize, PAGE_EXECUTE_READWRITE, &oldProtect)) {
			std::cerr << "VirtualProtect failed: " << GetLastError() << std::endl;
		}

		std::cout << "Memory protection removed" << std::endl;
	}
}