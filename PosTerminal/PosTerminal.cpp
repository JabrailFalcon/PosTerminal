// PosTerminal.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "PosTerminal.h"
#include "ProductsRepo.h"
#include "UsersRepo.h"

#define MAX_LOADSTRING 100

//* Description
HWND hEdit1, hEdit2, hEdit3, hEdit4, hEdit5, hEdit6, hEdit7, hEdit8, hEdit9;
HWND hBtnLogin, hBtnClose, hBtnTerminal, hBtnProduct, hBtnPricing, hBtnLocation, hBtnClient, hBtnUsers, hBtnSupliers, hBtnReports;
HWND hBtnAdd, hBtnDel, hBtnPay, hBtnSelect, hBtnEdit, hBtnCategory, hBtnGenerate, hBtnMovement, hBtnApply1, hBtnApply2, hBtnSave;
HWND hCombo1, hCombo2, hCombo3;
HWND hList, hProductsList, hUsersList;
HWND hDataFrom, hDataTo;

//* GLOBAL Variers:
bool isAuthorize = true;
bool isAdmin = true;
bool continueProcess = true;
Helper helper;
//* Products
auto productsRepo = std::make_unique<ProductsRepo>();

//* Users:
auto usersRepo = std::make_unique<UsersRepo>();

// ------


// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Authorization(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    MainWindow(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Terminal(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Products(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AddProduc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Users(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AddUser(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Location(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AddLocation(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Pricing(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Clients(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Supliers(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Report(HWND, UINT, WPARAM, LPARAM);

// 1
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_POSTERMINAL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_POSTERMINAL));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}


// 2
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_POSTERMINAL));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_POSTERMINAL);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

// 3
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

// 4
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        do {
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG18), hWnd, Authorization);
            if (!isAuthorize) {
                DestroyWindow(hWnd);
                continueProcess = false;
            }
            else {
                if (isAdmin) {
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, MainWindow);
                    DestroyWindow(hWnd);
                    continueProcess = false;
                }
                else {
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG16), hWnd, Terminal);
                    DestroyWindow(hWnd);
                    continueProcess = false;
                }
            }
        } while (continueProcess);

    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {

        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 5 -----------------  Authorization  --------------------
INT_PTR CALLBACK Authorization(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        // 1 Descriptors
        hEdit1 = GetDlgItem(hDlg, IDC_EDIT1);
        hEdit2 = GetDlgItem(hDlg, IDC_EDIT2);
        // 2
        hBtnLogin = GetDlgItem(hDlg, IDC_btn_Login);
        hBtnClose = GetDlgItem(hDlg, IDC_Btn_Cancel);
    }
    return (INT_PTR)TRUE;


    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        TCHAR buff1[100];
        TCHAR buff2[200];
        if (wmId == IDC_btn_Login) {
            GetWindowText(hEdit1, buff1, 100);
            if (lstrlen(buff1) == 0) {
                MessageBox(hDlg, L"Login is empty!", L"Warning!", MB_OK | MB_ICONWARNING);
                SetFocus(hEdit1);
            }
            else {
                GetWindowText(hEdit2, buff2, 100);
                if (lstrlen(buff2) == 0) {
                    MessageBox(hDlg, L"Password is empty!", L"Warning!", MB_OK | MB_ICONWARNING);
                    SetFocus(hEdit2);
                }
                else {
                    // Authorization ...
                    //isAuthorize = usersRepo->authenticate(buff1, buff2);
                    if (!isAuthorize) {
                        MessageBox(hDlg, L"Users not found!", L"Notification", MB_OK | MB_ICONERROR);
                        SetWindowText(hEdit1, L"");
                        SetWindowText(hEdit2, L"");
                        SetFocus(hEdit1);
                    }
                    else {
                        EndDialog(hDlg, wmId);
                    }
                }
            }

        }
        else if (wmId == IDC_Btn_Cancel) {
            EndDialog(hDlg, wmId);
            return (INT_PTR)TRUE;
        }
        else if (wmId == IDOK || wmId == IDCANCEL)
        {

            EndDialog(hDlg, wmId);
            return (INT_PTR)TRUE;
        }
        break;
    }
    }
    return (INT_PTR)FALSE;
}

