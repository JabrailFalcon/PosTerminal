#pragma once
#include "User.h"

class UsersRepo
{
    std::vector<User> users;
    std::string filepath;
public:
    UsersRepo();
    void loadData();
    void saveData();
    void addUser(const User& newUser);
    void editUser();
    void sort(TCHAR us[100], HWND hDlg, HWND hUsersList) const;
    void deleteUser();
    void clear();
    void displayUsers(HWND hDlg, HWND hUsersList) const;
    bool authenticate(TCHAR login[100], TCHAR pass[100]);
    std::vector<User> getUsers() const;
};
