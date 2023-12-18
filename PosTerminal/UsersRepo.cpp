#include "framework.h"
//#include "Header.h"
#include "UsersRepo.h"

UsersRepo::UsersRepo() : filepath("Data/Users.json")
{}

void UsersRepo::loadData()
{
    users.clear();
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
    indentUser.clear();
    //
    Json::Value data;
    Json::Value nList;

    for (int i = 0; i < users.size(); i++) {
        nList["id"] = users[i].getId();
        nList["f_name"] = users[i].getF_name();
        nList["l_name"] = users[i].getL_name();
        nList["role"] = users[i].getRole();
        nList["mobile"] = users[i].getMobile();
        nList["email"] = users[i].getEmail();
        nList["status"] = users[i].getStatus();
        nList["password"] = users[i].getPassword();
        // ->

        data["users"][i] = nList;
        //
        indentUser.push_back(users[i].getId());
    }

    data["size"] = users.size();

    std::ofstream fout;
    Json::StyledStreamWriter writer;
    //->
    fout.open(filepath);
    writer.write(fout, data);
    fout.close();
}

void UsersRepo::addUser(HWND hDlg, HWND hList, TCHAR Password[100], TCHAR Mobile[100], 
    TCHAR Email[100], TCHAR Role[100], TCHAR Fname[100], TCHAR Lname[100], TCHAR Status[100])
{
    Helper helper;
    char buff1[100];
    char buff2[100];
    char buff3[100];
    char buff4[100];
    char buff5[100];
    char buff6[100];
    char buff7[100];
    int id = users.back().getId() + 1;

    wcstombs_s(NULL, buff1, Fname, 100);
    wcstombs_s(NULL, buff2, Lname, 100);
    wcstombs_s(NULL, buff3, Role, 100);
    wcstombs_s(NULL, buff4, Mobile, 100);
    wcstombs_s(NULL, buff5, Email, 100);
    wcstombs_s(NULL, buff6, Status, 100);
    wcstombs_s(NULL, buff7, Password, 100);

    User us(id, buff1, buff2, buff3, buff4, buff5, buff6, buff7);

    users.push_back(us);
    indentUser.push_back(id);

    int n = indentUser.size();

    std::string user = std::to_string(n) + "               " + us.getF_name() + " " + us.getL_name() + "                          " + 
        us.getRole() + "                                            " + us.getStatus();
    TCHAR* pInfo = helper.string_tchar(user);
    SendMessage(hList, LB_ADDSTRING, 0, LPARAM(pInfo));
    delete[] pInfo;

    // ->
    std::ofstream fout;
    fout.open(fileIdBuffUser);
    int i = 0;
    for (auto& in : indentUser) {
        fout << indentUser[i] << std::endl;
        i++;
    }
    fout.close();

    //saveData();
}

void UsersRepo::editUser(HWND& hDlg, HWND& EditFname, HWND& EditLname, HWND& EditMobile,
    HWND& EditStatus, HWND& EditEmail, HWND& EditPassword,
    HWND& EditRole, int UserId)
{
    Helper helper;
    std::string fName, lName, mobile, email, password, role, status;
    int id = 0;
    TCHAR buff[100];

    GetDlgItemText(hDlg, IDC_COMBO_ROLE_AD_USER, buff, 100);
    role = helper.tchar_string(buff);

    GetDlgItemText(hDlg, IDC_COMBO_STATUS_AD_USER, buff, 100);
    status = helper.tchar_string(buff);

    GetWindowText(EditFname, buff, 100);
    fName = helper.tchar_string(buff);

    GetWindowText(EditLname, buff, 100);
    lName = helper.tchar_string(buff);

    GetWindowText(EditMobile, buff, 100);
    mobile = helper.tchar_string(buff);

    GetWindowText(EditPassword, buff, 100);
    password = helper.tchar_string(buff);

    GetWindowText(EditEmail, buff, 100);
    email = helper.tchar_string(buff);
    
    std::vector<User>::iterator iterat;

    iterat = std::find_if(users.begin(), users.end(), [UserId](User& u) { return u.getId() == UserId; });
    id = iterat->getId();
    users.erase(iterat);
    User user{ id, fName, lName, role, mobile, email, status, password };
    users.resize(users.size() + 1);
    iterat = users.begin() + id - 1;
    users.insert(iterat, user);
    users.pop_back();
    //saveData();
}

