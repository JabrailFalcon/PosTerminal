﻿// PosTerminal.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "PosTerminal.h"
#include "ProductsRepo.h"
#include "UsersRepo.h"
#include "SuppliersRepo.h"
#include "CategoriesRepo.h"

#define MAX_LOADSTRING 100

//* Description
HWND hEdit1, hEdit2, hEdit3, hEdit4, hEdit5, hEdit6, hEdit7, hEdit8, hEdit9, hEditSearch;
HWND hBtnLogin, hBtnClose, hBtnTerminal, hBtnProduct, hBtnPricing, hBtnLocation, hBtnClient, hBtnUsers, hBtnSupliers, hBtnReports;
HWND hBtnAdd, hBtnDel, hBtnPay, hBtnBanUnban, hRedisplayUsers, hGeneratePassword, hClear, hBtnSelect, hBtnReset, hBtnEdit, hBtnCategory, hBtnGenerate, hBtnMovement, hBtnApply1, hBtnApply2, hBtnSave;
HWND hCombo1, hCombo2, hCombo3, hSortByUser;
HWND hList, hProductsList, hUsersList;
HWND hDataFrom, hDataTo;
//* Products
HWND hEditProductSKU, hEditProductName, hEditProductDesc, hEditProductInprice, hEditProductOutprice, hEditProductQuantity;
HWND hComboProdCategories, hComboProdSort, hEditProdNameSKU, hPriceSlider, hComboProdCategoriesAdd, hBtnCatAdd, hBtnCatOk, hEditCatAdd;

//* GLOBAL Variers:
bool isAuthorize = true;
bool isAdmin = true;
bool continueProcess = true;
bool isBtnEdit = false;
//
bool AddEdit = true;
int UserDeleteIndex;
int IndexToEdit;
int UserId = -1;
//
// main
Helper helper;
//* Products
auto productsRepo = std::make_unique<ProductsRepo>();
auto categoriesRepo = std::make_unique<CategoriesRepo>();
bool sortedProducts = false;
bool editProduct = false;
int productID = -1;
std::string samesku = "";

//* Users:
auto usersRepo = std::make_unique<UsersRepo>();

