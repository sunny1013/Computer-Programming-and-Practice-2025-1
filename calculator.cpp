// calculator.cpp
// 계산기 창. 숫자 버튼이 있고, 결과값 보여줌. 
// 버튼을 누르면 buttons.c에 있는 해당 함수 호출

#include <cstdio>
#include "framework.h"
#include "calculator.h"

#define MAX_LOADSTRING 100
#define BUTTON_COUNT 11

/* 결과창과 결과값 */
static HWND hWndResult; // 결과 창
extern int result = 0;  // 결과 값 (다른 소스파일과 공유됨)

/* 버튼별 상태, 글자색, 배경색 */
static char buttonState[BUTTON_COUNT];          // 버튼 상태
static COLORREF buttonTextColor[BUTTON_COUNT];  // 글자색
static COLORREF buttonBgColor[BUTTON_COUNT];    // 배경색
static COLORREF buttonShadowColor[BUTTON_COUNT];  // 그림자색

/* 색깔 상수들 */
static const COLORREF BUTTON_TEXT_COLOR = RGB(50, 50, 50);              // 일반 글자색
static const COLORREF BUTTON_TEXT_COLOR_CLICKED = RGB(150, 150, 150);   // 클릭시 글자색
static const COLORREF BUTTON_BG_COLOR = RGB(245, 245, 245);             // 일반 배경색
static const COLORREF BUTTON_BG_COLOR_CLICKED = RGB(240, 240, 240);     // 클릭시 배경색
static const COLORREF BUTTON_SHADOW_COLOR = RGB(200, 200, 200);             // 일반 배경색
static const COLORREF BUTTON_SHADOW_COLOR_CLICKED = RGB(240, 240, 240);     // 클릭시 배경색

/* 디버그 함수: 콘솔에 메시지를 출력*/
void debug(UINT message);

