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
    void deleteUser();
    void clear();
    void displayUsers(HWND hDlg, HWND hUsersList) const;
    std::vector<User> getUsers() const;
};
