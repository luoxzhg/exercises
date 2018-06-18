#include <windows.h>
#include <w32api.h>

#define BUFSIZE  0xffff
#define SHIFTED  0x8000
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

// Global variables
HINSTANCE hThis;
HWND      hwndMain;



/*  Make the class name into a global variable  */
char szClassName[] = "CodeBlocksWindowsApp";

int WINAPI WinMain(HINSTANCE hThisInstance,
                   HINSTANCE,
                   LPSTR lpszArgument,
                   int nCmdShow)
{
    UNREFERENCED_PARAMETER(lpszArgument);
    hThis = hThisInstance;

    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;             /* Catch double-clicks */
    wincl.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wincl))
    {
        return EXIT_FAILURE;
    }

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
    if (hwnd == NULL)
    {
        return EXIT_FAILURE;
    }
    hwndMain = hwnd;
    /* Make the window visible on the screen */
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage(&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return (int)messages.wParam;
}

/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int cxChar, cyChar, cxClient, cyClient, nLineLength, nLines;
    static int nCaretPosX, nCaretPosY;
    static int cChar, nCurCharIndex;
    static PTSTR  pchCharBuf;

    switch (message)                  /* handle the messages */
    {
    case WM_CREATE:
        {
            TEXTMETRIC tm;
            HDC hdc = GetDC(hwnd);
            GetTextMetrics(hdc, &tm);
            ReleaseDC(hwnd, hdc);
            // cxChar, cyChar 为逻辑单位值
            cxChar = tm.tmAveCharWidth;
            cyChar = tm.tmHeight + tm.tmExternalLeading;

            pchCharBuf = (PTSTR)GlobalAlloc(GPTR, sizeof(TCHAR) * BUFSIZE);

            CreateCaret(hwnd, (HBITMAP)NULL, 1, cyChar);
        }
        break;

    case WM_SIZE:
        {
            // FIXME: WM_SIZE的是设备值, 而 cxChar和cyChar使用的是逻辑单位。如何将设备单位值转换为逻辑单位值？？？

            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);

            nLineLength = cxClient / cxChar;
            nLines = cyClient / cyChar;
        }
        break;
    case WM_SETFOCUS:
        {
            SetCaretPos(nCaretPosX, nCaretPosY * cyChar);
            ShowCaret(hwnd);
        }
        break;

    case WM_KILLFOCUS:
        {
            HideCaret(hwnd);
        }
        break;

    case WM_CHAR:
        {
            HideCaret(hwnd);
            switch (wParam)
            {
            
            
            case '\b':
            
                MessageBeep(MB_ICONWARNING);
                break;
                
            case '\t':
                for (int i = 0; i < 4; ++i)
                    SendMessage(hwnd, WM_CHAR, ' ', 1);
                break;
                
            case '\r':
            case '\n':
                {
                    pchCharBuf[cChar++] = '\n';
                    
                    nCaretPosX = 0;
                    ++nCaretPosY;
                }
                break;
                
            default:
                {
                    TCHAR  ch = (TCHAR)wParam;
                    int  nCharWidth;

                    HDC hdc = GetDC(hwnd);
                    GetCharWidth(hdc, ch, ch, &nCharWidth);   // 得到的是逻辑值
                    TextOut(hdc, nCaretPosX, nCaretPosY * cyChar, &ch, 1);
                    ReleaseDC(hwnd, hdc);

                    pchCharBuf[cChar++] = ch;

                    // 计算插入符的新位置
                    nCaretPosX += nCharWidth;
                    if (nCaretPosX >= nLineLength * cxChar)
                    {
                        nCaretPosX = 0;
                        ++nCaretPosY;
                    }
                }
                break;
            }
            InvalidateRect(hwnd, NULL, TRUE);
            SetCaretPos(nCaretPosX, nCaretPosY * cyChar);
            ShowCaret(hwnd);
        }
        break;

    case WM_PAINT:
        {
            if (cChar == 0)
            {
                DefWindowProc(hwnd, message, wParam, lParam);
                break;
            }

            HideCaret(hwnd);

            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            RECT rc;
            SetRect(&rc, 0, 0, cxClient, cyClient);
            DrawText(hdc, pchCharBuf, -1, &rc, DT_LEFT);
            EndPaint(hwnd, &ps);

            ShowCaret(hwnd);
        }
        break;

    case WM_DESTROY:
        {
            DestroyCaret();
            GlobalFree((HGDIOBJ)pchCharBuf);

            PostQuitMessage(0);        /* send a WM_QUIT to the message queue */
        }
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}