/* 모든 버튼에서 쓰는 콜백 함수 */
LRESULT CALLBACK ButtonProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

    /* 버튼 클릭시 실행할 함수들의 배열 */
    static void(*buttonClick[BUTTON_COUNT])() = {
        button0, button1, button2, button3, button4,
        button5, button6, button7, button8, button9, 
        button_backspace
    };
    static bool clicked = false; // 클릭 중인 버튼이 있는지
    int buttonIndex = GetDlgCtrlID(hWnd) - 1; // 버튼 숫자

    if (buttonIndex < BUTTON_COUNT) { // 버튼 번호 확인
        // 디버그 
        // printf("ButtonProc %d: \n", buttonIndex);
        // debug(message);

        switch (message) {

        case WM_MOUSELEAVE: // 마우스 버튼이 바깥으로 나갈 때
        case WM_LBUTTONUP: // 마우스 버튼을 땠을 때
        {
            // 디버그 
            //printf("if: WM_LBUTTONUP, cliked = %d \n", clicked);

            clicked = false; // 클릭중 상태 해제

            /* 버튼 상태 및 색깔 변경*/
            buttonState[buttonIndex] = 'u';
            buttonTextColor[buttonIndex] = BUTTON_TEXT_COLOR;
            buttonBgColor[buttonIndex] = BUTTON_BG_COLOR;
            buttonShadowColor[buttonIndex] = BUTTON_SHADOW_COLOR;

            /* 버튼 다시 그리기 */
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
        }
        break;

        case WM_LBUTTONDOWN: // 마우스 버튼을 누를 때
        {
            // 디버그 
            // printf("if: WM_LBUTTONDOWN, clicked: %d \n", clicked);

            if (!clicked) { // 클릭중이 아닐 때만 반응
                clicked = true; // 클릭중 상태 설정

                buttonClick[buttonIndex](); // 클릭 함수 실행

                /* 결과창 다시 그리기 */
                InvalidateRect(hWndResult, NULL, TRUE);
                UpdateWindow(hWndResult);

                /* 버튼 상태 및 색깔 변경*/
                buttonState[buttonIndex] = 'd';
                buttonTextColor[buttonIndex] = BUTTON_TEXT_COLOR_CLICKED;
                buttonBgColor[buttonIndex] = BUTTON_BG_COLOR_CLICKED;
                buttonShadowColor[buttonIndex] = BUTTON_SHADOW_COLOR_CLICKED;

                /* 버튼 다시 그리기 */
                InvalidateRect(hWnd, NULL, TRUE);
                UpdateWindow(hWnd);

                /* 콘솔 출력 */
                if (buttonIndex >= 0 && buttonIndex <= 9) {
                    printf("----------버튼 클릭됨. 숫자 %d----------\n", buttonIndex);
                }
                else if (buttonIndex == 10) {
                    printf("----------버튼 클릭됨. 숫자 하나 지우기 ----------\n");
                }
                else {
                    printf("----------버튼 클릭됨. ----------\n");
                }

            }
        }
        break;

        case WM_PAINT: // 그림 그리기
        {
            // 디버그 printf("if: WM_PAINT \n");
            PAINTSTRUCT ps;

            HDC hdc = BeginPaint(hWnd, &ps); // 그림 그리기 시작

            /* 배경 색칠하기 */
            COLORREF bgColor = buttonBgColor[buttonIndex];
            HBRUSH hBrush = CreateSolidBrush(bgColor);
            FillRect(hdc, &ps.rcPaint, hBrush);
            DeleteObject(hBrush);

            /* 글자 쓰기 */
            wchar_t buttonText[2] = { 0 };

            if (buttonIndex < 10) {
                buttonText[0] = '0' + buttonIndex;
            }
            else if (buttonIndex == 10) {
                buttonText[0] = L'⌫';
            }

            RECT rc; // 계산기 창 기준 버튼 모서리 좌표
            GetWindowRect(hWnd, &rc);

            // 디버그 printf("L: %d, R: %d, U: %d, D: %d", rc.left, rc.right, rc.top, rc.bottom);

            RECT rc2; // 버튼 기준 버튼 모서리 좌표
            rc2.left = 0;
            rc2.top = 0;
            rc2.right = rc.right - rc.left;
            rc2.bottom = rc.bottom - rc.top;

            SetBkMode(hdc, TRANSPARENT); // 글자의 배경색 투명하게

            COLORREF textColor = buttonTextColor[buttonIndex];
            SetTextColor(hdc, textColor); // 글자색

            HFONT hFont = CreateFont( // 폰트 Arial 24
                24,
                0,
                0,
                0,
                FW_NORMAL,
                FALSE,
                FALSE,
                FALSE,
                DEFAULT_CHARSET,
                OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY,
                DEFAULT_PITCH | FF_SWISS,
                L"Arial"
            );

            SelectObject(hdc, hFont); // 폰트 설정

            // 글자 그리기
            DrawText(hdc, buttonText, -1, &rc2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            rc2.top = rc2.bottom - 1;

            COLORREF shadowColor = buttonShadowColor[buttonIndex];
            hBrush = CreateSolidBrush(shadowColor);
            FillRect(hdc, &rc2, hBrush);
            DeleteObject(hBrush);

            EndPaint(hWnd, &ps); // 그리기 끝
        }
        break;

        case WM_MOUSEMOVE:
        {
            TRACKMOUSEEVENT event = {
                sizeof(event),
                TME_LEAVE,
                hWnd,
                HOVER_DEFAULT
            };
            TrackMouseEvent(&event);
        }
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }

    return 0;
}


// 전역 변수:
HINSTANCE hInst;                                 // 현재 인스턴스
WCHAR szTitle[MAX_LOADSTRING];                   // 제목 표시줄 텍스트
WCHAR szWindowClass[MAX_LOADSTRING];             // 창 클래스 이름
WCHAR szResultClass[MAX_LOADSTRING];             // 결과 블록 클래스 이름 


// 함수의 선언:
ATOM                RegisterWindowClass(HINSTANCE hInstance);
ATOM                RegisterResultClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    ResProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR    lpCmdLine,
                      _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 전역 문자열을 초기화
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_CALCULATOR, szWindowClass, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_RESULT, szResultClass, MAX_LOADSTRING);

    // 클래스 등록
    RegisterWindowClass(hInstance);
    RegisterResultClass(hInstance);

    // 창 만들기
    if (!InitInstance (hInstance, nCmdShow))
    {
        return GetLastError();
    }

    MSG msg;
    // 기본 메시지 루프:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}


//
//  함수: RegisterWindowClass()
//
//  용도: 창 클래스 등록
//
ATOM RegisterWindowClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CALCULATOR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_CALCULATOR));

    return RegisterClassExW(&wcex);
}