// 6 -----------------  Main Window  ----------------------
INT_PTR CALLBACK MainWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        // Description
        hBtnTerminal = GetDlgItem(hDlg, IDC_BUTTON_Terminal);
        hBtnProduct = GetDlgItem(hDlg, IDC_BUTTON_Product);
        hBtnPricing = GetDlgItem(hDlg, IDC_BUTTON_Pricing);
        hBtnLocation = GetDlgItem(hDlg, IDC_BUTTON_Location);
        hBtnClient = GetDlgItem(hDlg, IDC_BUTTON_Client);
        hBtnUsers = GetDlgItem(hDlg, IDC_BUTTON_Users);
        hBtnSupliers = GetDlgItem(hDlg, IDC_BUTTON_Supliers);
        hBtnReports = GetDlgItem(hDlg, IDC_BUTTON_Reports);
    }
    return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        {
            if (wmId == IDC_BUTTON_Terminal) {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG16), hDlg, Terminal);
            }
            else if (wmId == IDC_BUTTON_Product) {

                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG3), hDlg, Products);

            }
            else if (wmId == IDC_BUTTON_Pricing) {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG15), hDlg, Pricing);
            }
            else if (wmId == IDC_BUTTON_Location) {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG10), hDlg, Location);
            }
            else if (wmId == IDC_BUTTON_Client) {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG6), hDlg, Clients);
            }
            else if (wmId == IDC_BUTTON_Users) {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG4), hDlg, Users);
            }
            else if (wmId == IDC_BUTTON_Supliers) {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG8), hDlg, Supliers);
            }
            else if (wmId == IDC_BUTTON_Reports) {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG19), hDlg, Report);
            }
            else if (wmId == IDOK || wmId == IDCANCEL)
            {
                EndDialog(hDlg, wmId);
                return (INT_PTR)TRUE;
            }
            break;
        }
    }
    return (INT_PTR)FALSE;
}

// 7 -----------------  Terminal  ----------------------
INT_PTR CALLBACK Terminal(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        // Description
        hBtnClose = GetDlgItem(hDlg, IDC_BTN_Close);
        hBtnAdd = GetDlgItem(hDlg, IDC_BTN_Add_Product);
        hBtnDel = GetDlgItem(hDlg, IDC_BTN_Del);
        hBtnPay = GetDlgItem(hDlg, IDC_BTN_Pay);
    }
    return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        {
            if (wmId == IDC_BTN_Add_Product) {

            }
            else if (wmId == IDC_BTN_Del) {

            }
            else if (wmId == IDC_BTN_Pay) {

            }
            else if (wmId == IDC_BTN_Close) {
                EndDialog(hDlg, wmId);
                return (INT_PTR)TRUE;
            }
            else if (wmId == IDOK || wmId == IDCANCEL)
            {
                EndDialog(hDlg, wmId);
                return (INT_PTR)TRUE;
            }
            break;
        }
    }
    return (INT_PTR)FALSE;
}

