/* 
     _   _                           ____  _      _   _         _             
    | | | | __ _ _ __  _ __  _   _  | __ )(_)_ __| |_| |__   __| | __ _ _   _ 
    | |_| |/ _` | '_ \| '_ \| | | | |  _ \| | '__| __| '_ \ / _` |/ _` | | | |
    |  _  | (_| | |_) | |_) | |_| | | |_) | | |  | |_| | | | (_| | (_| | |_| |
    |_| |_|\__,_| .__/| .__/ \__, | |____/|_|_|   \__|_| |_|\__,_|\__,_|\__, |
                |_|   |_|    |___/                                      |___/ 
*/


#include <Windows.h> 
#include <assert.h> 
#include <stdio.h>
#include <gdiplus.h>
#include <math.h>
#include<mmsystem.h>


using namespace Gdiplus;


#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "gdi32.lib") 
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "winmm.lib")


#define Celebration 101
#define Heart       102


int i;

//Window 1 Variables
int X_S = 50, Y_S = 200;
struct ballon
{
    int X;
    int Y;
    int R;
    int G;
    int B;
};

int check_ballon_went_up = 0;

struct ballon B0, B1, B2, B3, B4, B5;

//-----------------------------------------

//Window 2 Variables
int X_HEART = 0, Y_HEART1 = 0, Y_HEART2 = 0;
int REFER_X, REFER_Y;
int R, G, B;
int ColorCheck = 1;

//-----------------------------------------

//Credit variables:

int isCredit = 0;
//-----------------------------------------

//Main Variables
int check_window = 0;
int cxsize, cysize;
//----------------------------------------

//Functions

void draw_ballon(HDC hdc, int baseX, int baseY, PAINTSTRUCT ps, int r, int g, int b);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam); 
void fill_ballon_struct(void);
void make_paper_scraps(HDC hdc, int X, int Y, PAINTSTRUCT);
void Bday_Text(HDC hdc, HWND hWnd, PAINTSTRUCT ps);
void window_1(HDC hdc, HWND hWnd, PAINTSTRUCT ps);
void window_2(HDC hdc, HWND hWnd, PAINTSTRUCT ps);
void Credit_Window(HDC hdc, HWND hWnd, PAINTSTRUCT ps);
double Calculate_Y_1(double X, BOOL *real1);
double Calculate_Y_2(double X, BOOL *real2);
void Active_side_pixels(HDC hdc, int X, int Y);
void instructor(HDC hdc);
int range_rand(int, int);