//
//  함수: RegisterResultClass()
//
//  용도: 결과 블록 클래스 등록
//
ATOM RegisterResultClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_DROPSHADOW;
    wcex.lpfnWndProc = ResProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = nullptr;
    wcex.hCursor = nullptr;
    wcex.hbrBackground = nullptr;
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = szResultClass;
    wcex.hIconSm = nullptr;

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창 만들기
//
//   주석:
//
//        인스턴스 핸들을 전역 변수에 저장
//        주 프로그램 창 만들고 표시
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장

    /* 모니터 화면 크기 구하기 */
    RECT rc;
    GetWindowRect(GetDesktopWindow(), &rc);
    int screenWidth = rc.right;
    int screenHeight = rc.bottom;

    /* 창 크기와 모니터에서의 좌표 */
    int windowWidth = 360;
    int windowHeight = 360;

    int posX = (screenWidth - windowWidth) / 2;
    int posY = (screenHeight - windowHeight) / 2;

    /* 창 만들기 */
    HWND hWnd = CreateWindowEx(
        0, 
        szWindowClass, 
        szTitle, 
        WS_OVERLAPPEDWINDOW,
        posX, posY, windowWidth, windowHeight, 
        nullptr, nullptr, hInstance, nullptr
    );

    if (!hWnd) {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);

    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지 처리
