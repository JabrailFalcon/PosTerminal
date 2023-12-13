#pragma once
#include "User.h"

class UsersRepo
{
    std::vector<User> users;
    std::string filepath;
    std::vector<User> sortedUsers;
public:
    UsersRepo();
    void loadData();
    void saveData();
    void addUser(HWND& hDlg, HWND& hEditFname, HWND& hEditLname, HWND& hEditRole,
        HWND& hEditMobile, HWND& hEditEmail, HWND& hEditStatus, HWND& hEditPassword);
    void editUser();
    void sort(TCHAR us[100], HWND hDlg, HWND hUsersList) const;
    void deleteUser(HWND& hDlg, HWND& hUsersList);
    void clear();
    void displayUsers(HWND hDlg, HWND hUsersList) const;
    void fillEdit(int index, HWND& hDlg, HWND& hEditFname, HWND& hEditLname, HWND& hEditRole,
        HWND& hEditMobile, HWND& hEditEmail, HWND& hEditStatus, HWND& hEditPassword);
    void sortByName(std::string fName);
    void sortByStatus(std::string status);
    void sortByRole(std::string role);
    void selectSortedUsers(HWND& hDlg, HWND& hUsersList, HWND& hEdit);
    void displaySortUsers(HWND& hUsersList);
    std::vector<User> getUsers() const;
};