//-------------------------------------------

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    static TCHAR szClassName[] = TEXT("The Standard Window"); 
    static TCHAR szWindowName[] = TEXT("Happy Birthday Sir!!!");    

    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;

    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    HWND hWnd = NULL; 
    HBRUSH hBrush = NULL; 
    HCURSOR hCursor = NULL; 
    HICON hIcon = NULL; 
    HICON hIconSm = NULL; 

    WNDCLASSEX wndEx; 
    MSG msg; 

    ZeroMemory(&wndEx, sizeof(WNDCLASSEX)); 
    ZeroMemory(&msg, sizeof(MSG)); 

    hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH); 
    assert(hBrush); 

    hCursor = LoadCursor(NULL, IDC_ARROW); 
    assert(hCursor); 
 
    hIcon = LoadIcon(NULL, IDI_APPLICATION); 
    assert(hIcon); 

    hIconSm = LoadIcon(NULL, IDI_APPLICATION); 
    assert(hIconSm); 

    wndEx.cbSize = sizeof(WNDCLASSEX); 
    wndEx.cbClsExtra = 0; 
    wndEx.cbWndExtra = 0; 
    wndEx.hbrBackground = hBrush; 
    wndEx.hCursor = hCursor; 
    wndEx.hIcon = hIcon; 
    wndEx.hIconSm = hIconSm; 
    wndEx.hInstance = hInstance; 
    wndEx.lpfnWndProc = WndProc; 
    wndEx.lpszClassName = szClassName; 
    wndEx.lpszMenuName = NULL; 
    wndEx.style = CS_HREDRAW | CS_VREDRAW; 

    ATOM bRet = RegisterClassEx(&wndEx); 
    assert(bRet); 

    
    hWnd = CreateWindowEx( WS_EX_APPWINDOW, szClassName, szWindowName, 
                            WS_OVERLAPPED | WS_THICKFRAME | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
                           CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT , CW_USEDEFAULT, NULL, NULL, hInstance, NULL); 
    assert(hWnd != NULL); 

    ShowWindow(hWnd, nShowCmd); 
    UpdateWindow(hWnd); 

    //Fill colors of ballon before painting 
    //Fill all instances of struct ballon
    //It will fill and show maximum 6 ballons
    fill_ballon_struct();

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg); 
        DispatchMessage(&msg); 
    }

    Gdiplus::GdiplusShutdown(gdiplusToken);

    return (msg.wParam); 
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    char buffer[32];
    HDC hdc;
    PAINTSTRUCT ps;

    switch(uMsg)
    {
        case WM_SIZE:
            cysize = HIWORD(lParam);
            cxsize = LOWORD(lParam);
            break;

        case WM_TIMER:
            switch(wParam)
            {
                case Celebration:
                    if(isCredit == 1)
                    {
                        KillTimer(hWnd, 101);
                        InvalidateRect(hWnd, NULL, TRUE);
                        break;
                    }
                    KillTimer(hWnd, 101);
                    B0.Y = B0.Y - 3;
                    B1.Y = B1.Y - 2;
                    B2.Y = B2.Y - 3;
                    B3.Y = B3.Y - 4;
                    B4.Y = B4.Y - 3;
                    B5.Y = B5.Y - 4;
                    Y_S = Y_S + 3;
                    
                    //Change color of heart
                    R = range_rand(0, 255);
                    G = range_rand(0, 255);
                    B = range_rand(0, 255);

                    if(check_window % 2 != 0)
                    {
                        InvalidateRect(hWnd, NULL, TRUE);
                        SetTimer(hWnd, 101, 1000, NULL);
                        break;
                    }

                    if(B0.Y < 25 && B1.Y < 25 && B2.Y < 25 && B3.Y < 25 && B4.Y < 25 && B5.Y < 25)
                    {
                        check_ballon_went_up++;
                        B0.Y = cysize - 100;
                        B1.Y = cysize - 250;
                        B2.Y = cysize - 200;
                        B3.Y = cysize - 150;
                        B4.Y = cysize - 50;
                        B5.Y = cysize - 100;

                        InvalidateRect(hWnd, NULL, TRUE);
                        SetTimer(hWnd, 101, 50, NULL);
                    }
                    else
                    {
                        InvalidateRect(hWnd, NULL, TRUE);
                        SetTimer(hWnd, 101, 50, NULL);
                    }
                    break;
            }
            break;
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            instructor(hdc);
            if(isCredit == 1)
            {
                Credit_Window(hdc, hWnd, ps);
                EndPaint(hWnd, &ps);
                break;
            }
            if(check_window % 2 == 0)
            {
                window_1(hdc, hWnd, ps);
            }
            else
            {
                window_2(hdc, hWnd, ps);
            }
            EndPaint(hWnd, &ps);
            break;
        case WM_KEYDOWN:
            switch(wParam)
            {
                case VK_SPACE:
                    PlaySound((LPCSTR)"HBD_Song.wav", NULL, SND_LOOP | SND_ASYNC);
                    isCredit = 0;
                    SetTimer(hWnd, 101, 500, NULL);
                    break;

                case VK_RETURN:
                    PlaySound(NULL, 0, 0);
                    check_window++;
                    isCredit = 0;

                    if(check_window % 2 != 0)
                    {
                        PlaySound((LPCSTR)"Soft_Music.wav", NULL, SND_LOOP | SND_ASYNC);
                    }
                    else
                    {
                        PlaySound((LPCSTR)"HBD_Song.wav", NULL, SND_LOOP | SND_ASYNC);
                    }

                    SetTimer(hWnd, 101, 500, NULL);

                    break;

                case VK_SHIFT:
                    isCredit = 1;
                    break;
            }
            break;
        case WM_DESTROY: 
            PostQuitMessage(0); 
            break; 
    }

    return (DefWindowProc(hWnd, uMsg, wParam, lParam)); 
}