//
//  WM_CREATE   - 버튼 생성
//  WM_COMMAND  - 애플리케이션 메뉴 처리
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // 디버그
    // printf("WndProc: message %04x\n", message);
    // debug(message);

    static HWND hwndButtons[BUTTON_COUNT]; // 버튼의 핸들

    switch (message) {
    
    case WM_CREATE: // 창이 만들어질 때
    {
        // 빨간색을 투명하게 설정
        SetWindowLong(
            hWnd,
            GWL_EXSTYLE,
            GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED
        );
        SetLayeredWindowAttributes(hWnd, RGB(255, 0, 0), 0, LWA_COLORKEY);

        // 콘솔 창 열기
        AllocConsole();
        FILE* pConsole;
        freopen_s(&pConsole, "CONOUT$", "w", stdout);

        // 창 크기 
        RECT rc;
        GetClientRect(hWnd, &rc);
        int windowWidth = rc.right - rc.left;
        int windowHeight = rc.bottom - rc.top;

        // 버튼 만들기
        for (int i = 0; i < BUTTON_COUNT; ++i) {

            // 버튼 위치
            int posX, posY;
            if (i == 0) { // 숫자 0
                posX = 20 + 80;
                posY = windowHeight - 30 - 40;
            }
            else if (i >= 1 && i <= 9) { // 숫자 1-9
                posX = 20 + 80 * ((i - 1) % 3);
                posY = windowHeight - 30 - 40 - 55 * ((i + 2) / 3);
            }
            else if (i == 10) { // 지우기 버튼
                posX = 20 + 80 * 3;
                posY = windowHeight - 30 - 40 - 55 * 3;
            }

            // 버튼 이름
            wchar_t buttonText[20];
            wsprintf(buttonText, L"Button %d", i + 1);

            // 버튼에 해당하는 창 만들기
            hwndButtons[i] = CreateWindow(
                L"BUTTON",
                buttonText,
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
                posX,
                posY,
                60,
                40,
                hWnd,
                (HMENU)(i + 1),
                (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                NULL);

            // 버튼 콜백 등록
            SetWindowLongPtr(hwndButtons[i], GWLP_WNDPROC, (LONG_PTR)ButtonProc);
            buttonTextColor[i] = BUTTON_TEXT_COLOR;
            buttonBgColor[i] = BUTTON_BG_COLOR;

            buttonState[i] = 'u';
            buttonShadowColor[i] = BUTTON_SHADOW_COLOR;

            // 디버그 printf("Button %d: hwnd %d, proc %p, col %x\n", i, hwndButtons[i], GetWindowLongPtr(hwndButtons[i], GWLP_WNDPROC), buttonTextColors[i]);
        }

        // 결과 화면 위치
        int posX, posY;
        posX = 20;
        posY = windowHeight - 30 - 40 - 55 * 4;
        int w = 60 * 4 + 20 * 3;
        int h = 40;

        // 결과 화면 만들기
        hWndResult = CreateWindow(
            szResultClass,
            L"Result",
            WS_CHILD | WS_VISIBLE,
            posX,
            posY,
            w,
            h,
            hWnd,
            (HMENU)(BUTTON_COUNT + 1),
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL
        );

    }
    break;
    case WM_COMMAND: // 버튼을 눌렀을 때
    {
        int wmId = LOWORD(wParam);
        // 버튼이 클릭되서 메시지를 받은 경우
        if (wmId > 0 && wmId <= BUTTON_COUNT) {
            buttonState[wmId - 1] = 'c';
            // 디버그 printf("!!!Button %d clicked ... %c\n", wmId - 1, buttonState[wmId - 1]);
            break;
        }
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    break;
    case WM_PAINT: // 그림 그릴 때
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1)); // 일반 창 색깔
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DRAWITEM:
    {
        /* 디버그 
        int buttonIndex = LOWORD(wParam) - 1;
        printf("!!!Button %d WM_DRAWITEM ... %c \n", buttonIndex, state[buttonIndex]);
        */
    }
    break;

    case WM_DESTROY: // 창을 닫을 때
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK ResProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

    switch (message) {

    case WM_PAINT:
    {
        COLORREF resColor = RGB(200, 255, 200);
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        HBRUSH hBrush = CreateSolidBrush(resColor);
        FillRect(hdc, &ps.rcPaint, hBrush);

        wchar_t resultText[11] 
            = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0', '\0'};

        int trimed_result = result % 100000000;
        swprintf_s(resultText, 11, L"%10d", trimed_result);

        RECT rc;
        GetWindowRect(hWnd, &rc);

        //디버그 printf("L: %d, R: %d, U: %d, D: %d", rc.left, rc.right, rc.top, rc.bottom);

        RECT rc2;
        rc2.left = 0;
        rc2.top = 0;
        rc2.right = rc.right - rc.left - 10;
        rc2.bottom = rc.bottom - rc.top;

        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(50, 50, 50));

        HFONT hFont = CreateFont(
            24,
            0,
            0,
            0,
            FW_NORMAL,
            FALSE,
            FALSE,
            FALSE,
            DEFAULT_CHARSET,
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_SWISS,
            L"Arial"
        );

        SelectObject(hdc, hFont);

        DrawText(hdc, resultText, -1, &rc2, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
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

void debug(UINT message) {

    switch (message) {
    case WM_GETOBJECT:
        printf("WM_GETOBJECT\n");
        break;
    case WM_CAPTURECHANGED:
        printf("WM_CAPTURECHANGED\n");
        break;
    case WM_LBUTTONDOWN:
        printf("WM_LBUTTONDOWN\n");
        break;
    case BM_SETSTATE:
        printf("BM_SETSTATE\n");
        break;
    case WM_LBUTTONUP:
        printf("WM_LBUTTONUP\n");
        break;
    case WM_IME_NOTIFY:
        printf("WM_IME_NOTIFY\n");
        break;
    case WM_IME_SETCONTEXT:
        printf("WM_IME_SETCONTEXT\n");
        break;
    case WM_KILLFOCUS:
        printf("WM_KILLFOCUS\n");
        break;
    case WM_SETFOCUS:
        printf("WM_SETFOCUS\n");
        break;
    case WM_MOUSEACTIVATE:
        printf("WM_MOUSEACTIVATE\n");
        break;
    case WM_SETCURSOR:
        printf("WM_SETCURSOR\n");
        break;
    case WM_NCHITTEST:
        printf("WM_NCHITTEST\n");
        break;
    case WM_MOUSELEAVE:
        printf("WM_MOUSELEAVE\n");
        break;
    case WM_NCLBUTTONUP:
        printf("WM_NCLBUTTONUP\n");
        break;
    case WM_NCPAINT:
        printf("WM_NCPAINT\n");
        break;
    case WM_ERASEBKGND:
        printf("WM_ERASEBKGND\n");
        break;
    case WM_COMMAND:
        printf("WM_COMMAND\n");
        break;
    case WM_CREATE:
        printf("WM_CREATE\n");
        break;
    case WM_PAINT:
        printf("WM_PAINT\n");
        break;
    case WM_MOUSEMOVE:
        printf("WM_MOUSEMOVE\n");
        break;
    default:
        printf("WM_ %04x\n", message);
    }
}