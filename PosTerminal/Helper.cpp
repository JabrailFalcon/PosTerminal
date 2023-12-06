#include "framework.h"
#include "Helper.h"

std::string Helper::tchar_string(TCHAR* buff)
{
    std::string result = "";
    for (int i = 0; i < lstrlen(buff); i++) {
        result += buff[i];
    }
    return result;
}

TCHAR* Helper::string_tchar(std::string text)
{
    int size1 = text.length() + 1;
    int size2 = (size1 - 1) * 2;
    char* nameC = new char[size1];
    strcpy_s(nameC, size1, text.c_str());
    TCHAR* buff = new TCHAR[size2];
    mbstowcs_s(NULL, buff, size1, nameC, size2);
    delete[] nameC;
    return buff;
}

int Helper::string_int(std::string buff)
{
    return stoi(buff);
}

char* Helper::string_char(std::string text)
{
    int size = text.length();
    char* buff = new char[size + 1] {};
    for (int i = 0; i < size; i++) {
        buff[i] = text[i];
    }
    buff += '\0';

    return buff;
}

TCHAR* Helper::char_tchar(char* text)
{
    TCHAR* buff = new TCHAR[strlen(text) * 2];
    mbstowcs_s(NULL, buff, strlen(text) * 2, text, strlen(text));
    return buff;
}

