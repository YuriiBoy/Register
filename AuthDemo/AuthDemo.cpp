
#include "framework.h"
#include "AuthDemo.h"
#include "AccountsRep.h"

#define MAX_LOADSTRING 100

// Дескрипторы of управления elements

HWND hSubmitButton, hResetButton, hRegisterButton;
HWND hLoginField, hPasswordField;

HWND hNameEdit, hSurnameEdit, hTelEdit, hLoginEdit, hPasswordEdit, hConfPasEdit;
HWND hRegistButton;


// *
bool authResult = false;
auto accountsRep = std::make_unique<AccountsRep>();

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Auth(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Regist(HWND, UINT, WPARAM, LPARAM);

// 1
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_AUTHDEMO, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_AUTHDEMO));

    MSG msg;

    // Main message loop:
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_AUTHDEMO));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_AUTHDEMO);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

// 3
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

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
        // відкриваємо вікно авторизації:
        DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Auth);

        // 2 Після закриття вікна авторизації  обробляєм ії результат
        
            if (authResult == false) {
                MessageBox(hWnd, L"Користувач не знайдений", L"Повідомлення",
                    MB_OK | MB_ICONERROR);
                // DestroyWindow(hWnd);
            }
            else {
                MessageBox(hWnd, L"Ви авторизовані", L"Повідомлення",
                    MB_OK | MB_ICONINFORMATION);
                TCHAR buff[100];
                lstrcpy(buff, L"Авторизований  Користувач - ");
                lstrcat(buff, accountsRep->getUserName());
                lstrcat(buff, L" ");
                lstrcat(buff, accountsRep->getUserSurname());
                lstrcat(buff, L" !");
                SetWindowText(hWnd, buff);
                break;
            
        }
        

        DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, Regist);

            }

        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, Regist);
                break;
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
            // TODO: Add any drawing code that uses hdc here...
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

// 5

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

// * 6
INT_PTR CALLBACK Auth(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        {
        hSubmitButton = GetDlgItem(hDlg, IDC_BUTTON1);
        hResetButton = GetDlgItem(hDlg, IDC_BUTTON2);
        hRegisterButton = GetDlgItem(hDlg, IDC_BUTTON3);
        hLoginField = GetDlgItem(hDlg, IDC_EDIT1);
        hPasswordField = GetDlgItem(hDlg, IDC_EDIT2);
        accountsRep->loadData();
        }
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            if (wmId == IDC_BUTTON1)
            {
                TCHAR buff1[100];
                GetWindowText(hLoginField, buff1, 100);
                if (lstrlen(buff1) == 0) {
                    MessageBox(hDlg, L" Ви не ввели логін", L"Повідомлення",
                        MB_OK | MB_ICONEXCLAMATION);
                    SetFocus(hLoginField);
                }
                else {

                    TCHAR buff2[100];
                    GetWindowText(hPasswordField, buff2, 100);
                    if (lstrlen(buff2) == 0) {
                        MessageBox(hDlg, L" Ви не ввели пароль", L"Повідомлення",
                            MB_OK | MB_ICONEXCLAMATION);
                        SetFocus(hPasswordField);
                    }
                    else {
                        authResult = accountsRep->authCheck(buff1, buff2);
                        EndDialog(hDlg, wmId);
                    }
                }
            }
            else if (wmId == IDC_BUTTON2)
            {
                SetWindowText(hLoginField, L"");
                SetWindowText(hPasswordField, L"");
                SetFocus(hLoginField);
            }
            else if (wmId == IDC_BUTTON3)
            {
                EndDialog(hDlg, wmId);
                 
            }
            else if (wmId == IDOK || wmId == IDCANCEL)
            {
                EndDialog(hDlg, wmId);
                return (INT_PTR)TRUE;
            }
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// 7
INT_PTR CALLBACK Regist(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
         {
        hNameEdit = GetDlgItem(hDlg, IDC_EDIT1);
        hSurnameEdit = GetDlgItem(hDlg, IDC_EDIT2);
        hTelEdit = GetDlgItem(hDlg, IDC_EDIT3);
        hLoginEdit = GetDlgItem(hDlg, IDC_EDIT4);
        hPasswordEdit = GetDlgItem(hDlg, IDC_EDIT5);
        hConfPasEdit = GetDlgItem(hDlg, IDC_EDIT6);
        hRegistButton = GetDlgItem(hDlg, IDC_BUTTON1);
         }
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