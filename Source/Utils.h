#pragma once
#include <Windows.h>
#include <vector>
#include <string>

namespace Utils
{
	DWORD GetCurrentDisplayHz();
	std::vector <std::string> explode(const std::string& str, const char& ch);
}