void fill_ballon_struct(void)
{
    //Ballon No. 0:
    B0.X = 0 + 100;
    B0.Y = cysize - 100;
    B0.R = 200;
    B0.G = 0;
    B0.B = 0;

    //Ballon No. 1:
    B1.X = B0.X + cxsize/6 + 100;
    B1.Y = cysize - 250;
    B1.R = 255;
    B1.G = 255;
    B1.B = 0;

    //Ballon No. 2:
    B2.X = B1.X + cxsize/6 + 100;
    B2.Y = cysize - 200;
    B2.R = 0;
    B2.G = 200;
    B2.B = 0;

    //Ballon No. 3:
    B3.X = B2.X + cxsize/6 + 100;
    B3.Y = cysize - 150;
    B3.R = 0;
    B3.G = 0;
    B3.B = 200;

    //Ballon No. 4:
    B4.X = B3.X + cxsize/6 + 100;
    B4.Y = cysize - 50;
    B4.R = 203;
    B4.G = 132;
    B4.B = 190;

    //Ballon No. 5:
    B5.X = B4.X + cxsize/6 + 100;
    B5.Y = cysize - 100;
    B5.R = 165;
    B5.G = 0;
    B5.B = 172;
}

void draw_ballon(HDC hdc, int baseX, int baseY, PAINTSTRUCT ps, int r, int g, int b)
{
    DWORD pen_style = PS_SOLID;
	COLORREF col = RGB(0, 0, 0);

	HPEN hPen1 = CreatePen(pen_style, 5, col);
	HPEN holdPen = (HPEN)SelectObject(hdc, hPen1);

    //Color of ballon
    SetDCBrushColor(hdc, RGB(r, g, b));
    SelectObject(ps.hdc, GetStockObject(DC_BRUSH));

    //Ballon
    Ellipse(ps.hdc, baseX, baseY - 20, baseX + 100, baseY + 100);

	//String
	POINT mid_section[] = { POINT{baseX + 50, baseY + 100}, POINT{ baseX + 50, baseY + 250 } };
	Polyline(hdc, mid_section, 2);

	//Left Leg
	POINT leg_1[] = { POINT{baseX + 50, baseY + 100}, POINT{ baseX + 25, baseY + 125 } };
	Polyline(hdc, leg_1, 2);

	//Right Leg
	POINT leg_2[] = { POINT{baseX + 50, baseY + 100}, POINT{ baseX + 80, baseY + 125 } };
	Polyline(hdc, leg_2, 2);

    //Join Line
    POINT line_3[] = {POINT{baseX + 25, baseY + 125}, POINT{baseX + 80, baseY + 125}};
    Polyline(hdc, line_3, 2);

}