// 8 -----------------  Products  ----------------------
INT_PTR CALLBACK Products(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        // Description
        hBtnCategory = GetDlgItem(hDlg, IDC_BTN_Category);
        hBtnAdd = GetDlgItem(hDlg, IDC_BTN_AddProdact1);
        hBtnSelect = GetDlgItem(hDlg, IDC_BTN_Select);
        hBtnEdit = GetDlgItem(hDlg, IDC_BTN_EditP);
        hBtnDel = GetDlgItem(hDlg, IDC_BTN_DelP);
        hBtnClose = GetDlgItem(hDlg, IDC_BTN_CloseP);
        //...
        hProductsList = GetDlgItem(hDlg, IDC_LIST_PRODUCTS);

        // Load Data
        productsRepo->loadData();
        productsRepo->displayAllProducts(hDlg, hProductsList);
        /*std::vector<Product> buff = productsRepo->getProducts();
        for (auto& p : buff) {
            TCHAR* pInfo = helper.string_tchar(p.getSKU());
            SendMessage(hProductsList, LB_ADDSTRING, 0, LPARAM(pInfo));
            delete[] pInfo;
        }*/
    }
    return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        {
            if (wmId == IDC_BTN_Category) {

            }
            else if (wmId == IDC_BTN_AddProdact1) {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hDlg, AddProduc);
            }
            else if (wmId == IDC_BTN_Select) {

            }
            else if (wmId == IDC_BTN_EditP) {

            }
            else if (wmId == IDC_BTN_DelP) {

            }
            else if (wmId == IDC_BTN_CloseP) {
                EndDialog(hDlg, wmId);
                return (INT_PTR)TRUE;
            }
            else if (wmId == IDOK || wmId == IDCANCEL)
            {
                EndDialog(hDlg, wmId);
                return (INT_PTR)TRUE;
            }
            break;
        }
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK AddProduc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        // Description
        hEdit1 = GetDlgItem(hDlg, IDC_EDIT_SKU);
        hEdit2 = GetDlgItem(hDlg, IDC_EDIT_PRODNAME);
        hEdit2 = GetDlgItem(hDlg, IDC_EDIT_DESCRIPTION);
        hCombo1 = GetDlgItem(hDlg, IDC_COMBO_CATEGORY);
        hBtnGenerate = GetDlgItem(hDlg, IDC_BTN_SKU);
        hBtnAdd = GetDlgItem(hDlg, IDC_BTN_ADD3);
        hBtnClose = GetDlgItem(hDlg, IDC_BTN_CANCEL3);
    }
    return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        {
            if (wmId == IDC_BTN_SKU) {

            }
            else if (wmId == IDC_BTN_ADD3) {

            }
            else if (wmId == IDC_BTN_CANCEL3) {
                EndDialog(hDlg, wmId);
                return (INT_PTR)TRUE;
            }
            else if (wmId == IDOK || wmId == IDCANCEL)
            {
                EndDialog(hDlg, wmId);
                return (INT_PTR)TRUE;
            }
            break;
        }
    }
    return (INT_PTR)FALSE;
}

// 9 -----------------  Users  ----------------------
INT_PTR CALLBACK Users(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        // Description
        hBtnAdd = GetDlgItem(hDlg, IDC_BTN_AddUser);
        hBtnSelect = GetDlgItem(hDlg, IDC_BTN_Select2);
        hBtnEdit = GetDlgItem(hDlg, IDC_BTN_Edit2);
        hBtnDel = GetDlgItem(hDlg, IDC_BTN_Del2);
        hBtnClose = GetDlgItem(hDlg, IDC_BTN_Close2);

        // mine
        hUsersList = GetDlgItem(hDlg, IDC_LIST_USERS);

        // actions
        usersRepo->loadData();
        usersRepo->displayUsers(hDlg, hUsersList);

    }
    return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        {
            if (wmId == IDC_BTN_AddUser) {

            }
            else if (wmId == IDC_BTN_Select2) {

            }
            else if (wmId == IDC_BTN_Edit2) {

            }
            else if (wmId == IDC_BTN_Del2) {

            }
            else if (wmId == IDC_BTN_Close2) {
                EndDialog(hDlg, wmId);
                return (INT_PTR)TRUE;
            }
            else if (wmId == IDOK || wmId == IDCANCEL)
            {
                EndDialog(hDlg, wmId);
                return (INT_PTR)TRUE;
            }
            break;
        }
    }
    return (INT_PTR)FALSE;
}

