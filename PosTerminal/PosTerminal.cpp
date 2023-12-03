// PosTerminal.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "PosTerminal.h"

#define MAX_LOADSTRING 100

//* Description
HWND hEdit1, hEdit2;
HWND hBtnLogin, hBtnClose, hBtnTerminal, hBtnProduct, hBtnPricing, hBtnLocation, hBtnClient, hBtnUsers, hBtnSupliers, hBtnReports;
HWND hBtnAdd, hBtnDel, hBtnPay;

//* GLOBAL Variers:
bool isAuthorize = true;
bool isAdmin = true; 
bool continueProcess = true;
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
    if (!InitInstance (hInstance, nCmdShow))
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

    return (int) msg.wParam;
}


// 2
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_POSTERMINAL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_POSTERMINAL);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

            }
            else if (wmId == IDC_BUTTON_Product) {

            }
            else if (wmId == IDC_BUTTON_Pricing) {

            }
            else if (wmId == IDC_BUTTON_Location) {

            }
            else if (wmId == IDC_BUTTON_Client) {

            }
            else if (wmId == IDC_BUTTON_Users) {

            }
            else if (wmId == IDC_BUTTON_Supliers) {

            }
            else if (wmId == IDC_BUTTON_Reports) {
                 
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