void UsersRepo::displayEdits(int UserId, HWND& EditFname, HWND& EditLname, HWND& editMobile,
    HWND& EditStatus, HWND& EditRole, HWND& EditEmail, HWND& EditPassword)
{
    Helper helper;

    auto iterator = std::find_if(users.begin(), users.end(), [UserId](User& u)
        { return u.getId() == UserId; });

    TCHAR* buff = helper.string_tchar(iterator->getF_name());
    SetWindowText(EditFname, buff);
    delete[] buff;

    buff = helper.string_tchar(iterator->getL_name());
    SetWindowText(EditLname, buff);
    delete[] buff;

    buff = helper.string_tchar(iterator->getMobile());
    SetWindowText(editMobile, buff);
    delete[] buff;

    buff = helper.string_tchar(iterator->getEmail());
    SetWindowText(EditEmail, buff);
    delete[] buff;

    buff = helper.string_tchar(iterator->getPassword());
    SetWindowText(EditPassword, buff);
    delete[] buff;

    // ComboBox
    buff = helper.string_tchar(iterator->getRole());
    int i = SendMessage(EditRole, CB_FINDSTRING, -1, (LPARAM)buff);
    delete[] buff;
    SendMessage(EditRole, CB_SETCURSEL, i, 0);

    buff = helper.string_tchar(iterator->getStatus());
    int x = SendMessage(EditStatus, CB_FINDSTRING, -1, (LPARAM)buff);
    delete[] buff;
    SendMessage(EditStatus, CB_SETCURSEL, x, 0);
    
}

void UsersRepo::sorting(HWND& hDlg, HWND& EditFname, HWND& hUsersList)
{
    Helper helper;
    sortedUsers.clear();

    TCHAR text[100];
    GetDlgItemText(hDlg, IDC_SORT_BY_USER, text, 100);
    int sortBy = -1;
    std::string stringtext = helper.tchar_string(text);


    if (stringtext == "Name") sortBy = 0;
    if (stringtext == "Role") sortBy = 1;
    if (stringtext == "Status") sortBy = 2;

    switch (sortBy)
    {
    case 0:
    {
        GetDlgItemText(hDlg, IDC_EDIT_SEARCH_USER, text, 100);
        GetWindowText(EditFname, text, 100);
        if (lstrlen(text) == 0) {
            MessageBox(hDlg, L"Enter user first name", L"Warning", MB_OK || MB_ICONWARNING);
            SetFocus(EditFname);
            return;
        }
        else {
            sortByName(helper.tchar_string(text));
        }
    }
    break;

    case 1:
    {
        GetDlgItemText(hDlg, IDC_COMBO_ROLE_USER, text, 100);
        sortByRole(helper.tchar_string(text));
    }
    break;

    case 2:
    {
        GetDlgItemText(hDlg, IDC_COMBO_STATUS_USER, text, 100);
        sortByStatus(helper.tchar_string(text));
    }
    break;

    default:
    {
        MessageBox(hDlg, L"Something went wrong", L"Warning", MB_OK || MB_ICONWARNING);
    }
    break;
    }

    if (sortedUsers.empty()) {
        MessageBox(hDlg, L"There are no users matching your filter", L"Warning", MB_OK || MB_ICONWARNING);
        SetWindowText(EditFname, 0);
    }
    else {
        SendMessage(hUsersList, LB_RESETCONTENT, 0, 0);
        displaySortingUsers(hUsersList);
    }
}

void UsersRepo::sortByName(std::string name)
{
    std::copy_if(users.begin(), users.end(), std::back_inserter(sortedUsers),
        [name](User& u) { return u.getF_name() == name; });
}

void UsersRepo::sortByStatus(std::string status)
{
    std::copy_if(users.begin(), users.end(), std::back_inserter(sortedUsers),
        [status](User& u) { return u.getStatus() == status; });
}

