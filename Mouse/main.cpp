#include <windows.h>
#include <math.h>
#include "resource.h"
#include "PixelSet.h"

/*  Make the class name into a global variable  */
char szClassName[ ] = "CodeBlocksWindowsApp";
HBITMAP hbmpLeft;
HBITMAP hbmpRight;

double PMin = -2.5, PMax = 0.9, QMin = -1.0, QMax = 1.0;
double newPMin, newPMax, newQMin, newQMax;

//
int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = TEXT("myMenu");                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx(
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               "Code::Blocks Template Windows App",       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               544,                 /* The programs width */
               375,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow(hwnd, nCmdShow);

    //
    hbmpLeft = LoadBitmap(hThisInstance, TEXT("MYBITMAP1"));
    hbmpRight = LoadBitmap(hThisInstance, TEXT("MYBITMAP2"));

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage(&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static  int cxClient, cyClient;
    static  bool  fleft = true;
    static  int  counts;
    HBITMAP hloadbmp = fleft ? hbmpLeft : hbmpRight;
    RECT rect = {0, 0, 300, 300};
    bool fErase = false;
    static POINT points[2];

    switch (message)                  /* handle the messages */
    {
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            GetClientRect(hwnd, &rect);
            HDC hdc = BeginPaint(hwnd, &ps);
//            HDC hmemdc = CreateCompatibleDC(hdc);

//            SelectObject(hmemdc, hloadbmp);
//            BitBlt(hdc, rect.left, rect.top, rect.bottom, rect.right, hmemdc, 0, 0, SRCAND);

            DrawMandelbrotSet(hdc, rect.left, rect.top, rect.right, rect.bottom);
            //DeleteDC(hmemdc);
            EndPaint(hwnd, &ps);
        }
        break;

    case WM_SIZE:
        {
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
        }
        break;

    case WM_LBUTTONDOWN:
        {
            points[0].x = LOWORD(lParam);
            points[0].y = HIWORD(lParam);
            newPMin = PMin + (PMax - PMin) * points[0].x / rect.right;
            newQMin = QMin + (QMax - QMin) * points[0].y / rect.bottom;
//            if ((wParam & MK_LBUTTON) || (wParam & MK_RBUTTON))
//            {
//                HDC hdc = GetDC(hwnd);
//                SetPixelV(hdc, LOWORD(lParam), HIWORD(lParam), RGB(0, 0, 0));
//
//                ReleaseDC(hwnd, hdc);
//            }
//
//            if ((LOWORD(lParam) <= rect.right) && (HIWORD(lParam) <= rect.bottom))
//            {
//                fleft = !fleft;
//                InvalidateRect(hwnd, &rect, TRUE);
//            }
        }
        break;
    case WM_LBUTTONUP:
        {
            points[1].x = LOWORD(lParam);
            points[1].y = HIWORD(lParam);
            fErase = false;
            if (points[1].x == points[0].x || points[1].y == points[0].y)
                break;
            newPMax = PMin + (PMax - PMin)*points[1].x / rect.right;
            newQMax = QMin + (QMax - QMin)*points[1].y / rect.bottom;
            if (newPMax > newPMin)
            {
                PMax = newPMax;
                PMin = newPMin;
            }
            else
            {
                PMax = newPMin;
                PMin = newPMax;
            }
            if (newQMax > newQMin)
            {
                QMax = newQMax;
                QMin = newQMin;
            }
            else
            {
                QMin = newQMax;
                QMax = newQMin;
            }
            InvalidateRect(hwnd, NULL, TRUE);
        }

        break;
    case WM_MOUSEMOVE:
        {
            if (wParam & MK_LBUTTON)
            {
                HDC hdc = GetDC(hwnd);
                SetROP2(hdc, R2_NOTXORPEN);
                if (fErase)
                    DrawMandelbrotSet(hdc, points[0].x, points[0].y, points[1].x, points[1].y);
                fErase = true;

                points[1].x = LOWORD(lParam);
                points[1].y = HIWORD(lParam);
                DrawMyRect(hdc, points[0].x, points[0].y, points[1].x, points[1].y);
                ReleaseDC(hwnd, hdc);
            }
        }
        break;
    case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
            case IDM_TIMER:
                {
                    SetTimer(hwnd, IDT_TIMER1, 1000, NULL);
                }
                break;

            case IDM_KILLTIMER:
                {
                    KillTimer(hwnd, IDT_TIMER1);
                }
                break;

            case IDM_ZOOMIN:
                {
                    newPMin = 4*PMin - 3*PMax;
                    newQMin = 4*QMin - 3*QMax;
                    newPMax = 4*PMax - 3*PMin;

                    PMin = newPMin;
                    PMax = newPMax;
                    QMin = newQMin;
                    InvalidateRect(hwnd, NULL, TRUE);
                }
                break;
            }
        }
        break;
SB_BOTTOM
SBS_HORZ
    case WM_TIMER:
        {
            switch (wParam)
            {
            case IDT_TIMER1:
                fleft = !fleft;
                InvalidateRect(hwnd, &rect, TRUE);
                break;

            case IDT_TIMER2:
                {
                    ++counts;
                }
                break;
            }
        }
        break;

    case WM_DESTROY:
        {
            //DeleteObject(hloadbmp);
            PostQuitMessage(0);        /* send a WM_QUIT to the message queue */
        }
        break;

    default:                      /* for messages that we don't deal with */
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}

int DrawMandelbrotSet(HDC hdc, int xMin, int yMin, int xMax, int yMax)
{
    double DetP, DetQ;
    double  q, p, x1, y1, x, y, r;
    int M = 100, K = 256, k;
    int nq, np;

    QMax = QMin + (PMax - PMin)*(yMax - yMin)/(xMax-xMin);
    DetP = (PMax - PMin)/(xMax - xMin);
    DetQ = (QMax - QMin)/(yMax - yMin);
    for (nq = yMin; nq <= yMax; ++nq)
        for (np = xMin; np <= xMax; ++np)
        {
            p = PMin + np*DetP;
            q = QMin + nq*DetQ;
            k = 0;
            x1 = x = y1 = y = 0;

            do
            {
                x = x1*x1 - y1*y1 - p;
                y = 2*x1*y1 + q;
                x1 = x;
                y1 = y;
                k++;
                r = x*x + y*y;
            }while (r<=M && k < K);

            if (k == K)
                k--;

            k = 255 - k;
            SetPixelV(hdc, np, nq, RGB(k,k,k));
        }
    return 1;
}

int DrawMyRect(HDC hdc, int x0, int y0, int x1, int y1)
{
    MoveToEx(hdc, x0, y0, NULL);
    LineTo(hdc, x0, y1);
    LineTo(hdc, x1, y1);
    LineTo(hdc, x0, y0);
    LineTo(hdc, x1, y0);
    return 1;
}