void make_paper_scraps(HDC hdc, int X, int Y, PAINTSTRUCT ps)
{
    int i;
    int j;

    DWORD pen_style = PS_SOLID;
	COLORREF col = RGB(200, 0, 0);
	HPEN hPen2 = CreatePen(pen_style, 7, col);
	HPEN holdPen2 = (HPEN)SelectObject(hdc, hPen2);

    for(j = 0; j < 5; j++)
    {
        for(i = 0; i < cxsize/300; i++)
        {
            col = RGB(200, 0, 0);
            hPen2 = CreatePen(pen_style, 7, col);
            holdPen2 = (HPEN)SelectObject(hdc, hPen2);
            
            //Scrap 1
            //Color : Red

            POINT scrap1[] = {POINT{X, Y} , POINT{X + 15, Y + 15}, POINT{X , Y + 30}, POINT{X + 15, Y + 45}};
            Polyline(hdc, scrap1, 4);

            X = X + 100;
            Y = Y + 100 - 10 * i;

            DeleteObject(hPen2);
            DeleteObject(holdPen2);

            //Scrap 2
            //Color : Green

            col = RGB(0, 200, 0);
            hPen2 = CreatePen(pen_style, 7, col);
            holdPen2 = (HPEN)SelectObject(hdc, hPen2);

            POINT scrap2[] = {POINT{X, Y} , POINT{X + 15, Y + 15}, POINT{X + 30, Y}, POINT{X + 45, Y + 15}};
            Polyline(hdc, scrap2, 4);

            X = X + 100;
            Y = Y - 100 + 10 * i - 70 + 2 * i;

            DeleteObject(hPen2);
            DeleteObject(holdPen2);
            
            //Scrap 3
            //Color : Blue
            col = RGB(0, 0, 200);
            hPen2 = CreatePen(pen_style, 7, col);
            holdPen2 = (HPEN)SelectObject(hdc, hPen2);

            SetDCBrushColor(hdc, RGB(0, 0, 200));
            SelectObject(ps.hdc, GetStockObject(DC_BRUSH));

            Rectangle(hdc, X, Y, X + 20, Y + 20);

            Y = Y + 100;
            X = X + 100;

            DeleteObject(hPen2);
            DeleteObject(holdPen2);
        }
        Y = Y - 500;
        X = 50;
    }
}

void Bday_Text(HDC hdc, HWND hWnd, PAINTSTRUCT ps)
{ 
    DWORD pen_style = PS_SOLID;
	COLORREF col = RGB(0, 0, 0);
	HPEN hPen2 = CreatePen(pen_style, 7, col);
	HPEN holdPen2 = (HPEN)SelectObject(hdc, hPen2);


    POINT box[] = {POINT{cxsize/2 - 300, cysize/2 - 160}, POINT{cxsize/2  + 300, cysize/2 - 160}, POINT{cxsize/2  + 300, cysize/2 - 70}, POINT{cxsize/2  - 300, cysize/2 - 70}, POINT{cxsize/2  - 300, cysize/2 - 160}};

    Polyline(hdc, box, 5);

    RECT rc = {cxsize/2 - 300, cysize/2 - 150, cxsize/2  + 300, cysize + 150};

    HFONT hEnglishFont = CreateFontA(50, 25, -1, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_CHARACTER_PRECIS,
		CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("MyFont"));

    HFONT hOldFont = (HFONT)SelectObject(hdc, hEnglishFont);
    SetBkColor(hdc, RGB(255, 255, 255));

    DrawTextW(hdc, L"HAPPY BIRTHDAY SIR", wcslen(L"Happy Birthday Sir"), &rc, DT_VCENTER | DT_CENTER | DT_WORDBREAK | DT_NOCLIP);

    DeleteObject(hOldFont);
    DeleteObject(hEnglishFont);
}


void window_1(HDC hdc, HWND hWnd, PAINTSTRUCT ps)
{
    draw_ballon(hdc, B0.X, B0.Y, ps, B0.R, B0.G, B0.B);
    draw_ballon(hdc, B1.X, B1.Y, ps, B1.R, B1.G, B1.B);
    draw_ballon(hdc, B2.X, B2.Y, ps, B2.R, B2.G, B2.B);
    draw_ballon(hdc, B3.X, B3.Y, ps, B3.R, B3.G, B3.B);
    draw_ballon(hdc, B4.X, B4.Y, ps, B4.R, B4.G, B4.B);
    draw_ballon(hdc, B5.X, B5.Y, ps, B5.R, B5.G, B5.B);

    if(Y_S > 900)
    {
        Y_S = 700;
    }

    make_paper_scraps(hdc, X_S, Y_S, ps);
    Bday_Text(hdc, hWnd, ps);    
}