// 9 ----------------- Location ---------------------
INT_PTR CALLBACK Location(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        // Description
        hEdit1 = GetDlgItem(hDlg, IDC_EDIT_SERCH_LOC);
        hList = GetDlgItem(hDlg, IDC_LIST_LOC);
        hBtnAdd = GetDlgItem(hDlg, IDC_BTN_ADDLOCATION);
        hBtnSelect = GetDlgItem(hDlg, IDC_BTN_SELECT3);
        hBtnEdit = GetDlgItem(hDlg, IDC_BTN_EDIT_LOC);
        hBtnDel = GetDlgItem(hDlg, IDC_BTN_DEL_LOC);
        hBtnMovement = GetDlgItem(hDlg, IDC_BTN_MOVEMENT);
        hBtnClose = GetDlgItem(hDlg, IDC_BTN_CLOSE_LOC);
    }
    return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        {
            if (wmId == IDC_BTN_ADDLOCATION) {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG11), hDlg, AddLocation);
            }
            else if (wmId == IDC_BTN_SELECT3) {

            }
            else if (wmId == IDC_BTN_EDIT_LOC) {

            }
            else if (wmId == IDC_BTN_DEL_LOC) {

            }
            else if (wmId == IDC_BTN_MOVEMENT) {

            }
            else if (wmId == IDC_BTN_CLOSE_LOC) {
                EndDialog(hDlg, wmId);
                return (INT_PTR)TRUE;
            }
            else if (wmId == IDOK || wmId == IDCANCEL)
            {
                EndDialog(hDlg, wmId);
                return (INT_PTR)TRUE;
            }
            break;
        }
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK AddLocation(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        // Description
        hEdit1 = GetDlgItem(hDlg, IDC_EDIT_LOC_NAME);
        hEdit2 = GetDlgItem(hDlg, IDC_EDIT_LOC_ADRESS);
        hBtnSave = GetDlgItem(hDlg, IDC_BTN_SAVE_NEW_LOC);
        hBtnClose = GetDlgItem(hDlg, IDC_BTN_CANCEL_NLOC);
    }
    return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        {
            if (wmId == IDC_BTN_SAVE_NEW_LOC) {

            }
            else if (wmId == IDC_BTN_CANCEL_NLOC) {
                EndDialog(hDlg, wmId);
                return (INT_PTR)TRUE;
            }
            else if (wmId == IDOK || wmId == IDCANCEL)
            {
                EndDialog(hDlg, wmId);
                return (INT_PTR)TRUE;
            }
            break;
        }
    }
    return (INT_PTR)FALSE;
}

// 10 ----------------- Pricing ---------------------
INT_PTR CALLBACK Pricing(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        // Description 
        hEdit1 = GetDlgItem(hDlg, IDC_EDIT_SEARCH_PR);
        hList = GetDlgItem(hDlg, IDC_LIST_PR);
        hCombo1 = GetDlgItem(hDlg, IDC_COMBO_CATEG_PR);
        hCombo2 = GetDlgItem(hDlg, IDC_COMBO_SORT_PR);
        hBtnSelect = GetDlgItem(hDlg, IDC_BTN_SELECT_PR);
        hBtnApply1 = GetDlgItem(hDlg, IDC_BTN_APPLY1);
        hBtnApply2 = GetDlgItem(hDlg, IDC_BTN_APPLY2);
        hBtnSave = GetDlgItem(hDlg, IDC_BTN_SAVE_PRICE);
        hBtnClose = GetDlgItem(hDlg, IDC_BTN_CLOSE_PR);
    }
    return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        {
            if (wmId == IDC_BTN_SELECT_PR) {

            }
            else if (wmId == IDC_BTN_APPLY1) {

            }
            else if (wmId == IDC_BTN_APPLY2) {

            }
            else if (wmId == IDC_BTN_SAVE_PRICE) {

            }
            else if (wmId == IDC_BTN_CLOSE_PR) {
                EndDialog(hDlg, wmId);
                return (INT_PTR)TRUE;
            }
            else if (wmId == IDOK || wmId == IDCANCEL)
            {
                EndDialog(hDlg, wmId);
                return (INT_PTR)TRUE;
            }
            break;
        }
    }
    return (INT_PTR)FALSE;
}

// 11 ----------------- Clients ---------------------
INT_PTR CALLBACK Clients(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        // Description 
        hEdit1 = GetDlgItem(hDlg, IDC_EDIT_SEARC_CL);
        hList = GetDlgItem(hDlg, IDC_LIST_CLIENT);
        hCombo1 = GetDlgItem(hDlg, IDC_COMBO_SORT_CL);
        hBtnAdd = GetDlgItem(hDlg, IDC_BTN_ADD_CL);
        hBtnSelect = GetDlgItem(hDlg, IDC_BTN_SELECT_CL);
        hBtnEdit = GetDlgItem(hDlg, IDC_BTN_EDIT_CL);
        hBtnDel = GetDlgItem(hDlg, IDC_BTN_DEL_CL);
        hBtnClose = GetDlgItem(hDlg, IDC_BTN_CLOSE_CL);
    }
    return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        {
            if (wmId == IDC_BTN_ADD_CL) {

            }
            else if (wmId == IDC_BTN_SELECT_CL) {

            }
            else if (wmId == IDC_BTN_EDIT_CL) {

            }
            else if (wmId == IDC_BTN_DEL_CL) {

            }
            else if (wmId == IDC_BTN_CLOSE_CL) {
                EndDialog(hDlg, wmId);
                return (INT_PTR)TRUE;
            }
            else if (wmId == IDOK || wmId == IDCANCEL)
            {
                EndDialog(hDlg, wmId);
                return (INT_PTR)TRUE;
            }
            break;
        }
    }
    return (INT_PTR)FALSE;
}

