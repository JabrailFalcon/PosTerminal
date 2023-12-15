#pragma once
#include "User.h"

class UsersRepo
{
    std::vector<User> users;
    std::vector<int> indentUser;
    std::string fileIdBuffUser;
    std::vector<std::string> sortingname;
    std::vector<User> sortedUsers;
    std::vector<int> idStorage;
    std::string filepath;
public:
    UsersRepo();
    void loadData();
    void saveData();
    void addUser(HWND hDlg, HWND hList, TCHAR Password[100], TCHAR Mobile[100], TCHAR Email[100], 
        TCHAR Role[100], TCHAR Fname[100], TCHAR Lname[100], TCHAR Status[100]);
    void editUser(HWND& hDlg, HWND& EditFname, HWND& EditLname, HWND& EditMobile,
        HWND& EditStatus, HWND& EditEmail, HWND& EditPassword,
        HWND& EditRole, int UserId);
    void displayEdits(int UserId, HWND& EditFname, HWND& EditLname, HWND& editMobile,
        HWND& EditStatus, HWND& EditRole, HWND& EditEmail, HWND& EditPassword);
    void sorting(HWND& hDlg, HWND& EditFname, HWND& hUsersList);
    void sortByName(std::string name);
    void displaySortingUsers(HWND& hUsersList);
    void deleteUser(int index);
    void displayUsers(HWND hDlg, HWND hUsersList);
    bool authenticate(TCHAR login[100], TCHAR pass[100]);
    std::vector<User> getUsers() const;
};