void window_2(HDC hdc, HWND hWnd, PAINTSTRUCT ps)
{
    RECT rect;
    GetClientRect(hWnd, &rect);

    SetDCBrushColor(hdc, RGB(206, 255, 212));
    HBRUSH brush = (HBRUSH)GetStockObject(DC_BRUSH);

    FillRect(hdc, &rect, brush);

    char buf[32];
    REFER_X = cxsize/2;
    REFER_Y = cysize/2;

    X_HEART = 700;
    Y_HEART1 = 0;
    Y_HEART2 = 0;

    double X_Dob = X_HEART / 300;
    double Y2_Dob, Y3_Dob;

    int x = 0, y = 0;

    RECT rc = {cxsize/2 - 300, cysize/2 - 200, cxsize/2  + 300, cysize + 100};
    FillRect(hdc, &rc, brush);

    HFONT hEnglishFont = CreateFontA(30, 15, -1, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_CHARACTER_PRECIS,
		CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("MyFont"));

    SetBkColor(hdc, RGB(206, 255, 212));

    HFONT hOldFont = (HFONT)SelectObject(hdc, hEnglishFont);

    DeleteObject(hOldFont);
    DeleteObject(hEnglishFont);

    DWORD pen_style = PS_SOLID;
	COLORREF col = RGB(0, 255, 0);
	HPEN hPen2 = CreatePen(pen_style, 4, col);
	HPEN holdPen2 = (HPEN)SelectObject(hdc, hPen2);

    POINT x_axis[] = { POINT{0, cysize/2}, POINT{cxsize, cysize/2}};
	Polyline(hdc, x_axis, 2);

    POINT y_axis[] = {POINT{cxsize / 2, 0}, POINT{cxsize/2, cysize}};
    Polyline(hdc, y_axis, 2);

    DeleteObject(hPen2);
    DeleteObject(holdPen2);

    hPen2 = CreatePen(pen_style, 1, col);
	holdPen2 = (HPEN)SelectObject(hdc, hPen2);

    for(x = 0; x < cxsize; x = x + 100)
    {
        y_axis[0] = POINT{x, 0};
        y_axis[1] = POINT{x, cysize};
	    Polyline(hdc, y_axis, 2);
    }

    for(y = 0; y < cysize; y = y + 100)
    {
        x_axis[0] = POINT{0, y};
        x_axis[1] = POINT{cxsize, y};
	    Polyline(hdc, x_axis, 2);
    }

    DrawTextW(hdc, L"(x^2 + y^2 - 1)^3 = x^2.y^3", wcslen(L"(x^2 + y^2 - 1)^3 = x^2.y^3"), &rc, DT_VCENTER | DT_CENTER | DT_WORDBREAK | DT_NOCLIP);

    while(X_HEART > -701)
    {
        X_Dob = (float)X_HEART / 300;
        BOOL real1;
        BOOL real2;
        X_HEART--;
        Y_HEART1 = (int)(300 * Calculate_Y_1(X_Dob, &real1));
        if(!real1)
            continue;
        Y_HEART2 = (int)(300 * Calculate_Y_2(X_Dob, &real2));
        if(!real2)
            continue;
        
        SetPixel(hdc, REFER_X + X_HEART + 1, REFER_Y - Y_HEART1, RGB(R, G, B));
        Active_side_pixels(hdc, REFER_X + X_HEART + 1, REFER_Y - Y_HEART1);
        SetPixel(hdc, REFER_X + X_HEART + 1, REFER_Y - Y_HEART2, RGB(R, G, B));
        Active_side_pixels(hdc, REFER_X + X_HEART + 1, REFER_Y - Y_HEART2);
    }

    DeleteObject(brush);
    DeleteObject(hPen2);
    DeleteObject(holdPen2);
}