// 12 ----------------- Supliers ---------------------
INT_PTR CALLBACK Supliers(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        // Description 
        hEdit1 = GetDlgItem(hDlg, IDC_EDIT_SEARCH_SUP);
        hList = GetDlgItem(hDlg, IDC_LIST_SUP);
        hCombo1 = GetDlgItem(hDlg, IDC_COMBO_SORT_SUP);
        hBtnAdd = GetDlgItem(hDlg, IDC_BTN_ADD_SUP);
        hBtnSelect = GetDlgItem(hDlg, IDC_BTN_SELECT_SUP);
        hBtnEdit = GetDlgItem(hDlg, IDC_BTN_EDIT_SUP);
        hBtnDel = GetDlgItem(hDlg, IDC_BTN_DEL_SUP);
        hBtnClose = GetDlgItem(hDlg, IDC_BTN_CLOSE_SUP);
    }
    return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        {
            if (wmId == IDC_BTN_ADD_SUP) {

            }
            else if (wmId == IDC_BTN_SELECT_SUP) {

            }
            else if (wmId == IDC_BTN_EDIT_SUP) {

            }
            else if (wmId == IDC_BTN_DEL_SUP) {

            }
            else if (wmId == IDC_BTN_CLOSE_SUP) {
                EndDialog(hDlg, wmId);
                return (INT_PTR)TRUE;
            }
            else if (wmId == IDOK || wmId == IDCANCEL)
            {
                EndDialog(hDlg, wmId);
                return (INT_PTR)TRUE;
            }
            break;
        }
    }
    return (INT_PTR)FALSE;
}

// 13 ----------------- Report ---------------------
INT_PTR CALLBACK Report(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        // Description 

        hCombo1 = GetDlgItem(hDlg, IDC_COMBO_SORT_SUP);
        hCombo2 = GetDlgItem(hDlg, IDC_COMBO_SORT_SUP);
        hDataFrom = GetDlgItem(hDlg, IDC_DATETIMEPICKER_fRP);
        hDataTo = GetDlgItem(hDlg, IDC_DATETIMEPICKER_tRP);
        hList = GetDlgItem(hDlg, IDC_LIST_REPORT);
        hEdit1 = GetDlgItem(hDlg, IDC_EDIT_CASH_BALANCE_RP);
        hEdit1 = GetDlgItem(hDlg, IDC_EDIT_VISA_BALANCE_RP);
        hEdit1 = GetDlgItem(hDlg, IDC_EDIT_TOTAL_INCOME_RP);
        hEdit1 = GetDlgItem(hDlg, IDC_EDIT_TOTAL_CASH_RP);
        hEdit1 = GetDlgItem(hDlg, IDC_EDIT_TOTAL_VISA_RP);
        hEdit1 = GetDlgItem(hDlg, IDC_EDIT_TOTAL_AMOUT_RP);
        hEdit1 = GetDlgItem(hDlg, IDC_EDIT_TOTAL_EXPE_RP);
        hEdit1 = GetDlgItem(hDlg, IDC_EDIT_TOTAL_EXPE_CASH_RP);
        hEdit1 = GetDlgItem(hDlg, IDC_EDIT_TOTAL_EXPE_VISA_RP);
        hBtnSelect = GetDlgItem(hDlg, IDC_BTN_SELECT_RP);
        hBtnClose = GetDlgItem(hDlg, IDC_BTN_CLOSE_RP);
    }
    return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        {
            if (wmId == IDC_BTN_SELECT_RP) {

            }
            else if (wmId == IDC_BTN_CLOSE_RP) {
                EndDialog(hDlg, wmId);
                return (INT_PTR)TRUE;
            }
            else if (wmId == IDOK || wmId == IDCANCEL)
            {
                EndDialog(hDlg, wmId);
                return (INT_PTR)TRUE;
            }
            break;
        }
    }
    return (INT_PTR)FALSE;
}

// #
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
