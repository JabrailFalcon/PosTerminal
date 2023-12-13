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
    Json::Value data;
    Json::StyledStreamWriter writer;

    int size = users.size();
    data["size"] = size;

    int i = 0;
    for (auto& user : users) {
        data["users"][i]["id"] = user.getId();
        data["users"][i]["f_name"] = user.getF_name();
        data["users"][i]["l_name"] = user.getL_name();
        data["users"][i]["role"] = user.getRole();
        data["users"][i]["mobile"] = user.getMobile();
        data["users"][i]["email"] = user.getEmail();
        data["users"][i]["status"] = user.getStatus();
        data["users"][i]["password"] = user.getPassword();
        i++;
    }

    std::ofstream fout;
    fout.open(filepath);
    writer.write(fout, data);
    fout.close();
}

void UsersRepo::addUser(HWND& hDlg, HWND& hEditFname, HWND& hEditLname, HWND& hEditRole,
    HWND& hEditMobile, HWND& hEditEmail, HWND& hEditStatus, HWND& hEditpassword)
{
    Helper helper;
    int id = 0;
    bool nice = false;
    TCHAR buff[100];

    std::string fName, lName, role, mobile, email, status, password;

    // first name
    GetWindowText(hEditFname, buff, 100);
    if (lstrlen(buff) == 0) {
        MessageBox(hDlg, L"User first name is empty", L"Warning", MB_OK || MB_ICONWARNING);
        SetFocus(hEditFname);
    }
    else {
        fName = helper.tchar_string(buff);
        GetWindowText(hEditLname, buff, 100);
    }

    // last name
    if (lstrlen(buff) == 0) {
        MessageBox(hDlg, L"User last name is empty", L"Warning", MB_OK || MB_ICONWARNING);
        SetFocus(hEditLname);
    }
    else {
        lName = helper.tchar_string(buff);
        GetWindowText(hEditRole, buff, 100);
    }

    // role
    if (lstrlen(buff) == 0) {
        MessageBox(hDlg, L"User role is empty", L"Warning", MB_OK || MB_ICONWARNING);
        SetFocus(hEditRole);
    }
    else {
        role = helper.tchar_string(buff);
        GetWindowText(hEditMobile, buff, 100);
    }

    // mobile
    if (lstrlen(buff) == 0) {
        MessageBox(hDlg, L"User mobile is empty", L"Warning", MB_OK || MB_ICONWARNING);
        SetFocus(hEditMobile);
    }
    else {
        mobile = helper.tchar_string(buff);
        GetWindowText(hEditEmail, buff, 100);
    }

    // email
    if (lstrlen(buff) == 0) {
        MessageBox(hDlg, L"User email is empty", L"Warning", MB_OK || MB_ICONWARNING);
        SetFocus(hEditEmail);
    }
    else {
        email = helper.tchar_string(buff);
        GetWindowText(hEditRole, buff, 100);
    }

    // status
    if (lstrlen(buff) == 0) {
        MessageBox(hDlg, L"User status is empty", L"Warning", MB_OK || MB_ICONWARNING);
        SetFocus(hEditStatus);
    }
    else {
        status = helper.tchar_string(buff);
        GetWindowText(hEditpassword, buff, 100);
    }

    // password
    if (lstrlen(buff) == 0) {
        MessageBox(hDlg, L"User password is empty", L"Warning", MB_OK || MB_ICONWARNING);
        SetFocus(hEditpassword);
        return;
    }
    else {
        password = helper.tchar_string(buff);
        nice = true;
    }
    if (nice == true) {
        User user{ id, fName, lName, role, mobile, email, status, password };
        users.push_back(user);
        Json::Value data;
        int size = users.size() + 1;
        data["size"] = size;
        saveData();
    }
}

void UsersRepo::editUser()
{
    
}

void UsersRepo::sort(TCHAR us[100], HWND hDlg, HWND hUsersList) const
{

}

void UsersRepo::deleteUser(HWND& hDlg, HWND& hUsersList)
{
    int index = SendMessage(hUsersList, LB_GETCURSEL, 0, 0);
    if (index >= 0) {
        users.erase(users.begin() + index);
        saveData();
    }
    else {
        MessageBox(hDlg, L"Select user in the list to delete it!", L"Warning", MB_OK || MB_ICONWARNING);
    }
}

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
            "                                                  " + us.getRole() 
            + "                                          " + us.getStatus();
        TCHAR* usInfo = helper.string_tchar(user);
        SendMessage(hUsersList, LB_ADDSTRING, 0, LPARAM(usInfo));
        delete[] usInfo;
    }
}