void Credit_Window(HDC hdc, HWND hWnd, PAINTSTRUCT ps)
{

    //Credit Window Scene

    int x, y;

    DWORD pen_style = PS_SOLID;
	COLORREF col = RGB(0, 255, 0);

	HPEN hPen2 = CreatePen(pen_style, 4, col);
	HPEN holdPen2 = (HPEN)SelectObject(hdc, hPen2);

    RECT rect;
    GetClientRect(hWnd, &rect);

    RECT rc = {rect.left , rect.top + cysize/2 - 100, rect.right, rect.bottom};

    
    SetDCBrushColor(hdc, RGB(206, 255, 212));
    HBRUSH brush = (HBRUSH)GetStockObject(DC_BRUSH);

    FillRect(hdc, &rect, brush);

    POINT x_axis[] = { POINT{0, cysize/2}, POINT{cxsize, cysize/2}};
	Polyline(hdc, x_axis, 2);

    POINT y_axis[] = {POINT{cxsize / 2, 0}, POINT{cxsize/2, cysize}};
    Polyline(hdc, y_axis, 2);

    DeleteObject(hPen2);
    DeleteObject(holdPen2);

    hPen2 = CreatePen(pen_style, 1, col);
	holdPen2 = (HPEN)SelectObject(hdc, hPen2);

    for(x = 0; x < cxsize; x = x + 100)
    {
        y_axis[0] = POINT{x, 0};
        y_axis[1] = POINT{x, cysize};
	    Polyline(hdc, y_axis, 2);
    }

    for(y = 0; y < cysize; y = y + 100)
    {
        x_axis[0] = POINT{0, y};
        x_axis[1] = POINT{cxsize, y};
	    Polyline(hdc, x_axis, 2);
    }

    HFONT hEnglishFont = CreateFontA(35, 15, -1, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_CHARACTER_PRECIS,
		CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_SWISS , TEXT("MyFont"));

    SetBkColor(hdc, RGB(206, 255, 212));

    HFONT hOldFont = (HFONT)SelectObject(hdc, hEnglishFont);

    DrawTextW(hdc, L"Ignited by :\nYogeshwar Shukla Sir\n\nTechnology Used : Win32SDK\nMade by : Yash Thakare\nGuidance by : Prateek Thakare", 
            114, &rc, DT_VCENTER | DT_CENTER | DT_WORDBREAK | DT_NOCLIP);

}

void instructor(HDC hdc)
{
    char msg[] = "Press: Space - Start Celebration | Enter - Change Scene | Shift - Credit Window";
    TextOut(hdc, cxsize/2 - 200, cysize - 50, msg, strlen(msg));
}

double Calculate_Y_1(double X, BOOL *real)
{
    double Y;
    double XRAISEDto2by3 = cbrt((X * X));
    double discriminiant = XRAISEDto2by3 * XRAISEDto2by3 - 4*(X * X - 1);

    if(discriminiant >= 0)
    {
        Y = (XRAISEDto2by3 + sqrt(discriminiant))/2;
        *real = TRUE;
    }
    else
    {
        *real = FALSE;
    }

    return(Y);
}

double Calculate_Y_2(double X, BOOL *real)
{
    double Y;
    double XRAISEDto2by3 = cbrt((X * X));
    double discriminiant = XRAISEDto2by3 * XRAISEDto2by3 - 4*(X * X - 1);

    if(discriminiant >= 0)
    {
        Y = (XRAISEDto2by3 - sqrt(discriminiant))/2;
        *real = TRUE;
    }
    else
        *real = FALSE;

    return(Y);
}

void Active_side_pixels(HDC hdc, int X, int Y)
{

    //Active Side Pixels : It will activate all 8 pixel around a pixel.

    SetPixel(hdc, X - 1, Y + 1, RGB(R, G, B));
    SetPixel(hdc, X + 1, Y - 1, RGB(R, G, B));
    SetPixel(hdc, X - 1, Y - 1, RGB(R, G, B));
    SetPixel(hdc, X + 1, Y + 1, RGB(R, G, B));
    SetPixel(hdc, X - 1, Y    , RGB(R, G, B));
    SetPixel(hdc, X    , Y + 1, RGB(R, G, B));
    SetPixel(hdc, X + 1, Y    , RGB(R, G, B));
    SetPixel(hdc, X    , Y - 1, RGB(R, G, B));

}

int range_rand(int Start, int End)
{

    //Will Produce random number between range:

    int num;
    num = rand() % End + Start;
    return(num);

}
