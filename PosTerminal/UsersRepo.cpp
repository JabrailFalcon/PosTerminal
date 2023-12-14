#include "framework.h"
//#include "Header.h"
#include "UsersRepo.h"

UsersRepo::UsersRepo() : filepath("Data/Users.json")
{}

void UsersRepo::loadData()
{
    Json::Value data;
    Json::Reader reader;

    std::ifstream fin;
    fin.open(filepath);
    reader.parse(fin, data);
    fin.close();

    int size = data["size"].asInt();

    for (int i = 0; i < size; i++) {
        User us = {
        data["users"][i]["id"].asInt(),
        data["users"][i]["f_name"].asString(),
        data["users"][i]["l_name"].asString(),
        data["users"][i]["role"].asString(),
        data["users"][i]["mobile"].asString(),
        data["users"][i]["email"].asString(),
        data["users"][i]["status"].asString(),
        data["users"][i]["password"].asString()
        };
        users.push_back(us);
    }
}

void UsersRepo::saveData()
{
    
}

void UsersRepo::addUser(const User& newUser)
{
    users.push_back(newUser);
}

void UsersRepo::editUser()
{}

void UsersRepo::sort(TCHAR us[100], HWND hDlg, HWND hUsersList) const
{

}

void UsersRepo::deleteUser()
{}

void UsersRepo::clear()
{
    users.clear();
}

void UsersRepo::displayUsers(HWND hDlg, HWND hUsersList) const
{
    Helper helper;
    HFONT hFont = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial");
    int N = 0;
    for (auto us : users) {
        N++;
        std::string user = std::to_string(N) + "             " + us.getF_name() + " " + us.getL_name() +
            "    " + us.getRole() + "    " + us.getStatus();
        TCHAR* usInfo = helper.string_tchar(user);
        SendMessage(hUsersList, LB_ADDSTRING, 0, LPARAM(usInfo));
        delete[] usInfo;
    }
}

bool UsersRepo::authenticate(TCHAR login[100], TCHAR pass[100])
{
    Helper helper;
    std::string loginBuff = helper.tchar_string(login);
    std::string passBuff = helper.tchar_string(pass);
    // ->
    auto iter = std::find_if(users.begin(), users.end(),
        [loginBuff, passBuff](User& user) {
            return ((user.getF_name() == loginBuff || user.getEmail() == loginBuff || user.getMobile() == loginBuff) && (user.getPassword() == passBuff));
        });
    // ->
    bool result = (iter != users.end());
    // ->
    return result;
}

std::vector<User> UsersRepo::getUsers() const
{
    return users;
}