//* Supliers
auto supplierRepo = std::make_unique<SuppliersRepo>("Data/Suppliers.json", "filterId.txt");
int selIndex;
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
INT_PTR CALLBACK    AddProduct(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Users(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AddUser(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    EditUser(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Location(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AddLocation(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Pricing(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Clients(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Supliers(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AddSuplier(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Report(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AddCategory(HWND, UINT, WPARAM, LPARAM);

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
                    usersRepo->loadData();
                    isAuthorize = usersRepo->authenticate(buff1, buff2);
                    //isAdmin = 
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
        hComboProdCategories = GetDlgItem(hDlg, IDC_COMBO_CATEGORY_PRODUCT);
        hComboProdSort = GetDlgItem(hDlg, IDC_COMBO_SORT_PROD3);

        hEditProdNameSKU = GetDlgItem(hDlg, IDC_EDIT_SEARCH_PRODUCT);
        hPriceSlider = GetDlgItem(hDlg, IDC_SLIDER1);

        // Load Data
       productsRepo->loadData();
       productsRepo->displayAllProducts(hProductsList);
       productsRepo->comboSort(hComboProdSort);
       categoriesRepo->loadData();
       categoriesRepo->comboCategories(hComboProdCategories);

    }
    return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        {
            if (wmId == IDC_BTN_AddProdact1) {
                editProduct = false;
                sortedProducts = false;
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hDlg, AddProduct);

            }
            else if (wmId == IDC_BTN_Select) {
                sortedProducts = true;
                productsRepo->selectProducts(hDlg, hProductsList, hEditProdNameSKU);
            }
            else if (wmId == IDC_BTN_EditP) {
                editProduct = true;  
                if (SendMessage(hProductsList, LB_GETCURSEL, 0, 0) >= 0) {
                    productID = productsRepo->getIDbyIndex(SendMessage(hProductsList, LB_GETCURSEL, 0, 0));
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hDlg, AddProduct);

                }
                else {
                    MessageBox(hDlg, L"Select product in the list to edit it!", L"Warning", MB_OK || MB_ICONWARNING);
                }
            }
            else if (wmId == IDC_BTN_DelP) {
                productsRepo->deleteProduct(hDlg, hProductsList, sortedProducts, hEditProdNameSKU);
            }
            else if (wmId == IDC_BTN_CloseP) {
                EndDialog(hDlg, wmId);
                return (INT_PTR)TRUE;
            }
            else if (wmId == IDC_BTN_RESET) {
                sortedProducts = false; 
                SetWindowText(hEditProdNameSKU, 0); 
                SendMessage(hProductsList, LB_RESETCONTENT, 0, 0); 
                productsRepo->displayAllProducts(hProductsList); 
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

INT_PTR CALLBACK AddProduct(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        // Description
        hEditProductSKU = GetDlgItem(hDlg, IDC_EDIT_SKU);
        hEditProductName = GetDlgItem(hDlg, IDC_EDIT_PRODNAME);
        hEditProductDesc = GetDlgItem(hDlg, IDC_EDIT_DESCRIPTION);
        hEditProductInprice = GetDlgItem(hDlg, IDC_EDIT_INPRICE);
        hEditProductOutprice = GetDlgItem(hDlg, IDC_EDIT_OUTPRICE);
        hEditProductQuantity = GetDlgItem(hDlg, IDC_EDIT_PRODQUANTITY);
        //
        hComboProdCategoriesAdd = GetDlgItem(hDlg, IDC_COMBO_CATEGORY);
        hBtnGenerate = GetDlgItem(hDlg, IDC_BTN_SKU);
        hBtnAdd = GetDlgItem(hDlg, IDC_BTN_ADD3);
        hBtnClose = GetDlgItem(hDlg, IDC_BTN_CANCEL3);
        hBtnCatAdd = GetDlgItem(hDlg, IDC_BTN_PRODCATEGORY); 

        categoriesRepo->comboCategories(hComboProdCategoriesAdd); 

        if (editProduct) {
            SetWindowText(hDlg, L"Edit product");
            SetWindowText(hBtnAdd, L"Edit");
            productsRepo->fillEditWindow(productID, hEditProductSKU, hEditProductName, hEditProductDesc,
                hEditProductInprice, hEditProductOutprice, hEditProductQuantity, hComboProdCategoriesAdd);
            TCHAR buff[100];
            GetWindowText(hEditProductSKU, buff, 100);
            samesku = helper.tchar_string(buff);
        }
        else {
            SetWindowText(hDlg, L"Add new product");
            SetWindowText(hEditProductInprice, L"0.0");
            SetWindowText(hEditProductOutprice, L"0.0");
            SetWindowText(hEditProductQuantity, L"0");
            SetWindowText(hBtnAdd, L"Create");
        }
    }
    return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        {
            if (wmId == IDC_BTN_SKU) {
                productsRepo->generateSKU(hEditProductSKU);
            }
            else if (wmId == IDC_BTN_ADD3) {
                bool correct = false;
                if (editProduct) {
                    productsRepo->editProduct(hDlg, hEditProductSKU, hEditProductName, hEditProductDesc, hEditProductInprice,
                        hEditProductOutprice, hEditProductQuantity, hComboProdCategoriesAdd, productID, editProduct, sortedProducts, correct, samesku);
                }
                else {
                    productsRepo->addProduct(hDlg, hEditProductSKU, hEditProductName, hEditProductDesc, hEditProductInprice,
                        hEditProductOutprice, hEditProductQuantity, hComboProdCategoriesAdd, productID, editProduct, correct);
                }
                if (correct) {
                    EndDialog(hDlg, wmId);
                    SendMessage(hProductsList, LB_RESETCONTENT, 0, 0);
                    if (sortedProducts) {
                        productsRepo->displaySortedProducts(hProductsList);
                    }
                    else {
                        productsRepo->displayAllProducts(hProductsList);
                    }
                    editProduct = false;
                }
            }
            else if (wmId == IDC_BTN_PRODCATEGORY) { 
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG20), hDlg, AddCategory); 
                SendMessage(hComboProdCategories, CB_RESETCONTENT, 0, 0); 
                categoriesRepo->comboCategories(hComboProdCategories); 
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

INT_PTR CALLBACK AddCategory(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        hBtnCatOk = GetDlgItem(hDlg, IDC_ADDCAT_BTN);
        hEditCatAdd = GetDlgItem(hDlg, IDC_EDIT_ADDCAT);
    }
    return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        {
            if (wmId == IDC_ADDCAT_BTN) {
                categoriesRepo->addCategory(hDlg, hEditCatAdd); 
                SendMessage(hComboProdCategoriesAdd, CB_RESETCONTENT, 0, 0);
                categoriesRepo->comboCategories(hComboProdCategoriesAdd); 
                int catindex = categoriesRepo->categoriesSize() - 1;
                SendMessage(hComboProdCategoriesAdd, CB_SETCURSEL, catindex, 0); 

                EndDialog(hDlg, wmId);
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
        // . . . :
        const wchar_t* status_opt_1 = L"on";
        const wchar_t* status_opt_2 = L"off";

        //
        const wchar_t* role_opt_1 = L"admin";
        const wchar_t* role_opt_2 = L"client";
        const wchar_t* role_opt_3 = L"suplier";

        // 
        const wchar_t* sort_by_opt_1 = L"Name";
        const wchar_t* sort_by_opt_2 = L"Role";
        const wchar_t* sort_by_opt_3 = L"Status";

        bool AddEdit = true;

        //SetBkColor(GetDC(hDlg), RGB(100, 100, 100));

        // Description
        hBtnAdd = GetDlgItem(hDlg, IDC_BTN_AddUser);
        hBtnSelect = GetDlgItem(hDlg, IDC_BTN_Select2);
        hBtnReset = GetDlgItem(hDlg, IDC_RESET_SORT_USER);
        hBtnEdit = GetDlgItem(hDlg, IDC_BTN_Edit2);
        hBtnDel = GetDlgItem(hDlg, IDC_BTN_Del2);
        hBtnClose = GetDlgItem(hDlg, IDC_BTN_Close2);
        hEdit1 = GetDlgItem(hDlg, IDC_EDIT_SEARCH_USER);
        hCombo1 = GetDlgItem(hDlg, IDC_COMBO_ROLE_USER);
        hCombo2 = GetDlgItem(hDlg, IDC_COMBO_STATUS_USER);
        hSortByUser = GetDlgItem(hDlg, IDC_SORT_BY_USER);
        hRedisplayUsers = GetDlgItem(hDlg, IDC_REDISPLAY_USERS);
        hBtnBanUnban = GetDlgItem(hDlg, IDC_BAN_UNBAN_USERS);

        // hUsersList:
        hUsersList = GetDlgItem(hDlg, IDC_LIST_USERS);

        // Status CB:
        SendMessage(hCombo2, CB_ADDSTRING, 0, (LPARAM)status_opt_1);
        SendMessage(hCombo2, CB_ADDSTRING, 0, (LPARAM)status_opt_2);

        // Role CB:
        SendMessage(hCombo1, CB_ADDSTRING, 0, (LPARAM)role_opt_1);
        SendMessage(hCombo1, CB_ADDSTRING, 0, (LPARAM)role_opt_2);
        SendMessage(hCombo1, CB_ADDSTRING, 0, (LPARAM)role_opt_3);

        // Sort by CB:
        SendMessage(hSortByUser, CB_ADDSTRING, 0, (LPARAM)sort_by_opt_1);
        SendMessage(hSortByUser, CB_ADDSTRING, 0, (LPARAM)sort_by_opt_2);
        SendMessage(hSortByUser, CB_ADDSTRING, 0, (LPARAM)sort_by_opt_3);

        // mine:

        // actions:
        usersRepo->loadData();
        usersRepo->displayUsers(hDlg, hUsersList);
    }
    return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        {
            // mine
            TCHAR buff1[100];

            if (wmId == IDC_BTN_AddUser) {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG5), hDlg, AddUser);
            }
            else if (wmId == IDC_BTN_Select2) {
                usersRepo->sorting(hDlg, hEdit1, hUsersList);
            }
            else if (wmId == IDC_RESET_SORT_USER) {
                SetWindowText(hEdit1, L"");
                SendMessage(hUsersList, LB_RESETCONTENT, 0, 0);
                usersRepo->displayUsers(hDlg, hUsersList);
            }
            else if (wmId == IDC_BTN_Edit2) {
                IndexToEdit = SendMessage(hUsersList, LB_GETCURSEL, 0, 0);
                Helper helper;
                /*std::string buffer = std::to_string(IndexToEdit);
                TCHAR* buff = helper.string_tchar(buffer);
                MessageBox(hDlg, buff, L"Warning", MB_OK || MB_ICONWARNING);*/
                if (IndexToEdit < 0) {
                    MessageBox(hDlg, L"First of all, select user from list!", L"Warning!", MB_OK | MB_ICONWARNING);
                }
                else {
                    AddEdit = false;
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG5), hDlg, AddUser);

                }
            }
            else if (wmId == IDC_REDISPLAY_USERS) {
                usersRepo->loadData();
                SendMessage(hUsersList, LB_RESETCONTENT, 0, 0);
                usersRepo->displayUsers(hDlg, hUsersList);
            }
            else if (wmId == IDC_BAN_UNBAN_USERS) {
                int UserId = SendMessage(hUsersList, LB_GETCURSEL, 0, 0);
                if (UserId < 0) {
                    MessageBox(hDlg, L"First of all, select user from list!", L"Warning!", MB_OK | MB_ICONWARNING);
                }
                else {
                    usersRepo->banUnban(hDlg, UserId);
                    SendMessage(hUsersList, LB_RESETCONTENT, 0, 0);
                    usersRepo->displayUsers(hDlg, hUsersList);
                }
            }
            else if (wmId == IDC_BTN_Del2) {
                Helper helper;
                UserDeleteIndex = SendMessage(hUsersList, LB_GETCURSEL, 0, 0);
                //usersRepo->deleteUser(UserDeleteIndex);
                if (UserDeleteIndex < 0) {
                    MessageBox(hDlg, L"Choose the user to delete!", L"Warning!", MB_OK | MB_ICONWARNING);
                }
                else {
                    usersRepo->deleteUser(UserDeleteIndex);
                    SendMessage(hUsersList, LB_RESETCONTENT, 0, 0);
                    usersRepo->displayUsers(hDlg, hUsersList);
                }
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

INT_PTR CALLBACK AddUser(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        // . . .
        const wchar_t* status_opt_1 = L"on";
        const wchar_t* status_opt_2 = L"off";

        //
        const wchar_t* role_opt_1 = L"admin";
        const wchar_t* role_opt_2 = L"client";
        const wchar_t* role_opt_3 = L"suplier";

        // Description
        hEdit1 = GetDlgItem(hDlg, IDC_EDIT_FN_USER);
        hEdit2 = GetDlgItem(hDlg, IDC_EDIT_LN_USER);
        hEdit3 = GetDlgItem(hDlg, IDC_EDIT_MOB_USER);
        hCombo1 = GetDlgItem(hDlg, IDC_COMBO_ROLE_AD_USER);
        hCombo2 = GetDlgItem(hDlg, IDC_COMBO_STATUS_AD_USER);
        hEdit5 = GetDlgItem(hDlg, IDC_EDIT_MAIL_AD_USER);
        hEdit6 = GetDlgItem(hDlg, IDC_EDIT_PASS_USER);
        hBtnAdd = GetDlgItem(hDlg, IDC_BTN_ADD3);
        hBtnClose = GetDlgItem(hDlg, IDC_BTN_CANCEL3);
        hClear = GetDlgItem(hDlg, IDC_BTN_CLEAR_USER);
        hGeneratePassword = GetDlgItem(hDlg, IDC_BTN_GENERATE_PASSWORD);

        if (AddEdit == false) {
            UserId = SendMessage(hUsersList, LB_GETCURSEL, 0, 0) + 1;
            usersRepo->displayEdits(UserId, hEdit1, hEdit2, hEdit3, hCombo2, hCombo1, hEdit5, hEdit6);
        }

        // Status CB:
        SendMessage(hCombo2, CB_ADDSTRING, 0, (LPARAM)status_opt_1);
        SendMessage(hCombo2, CB_ADDSTRING, 0, (LPARAM)status_opt_2);

        // Role CB:
        SendMessage(hCombo1, CB_ADDSTRING, 0, (LPARAM)role_opt_1);
        SendMessage(hCombo1, CB_ADDSTRING, 0, (LPARAM)role_opt_2);
        SendMessage(hCombo1, CB_ADDSTRING, 0, (LPARAM)role_opt_3);
    }
    return (INT_PTR)TRUE;

    case WM_COMMAND:
        // Add
        if (AddEdit == true) {
            int wmId = LOWORD(wParam);
            {
                TCHAR fNameBuff[100], lNameBuff[100], roleBuff[100], mobileBuff[100], emailBuff[100], 
                    statusBuff[100], passwordBuff[100];

                if (wmId == IDC_BTN_SAVE_USER) {
                    GetWindowText(hEdit1, fNameBuff, 100);
                    GetWindowText(hEdit2, lNameBuff, 100);
                    GetWindowText(hEdit3, mobileBuff, 100);
                    GetWindowText(hCombo1, roleBuff, 100);
                    GetWindowText(hCombo2, statusBuff, 100);
                    GetWindowText(hEdit5, emailBuff, 100);
                    GetWindowText(hEdit6, passwordBuff, 100);

                    // Fields
                    // Fist Name:
                    if (lstrlen(fNameBuff) == 0) {
                        MessageBox(hDlg, L"Input first name!", L"Empty field", MB_OK | MB_ICONWARNING);
                        SetFocus(hEdit1);
                    }
                    else if (lstrlen(fNameBuff) == 1){
                        MessageBox(hDlg, L"First name can`t be with 1 symbol!", L"Incorrect first name", 
                            MB_OK | MB_ICONWARNING);
                        SetWindowText(hEdit1, L"");
                        SetFocus(hEdit1);
                    }

                    // Last Name:
                    else if (lstrlen(lNameBuff) == 0) {
                        MessageBox(hDlg, L"Input last name!", L"Empty field", MB_OK | MB_ICONWARNING);
                        SetFocus(hEdit2);
                    }
                    else if (lstrlen(lNameBuff) == 1) {
                        MessageBox(hDlg, L"Last name can`t be with 1 symbol!", L"Incorrect last name", 
                            MB_OK | MB_ICONWARNING);
                        SetWindowText(hEdit2, L"");
                        SetFocus(hEdit2);
                    }

                    // Mobile:
                    else if (lstrlen(mobileBuff) == 0) {
                        MessageBox(hDlg, L"Input phone number!", L"Empty field", MB_OK | MB_ICONWARNING);
                        SetFocus(hEdit3);
                    }
                    else if (lstrlen(mobileBuff) == 4) {
                        MessageBox(hDlg, L"Input correct phone number!", L"Incorrect number", 
                            MB_OK | MB_ICONWARNING);
                        SetWindowText(hEdit3, L"");
                        SetFocus(hEdit3);
                    }

                    // Role:
                    else if (lstrlen(roleBuff) == 0) {
                        MessageBox(hDlg, L"Choose the role!", L"Empty field", MB_OK | MB_ICONWARNING);
                        SetFocus(hCombo1);
                    }

                    // Status:
                    else if (lstrlen(statusBuff) == 0) {
                        MessageBox(hDlg, L"Choose the status!", L"Empty field", MB_OK | MB_ICONWARNING);
                        SetFocus(hCombo2);
                    }
                    
                    // Email:
                    else if (lstrlen(emailBuff) == 0) {
                        MessageBox(hDlg, L"Input the email!", L"Empty field", MB_OK | MB_ICONWARNING);
                        SetFocus(hEdit5);
                    }
                    else if (lstrlen(emailBuff) == 7) {
                        MessageBox(hDlg, L"Input correct emal!", L"Incorrect email", MB_OK | MB_ICONWARNING);
                        SetFocus(hEdit5);
                    }
                    
                    // Password:
                    else if (lstrlen(passwordBuff) == 0) {
                        MessageBox(hDlg, L"Input the password!", L"Empty field", MB_OK | MB_ICONWARNING);
                        SetFocus(hEdit6);
                    }
                    else if (lstrlen(passwordBuff) < 8) {
                        MessageBox(hDlg, L"Password must be longer than 7 symbols!", L"Incorrect password", 
                            MB_OK | MB_ICONWARNING);
                        SetFocus(hEdit6);
                    }

                    // Correct
                    else {
                        usersRepo->addUser(hDlg, hUsersList, passwordBuff, mobileBuff, emailBuff, 
                            roleBuff, fNameBuff,
                            lNameBuff, statusBuff);
                        MessageBox(hDlg, L"User successfully added!", L"Warning!", MB_OK | MB_ICONINFORMATION);
                        SetWindowText(hEdit1, L"");
                        SetWindowText(hEdit2, L"");
                        SetWindowText(hEdit3, L"");
                        SetWindowText(hCombo1, L"");
                        SetWindowText(hCombo2, L"");
                        SetWindowText(hEdit5, L"");
                        SetWindowText(hEdit6, L"");
                        SetFocus(hEdit1);
                        SendMessage(hUsersList, LB_RESETCONTENT, 0, 0);
                        usersRepo->displayUsers(hDlg, hUsersList);
                    }
                }
                else if (wmId == IDC_COMBO_STATUS_AD_USER) {
                    if (LOWORD(wParam) == CBN_SELENDOK) {
                        CHAR str_1[255];
                        int i = SendMessage(hCombo2, CB_GETCURSEL, 0, 0);
                        SendMessage(hCombo2, CB_GETLBTEXT, i, (LPARAM)str_1);

                    }
                }
                else if (wmId == IDC_COMBO_ROLE_AD_USER) {
                    if (LOWORD(wParam) == CBN_SELENDOK) {
                        CHAR str_1[255];
                        int i = SendMessage(hCombo1, CB_GETCURSEL, 0, 0);
                        SendMessage(hCombo1, CB_GETLBTEXT, i, (LPARAM)str_1);
                    }
                }
                else if (wmId == IDC_BTN_GENERATE_PASSWORD) {
                    usersRepo->generatePassword(hDlg, hEdit6);
                }
                else if (wmId == IDC_BTN_CANCEL_USER) {
                    EndDialog(hDlg, wmId);
                    return (INT_PTR)TRUE;
                }
                else if (wmId == IDC_BTN_CLEAR_USER) {
                    SetWindowText(hEdit1, L"");
                    SetWindowText(hEdit2, L"");
                    SetWindowText(hEdit3, L"");
                    SetWindowText(hEdit5, L"");
                    SetWindowText(hEdit6, L"");
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

        // Edit
        else {
            int wmId = LOWORD(wParam);
            {
                if (wmId == IDC_BTN_SAVE_USER) {

                    // . . .

                    TCHAR fNameBuff[100], lNameBuff[100], roleBuff[100], mobileBuff[100], 
                        emailBuff[100], statusBuff[100], passwordBuff[100];

                    GetWindowText(hEdit1, fNameBuff, 100);
                    GetWindowText(hEdit2, lNameBuff, 100);
                    GetWindowText(hEdit3, mobileBuff, 100);
                    GetWindowText(hCombo1, roleBuff, 100);
                    GetWindowText(hCombo2, statusBuff, 100);
                    GetWindowText(hEdit5, emailBuff, 100);
                    GetWindowText(hEdit6, passwordBuff, 100);

                    // Fields
                    if (lstrlen(fNameBuff) == 0) {
                        MessageBox(hDlg, L"Input first name!", L"Empty field", MB_OK | MB_ICONWARNING);
                        SetFocus(hEdit1);
                    }
                    else if (lstrlen(lNameBuff) == 0) {
                        MessageBox(hDlg, L"Input last name!", L"Empty field", MB_OK | MB_ICONWARNING);
                        SetFocus(hEdit2);
                    }
                    else if (lstrlen(mobileBuff) == 0) {
                        MessageBox(hDlg, L"Input phone number!", L"Empty field", MB_OK | MB_ICONWARNING);
                        SetFocus(hEdit3);
                    }
                    else if (lstrlen(roleBuff) == 0) {
                        MessageBox(hDlg, L"Choose the role!", L"Empty field", MB_OK | MB_ICONWARNING);
                        SetFocus(hCombo1);
                    }
                    else if (lstrlen(statusBuff) == 0) {
                        MessageBox(hDlg, L"Choose the status!", L"Empty field", MB_OK | MB_ICONWARNING);
                        SetFocus(hCombo2);
                    }
                    else if (lstrlen(emailBuff) == 0) {
                        MessageBox(hDlg, L"Input the email!", L"Empty field", MB_OK | MB_ICONWARNING);
                        SetFocus(hEdit5);
                    }
                    else if (lstrlen(passwordBuff) == 0) {
                        MessageBox(hDlg, L"Input the password!", L"Empty field", MB_OK | MB_ICONWARNING);
                        SetFocus(hEdit6);
                    }
                    else {
                        if (UserDeleteIndex < 0) {
                            MessageBox(hDlg, L"Choose the user to delete!", L"Warning!", MB_OK | MB_ICONWARNING);
                        }
                        else {
                            usersRepo->editUser(hDlg, hEdit1, hEdit2, hEdit3, hCombo2, hEdit5,
                                hEdit6, hCombo1, UserId);
                            MessageBox(hDlg, L"The user was edited successfully!", L"successfully", 
                                MB_OK | MB_ICONINFORMATION);
                            SendMessage(hUsersList, LB_RESETCONTENT, 0, 0);
                            usersRepo->displayUsers(hDlg, hUsersList);
                            SetWindowText(hEdit1, L"");
                            SetWindowText(hEdit2, L"");
                            SetWindowText(hEdit3, L"");
                            SetWindowText(hCombo1, L"");
                            SetWindowText(hCombo2, L"");
                            SetWindowText(hEdit5, L"");
                            SetWindowText(hEdit6, L"");
                            return (INT_PTR)TRUE;
                        }
                    }
                }
                else if (wmId == IDC_COMBO_STATUS_AD_USER) {
                    if (LOWORD(wParam) == CBN_SELENDOK) {
                        CHAR str_1[255];
                        int i = SendMessage(hCombo2, CB_GETCURSEL, 0, 0);
                        SendMessage(hCombo2, CB_GETLBTEXT, i, (LPARAM)str_1);
                    }
                }
                else if (wmId == IDC_COMBO_ROLE_AD_USER) {
                    if (LOWORD(wParam) == CBN_SELENDOK) {
                        CHAR str_1[255];
                        int i = SendMessage(hCombo1, CB_GETCURSEL, 0, 0);
                        SendMessage(hCombo1, CB_GETLBTEXT, i, (LPARAM)str_1);
                    }
                }
                else if (wmId == IDC_BTN_GENERATE_PASSWORD) {
                    usersRepo->generatePassword(hDlg, hEdit6);
                }
                else if (wmId == IDC_BTN_CANCEL_USER) {
                    EndDialog(hDlg, wmId);
                    return (INT_PTR)TRUE;
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
        hEditSearch = GetDlgItem(hDlg, IDC_EDIT_SEARCH_SUP);
        hList = GetDlgItem(hDlg, IDC_LIST_SUP);
        hCombo1 = GetDlgItem(hDlg, IDC_COMBO_SORT_SUP);
        hBtnAdd = GetDlgItem(hDlg, IDC_BTN_ADD_SUP);
        hBtnSelect = GetDlgItem(hDlg, IDC_BTN_SELECT_SUP);
        hBtnEdit = GetDlgItem(hDlg, IDC_BTN_EDIT_SUP);
        hBtnDel = GetDlgItem(hDlg, IDC_BTN_DEL_SUP);
        hBtnClose = GetDlgItem(hDlg, IDC_BTN_CLOSE_SUP);
        // ->
        supplierRepo->loadData();
        supplierRepo->displayAll(hDlg, hList);
        supplierRepo->comboSort(hDlg, hCombo1); 
        
    }
    return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        {        
            //-> 
            TCHAR buff1[100];
            TCHAR buff2[100];
            if (wmId == IDC_BTN_ADD_SUP) {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG9), hDlg, AddSuplier); 
            }
            else if (wmId == IDC_BTN_SELECT_SUP) {
                GetWindowText(hEditSearch, buff1, 100);
                GetDlgItemText(hDlg, IDC_COMBO_SORT_SUP, buff2, 100); 
                if (lstrlen(buff1) == 0 && lstrlen(buff2) == 0) {
                    MessageBox(hDlg, L"Search attributes are not specified!", L"Warning!", MB_OK | MB_ICONWARNING); 
                    SendMessage(hList, LB_RESETCONTENT, 0, 0); 
                    supplierRepo->displayAll(hDlg, hList); 
                    SetFocus(hEditSearch);
                }
                else if (lstrlen(buff1) != 0 && lstrlen(buff2) == 0) {
                    supplierRepo->displayExist(buff1, hDlg, hList);

                }
                else if (lstrlen(buff1) == 0 && lstrlen(buff2) != 0) {
                    supplierRepo->sortByName(hDlg, hList);

                }
            }
            else if (wmId == IDC_BTN_EDIT_SUP) {     
                selIndex = SendMessage(hList, LB_GETCURSEL, 0, 0);
                if (selIndex < 0) {
                    MessageBox(hDlg, L"First of all, select supplier from list!", L"Warning!", MB_OK | MB_ICONWARNING); 
                }
                else {
                    isBtnEdit = true;
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG9), hDlg, AddSuplier); 

                }            
            }
            else if (wmId == IDC_BTN_DEL_SUP) {
                selIndex = SendMessage(hList, LB_GETCURSEL, 0, 0);
                if (selIndex < 0) {
                    MessageBox(hDlg, L"First of all, select supplier from list!", L"Warning!", MB_OK | MB_ICONWARNING);
                }
                else {
                    if (MessageBox(hDlg, L"Are you shure?", L"Warning!", MB_OKCANCEL | MB_ICONWARNING) == true) {
                        int colItem = SendMessage(hList, LB_DELETESTRING, WPARAM(selIndex), 0);
                        supplierRepo->delSuplier(selIndex);

                    }
                }
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

INT_PTR CALLBACK AddSuplier(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) 
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        // Description 

        hEdit1 = GetDlgItem(hDlg, IDC_EDIT_COMNAME_SUPPL); 
        hEdit2 = GetDlgItem(hDlg, IDC_EDIT_MAILCOM_SAPP);
        hEdit3 = GetDlgItem(hDlg, IDC_EDIT_MOBCOMNUM_SUPP);
        hEdit4 = GetDlgItem(hDlg, IDC_EDIT_ADRESSCOM_SAPP);
        hEdit5 = GetDlgItem(hDlg, IDC_EDIT_FN_SAPP);
        hEdit6 = GetDlgItem(hDlg, IDC_EDIT_LN_SAPP);
        hEdit7 = GetDlgItem(hDlg, IDC_EDIT_MOB_SAPP);
        hEdit8 = GetDlgItem(hDlg, IDC_EDIT_MAIL_SAPP);
        hEdit9 = GetDlgItem(hDlg, IDC_EDIT_JT_SAPP);
        hBtnSave = GetDlgItem(hDlg, IDC_BTN_SAVE_ADDSAPP);
        hBtnClose = GetDlgItem(hDlg, IDC_BTN_CANCEL_ADDSAPP);
        // ->

        if (isBtnEdit) {
            supplierRepo->displayEditExist(selIndex, hEdit1, hEdit2, hEdit3, hEdit4, hEdit5, hEdit6, hEdit7, hEdit8, hEdit9);
        }
    }
    return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        {
            TCHAR buff1[100];
            TCHAR buff2[100];
            TCHAR buff3[100];
            TCHAR buff4[100];
            TCHAR buff5[100];
            TCHAR buff6[100];
            TCHAR buff7[100];
            TCHAR buff8[100];
            TCHAR buff9[100];
            if (wmId == IDC_BTN_SAVE_ADDSAPP) {
                // ->
                GetWindowText(hEdit1, buff1, 100);
                GetWindowText(hEdit2, buff2, 100);
                GetWindowText(hEdit3, buff3, 100);
                GetWindowText(hEdit4, buff4, 100);
                GetWindowText(hEdit5, buff5, 100);
                GetWindowText(hEdit6, buff6, 100);
                GetWindowText(hEdit7, buff7, 100);
                GetWindowText(hEdit8, buff8, 100);
                GetWindowText(hEdit9, buff9, 100);
                // ->
                if (lstrlen(buff1) == 0) {
                    MessageBox(hDlg, L"Input company name!", L"Warning!", MB_OK | MB_ICONWARNING);

                    SetFocus(hEdit1);
                }
                else if (lstrlen(buff2) == 0) {
                    MessageBox(hDlg, L"Input company mail!", L"Warning!", MB_OK | MB_ICONWARNING);

                    SetFocus(hEdit2);
                }
                else if (lstrlen(buff3) == 0) {
                    MessageBox(hDlg, L"Input company contact number!", L"Warning!", MB_OK | MB_ICONWARNING);

                    SetFocus(hEdit3);
                }
                else if (lstrlen(buff4) == 0) {
                    MessageBox(hDlg, L"Input company adress!", L"Warning!", MB_OK | MB_ICONWARNING);

                    SetFocus(hEdit4);
                }
                else if (lstrlen(buff5) == 0) {
                    MessageBox(hDlg, L"Input contact person name!", L"Warning!", MB_OK | MB_ICONWARNING);

                    SetFocus(hEdit5);
                }
                else if (lstrlen(buff6) == 0) {
                    MessageBox(hDlg, L"Input contact person last name!", L"Warning!", MB_OK | MB_ICONWARNING);

                    SetFocus(hEdit6);
                }
                else if (lstrlen(buff7) == 0) {
                    MessageBox(hDlg, L"Input contact person mobile number!", L"Warning!", MB_OK | MB_ICONWARNING);

                    SetFocus(hEdit7);
                }
                else if (lstrlen(buff8) == 0) {
                    MessageBox(hDlg, L"Input contact person mail!", L"Warning!", MB_OK | MB_ICONWARNING);

                    SetFocus(hEdit8);
                }
                else if (lstrlen(buff9) == 0) {
                    MessageBox(hDlg, L"Input job title!", L"Warning!", MB_OK | MB_ICONWARNING);

                    SetFocus(hEdit9);
                }
                else {
                    if (isBtnEdit) {
                        supplierRepo->editExist(selIndex, buff1, buff3, buff2, buff4, buff5, buff6, buff7, buff8, buff9);
                        MessageBox(hDlg, L"Supplier successfully edited", L"Warning!", MB_OK | MB_ICONWARNING);
                        // ->
                        SendMessage(hList, LB_RESETCONTENT, 0, 0); 
                        supplierRepo->displayAll(hDlg, hList); 
                    }
                    else {
                        supplierRepo->addSuplier(hDlg, hList, buff1, buff3, buff2, buff4, buff5, buff6, buff7, buff8, buff9); 
                        MessageBox(hDlg, L"Supplier successfully added!", L"Warning!", MB_OK | MB_ICONINFORMATION);
                        SetWindowText(hEdit1, L"");
                        SetWindowText(hEdit2, L"");
                        SetWindowText(hEdit3, L"");
                        SetWindowText(hEdit4, L"");
                        SetWindowText(hEdit5, L""); 
                        SetWindowText(hEdit6, L""); 
                        SetWindowText(hEdit7, L""); 
                        SetWindowText(hEdit8, L""); 
                        SetWindowText(hEdit9, L""); 
                        SetFocus(hEdit1); 
                        // ->
                        //SendMessage(hList, LB_RESETCONTENT, 0, 0); 
                       // supplierRepo->displayAll(hDlg, hList); 
                    }       
                }       
            }
            else if (wmId == IDC_BTN_CANCEL_ADDSAPP) {
                isBtnEdit = false;
                EndDialog(hDlg, wmId);
                return (INT_PTR)TRUE;
            }
            else if (wmId == IDOK || wmId == IDCANCEL)
            {
                isBtnEdit = false;
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