void UsersRepo::generatePassword(HWND hDlg, HWND& hEdit)
{
    Helper helper;
    int number = 0;
    std::string pwrd = "Abp_";
    std::string endPwrd = "_F!S";
    do {
        srand(time(0));
        number = rand() % 989999 + 100;
        pwrd += std::to_string(number);
        pwrd += endPwrd;
        number = rand() % 989999 + 10000;
        pwrd += std::to_string(number);
        SetWindowText(hEdit, helper.string_tchar(pwrd));
        break;

    } while (true);
    std::string pwrdString = "  Your password is: \n " + pwrd;
    TCHAR* passwordBox = helper.string_tchar(pwrdString);
    MessageBox(hDlg, passwordBox, L"Info!", MB_OK | MB_ICONINFORMATION);
}

void UsersRepo::sortByRole(std::string role)
{
    std::copy_if(users.begin(), users.end(), std::back_inserter(sortedUsers),
        [role](User& u) { return u.getRole() == role; });
}

void UsersRepo::displaySortingUsers(HWND& hUsersList)
{
    Helper helper;
    idStorage.clear();

    TCHAR* pInfo;
    std::string user;

    int i = 1;
    for (auto& u : sortedUsers) {

        idStorage.push_back(u.getId());

        std::stringstream us;
        us << std::left << std::setw(10) << i++
            << std::setw(10) << u.getF_name()
            << std::setw(10) << u.getL_name()
            << std::setw(50) << u.getRole()
            << std::setw(45) << u.getStatus();
        user = us.str();
        pInfo = helper.string_tchar(user);
        SendMessage(hUsersList, LB_ADDSTRING, 0, LPARAM(pInfo));
        delete[] pInfo;
    }
}

void UsersRepo::deleteUser(int index)
{
    /*int id = indentUser[index];
    auto iter = std::find_if(users.begin(), users.end(),
        [id](User& u) {
            return (u.getId() == id);
        });
    if (iter != users.end()) {
        users.erase(iter);
    }


    saveData();*/
    users.erase(users.begin() + index);
    //saveData();
}

void UsersRepo::displayUsers(HWND hDlg, HWND hUsersList)
{   
    indentUser.clear();
    Helper helper;
    HFONT hFont = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial");
    int N = 0;
    for (auto us : users) {
        N++;
        std::string user = std::to_string(N) + "             " + us.getF_name() + "   " + us.getL_name() +
            "                                                                                                    " + 
            "                    " + us.getRole() + "                                                         "
            + us.getStatus();
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
            return ((user.getF_name() == loginBuff || user.getEmail() == loginBuff || 
                user.getMobile() == loginBuff) && (user.getPassword() == passBuff));
        });
    // ->
    bool result = (iter != users.end());
    // ->
    return result;
}

void UsersRepo::banUnban(HWND& hDlg, int UserId)
{
    Helper helper;

    auto iterator = std::find_if(users.begin(), users.end(), [UserId](User& u)
        { return u.getId() == UserId + 1; });

    std::string F_name = iterator->getF_name();
    std::string L_name = iterator->getL_name();
    std::string Mobile = iterator->getMobile();
    std::string Status = iterator->getStatus();
    std::string Role = iterator->getRole();
    std::string Email = iterator->getEmail();
    std::string Password = iterator->getPassword();

    if (Status == "on") {
        Status = "off";
        MessageBox(hDlg, L"  User was succefully banned", L"Info!", MB_OK | MB_ICONINFORMATION);
    }
    else {
        Status = "on";
        MessageBox(hDlg, L"  User was succefully unbanned", L"Info!", MB_OK | MB_ICONINFORMATION);
    }
    users.erase(iterator);
    User user{UserId, F_name, L_name, Role, Mobile, Email, Status, Password};
    users.resize(users.size() + 1);
    iterator = users.begin() + UserId;
    users.insert(iterator, user);
    users.pop_back();

    //MessageBox(hDlg, F_name, L"Info!", MB_OK | MB_ICONINFORMATION);
}

std::vector<User> UsersRepo::getUsers() const
{
    return users;
}
