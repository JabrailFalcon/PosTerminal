#pragma once

class Helper {
public:
	std::string tchar_string(TCHAR* buff);
	TCHAR* string_tchar(std::string text);
	int string_int(std::string buff);
	char* string_char(std::string text);
	TCHAR* char_tchar(char* text);
	bool validateDouble(std::string text);
	bool validateInt(std::string text);
};