void UsersRepo::fillEdit(int index, HWND& hDlg, HWND& hEditFname, HWND& hEditLname, 
    HWND& hEditRole, HWND& hEditMobile, HWND& hEditEmail, HWND& hEditStatus, HWND& hEditpassword)
{
    Helper helper;

    TCHAR* buff = helper.string_tchar(users[index].getF_name());
    SetWindowText(hEditFname, buff);
    delete[] buff;

    buff = helper.string_tchar(users[index].getL_name());
    SetWindowText(hEditLname, buff);
    delete[] buff;

    buff = helper.string_tchar(users[index].getRole());
    SetWindowText(hEditRole, buff);
    delete[] buff;
    
    buff = helper.string_tchar(users[index].getMobile());
    SetWindowText(hEditMobile, buff);
    delete[] buff;

    buff = helper.string_tchar(users[index].getEmail());
    SetWindowText(hEditEmail, buff);
    delete[] buff;

    buff = helper.string_tchar(users[index].getStatus());
    SetWindowText(hEditStatus, buff);
    delete[] buff;

    buff = helper.string_tchar(users[index].getPassword());
    SetWindowText(hEditpassword, buff);
    delete[] buff;
}

void UsersRepo::sortByName(std::string fName)
{
    std::copy_if(users.begin(), users.end(), std::back_inserter(sortedUsers),
        [fName](User& u) { return u.getF_name() == fName; });
}

void UsersRepo::sortByStatus(std::string status)
{
    std::copy_if(users.begin(), users.end(), std::back_inserter(sortedUsers),
        [status](User& u) { return u.getStatus() == status; });
}

void UsersRepo::sortByRole(std::string role)
{
    std::copy_if(users.begin(), users.end(), std::back_inserter(sortedUsers),
        [role](User& u) { return u.getRole() == role; });
}

void UsersRepo::selectSortedUsers(HWND& hDlg, HWND& hUsersList, HWND& hEdit1)
{
    sortedUsers.clear();

    Helper helper;
    TCHAR text[100];
    GetDlgItemText(hDlg, IDC_COMBO_SORT_BY_USER, text, 100);

    std::string stringtext = helper.tchar_string(text);
    int choice = -1;

    if (stringtext == "Name") choice = 0;
    if (stringtext == "Role") choice = 1;
    if (stringtext == "Status") choice = 2;

    switch (choice) {
    case 0:
    {
        GetWindowText(hEdit1, text, 100);
        if (lstrlen(text) == 0) {
            MessageBox(hDlg, L"Enter product name", L"Warning", MB_OK || MB_ICONWARNING);
            SetFocus(hEdit1);
            return;
        }
        else {
            sortByName(helper.tchar_string(text));
        }
    }
    break;
    case 1:
    {
        GetDlgItemText(hDlg, IDC_COMBO_STATUS_USER, text, 100);
        sortByStatus(helper.tchar_string(text));
    }
    break;
    case 2:
    {
        GetDlgItemText(hDlg, IDC_COMBO_ROLE_USER, text, 100);
        sortByRole(helper.tchar_string(text));
    }
    break;
    default:
    {
        MessageBox(hDlg, L"Something went wrong", L"Warning", MB_OK || MB_ICONWARNING);
    }
    break;
    }

    if (sortedUsers.empty()) {
        MessageBox(hDlg, L"Users with this atributes did not find", L"Warning", MB_OK || MB_ICONWARNING);
        SetWindowText(hEdit1, 0);
    }
    else {
        SendMessage(hUsersList, LB_RESETCONTENT, 0, 0);
        displaySortUsers(hUsersList);
    }
}

void UsersRepo::displaySortUsers(HWND& hUsersList)
{
    Helper helper;
    TCHAR* pInfo;
    std::string user;

    int i = 1;
    for (auto& uS : sortedUsers) {
        std::stringstream ss;
        ss << std::left << std::setw(10) << i++
            << std::setw(10) << uS.getF_name()
            << std::setw(50) << uS.getL_name()
            << std::setw(45) << uS.getRole()
            << std::setw(15) << uS.getStatus();
        user = ss.str();
        pInfo = helper.string_tchar(user);
        SendMessage(hUsersList, LB_ADDSTRING, 0, LPARAM(pInfo));
        delete[] pInfo;
    }
}

std::vector<User> UsersRepo::getUsers() const
{
    return users;
}
