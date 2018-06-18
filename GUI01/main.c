//#undef WINVER
//#define WINVER 0x0501

#include "text.h"
#include "resource.h"

// 程序实例
HINSTANCE hThisInst;
HWND hdlgModeLess;

HBITMAP hbitmap;

// 缓冲区
TCHAR szBuffer[MAXSIZ];

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgMainLess(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = TEXT("CodeBlocksWindowsApp");

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE, PTSTR, int nCmdShow)
{
    hThisInst = hThisInstance;
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
    wincl.hIcon =  LoadIcon(hThisInstance, TEXT("myIcon"));
    wincl.hIconSm = NULL;
    wincl.hCursor = LoadCursor(hThisInstance, TEXT("MyCursor"));
    wincl.lpszMenuName = TEXT("myMenu");
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground =(HBRUSH)GetStockObject(WHITE_BRUSH); //(HBRUSH)(COLOR_WINDOW + 1);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx(
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               TEXT("Code::Blocks Template Windows App"),       /* Title Text */
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
    UpdateWindow(hwnd);     // 在进入消息循环之前，发送一条 WM_PAINT消息

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage(&messages, NULL, 0, 0))
    {
        if (IsWindow(hdlgModeLess) && IsDialogMessage(hdlgModeLess, &messages))
            continue;

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
    static  int cxClient, cyClient;     // 客户区的宽，高
    static  int cxChar, cyChar;         // 字符的宽度，高度
    static  int nLinesOnePage;
    
    switch (message)                  /* handle the messages */
    {
    case WM_CREATE:
        {
            // 获取主菜单
            HMENU  hmenu = GetMenu(hwnd);
            // 创建一个弹出式菜单
//            HMENU  hnew = CreatePopupMenu();
//            AppendMenu(hnew, MFT_STRING, IDM_ALIGN_CENTER, TEXT("居中对齐"));
//            AppendMenu(hnew, MFT_STRING|MFT_RADIOCHECK|MFS_CHECKED, IDM_ALIGN_LEFT, TEXT("左对齐"));
//            // 将它添加到主菜单
//            InsertMenu(hmenu, 2, MF_BYPOSITION|MF_POPUP|MF_STRING, (UINT)hnew, TEXT("添加"));

            // 初始化菜单
            CheckMenuRadioItem(hmenu, IDM_ALIGN_LEFT, IDM_ALIGN_RIGHT, IDM_ALIGN_LEFT, MF_BYCOMMAND);

            // 加载位图
            hbitmap = LoadBitmap(hThisInst, TEXT("myBmp"));
        }
        break;

    case WM_SIZE:
        {
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
        }
        break;

    case  WM_PAINT:
        {
//            TCHAR  szBuffer[BUFSIZ];   /// 如何得到资源字符串的具体长度
//            LoadString(hThisInst, IDS_SUN, szBuffer, BUFSIZ);
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
//            RECT rect;
//            GetClientRect(hwnd, &rect);
////            SetTextColor(hdc, RGB(255,0,0));
////            SetBkColor(hdc, GetPixel(hdc,0,0));
////            DrawText(hdc, szBuffer, -1, &rect, DT_SINGLELINE);

            // 显示位图
            HDC hmemDC = CreateCompatibleDC(hdc);
            SelectObject(hmemDC, hbitmap);
            BitBlt(hdc, 0, 0, 200, 200, hmemDC, 0, 0, SRCAND);
            DeleteDC(hmemDC);

            EndPaint(hwnd, &ps);
        }
        break;
    case WM_RBUTTONUP:
        {
            RECT rc;
            GetClientRect(hwnd, &rc);
            POINT pt;
            pt.x = LOWORD(lParam);
            pt.y = HIWORD(lParam);
            
            if (PtInRect(&rc, pt))
            {
                HMENU hmenuTrack = GetSubMenu(GetMenu(hwnd), 1);
                ClientToScreen(hwnd, &pt);
                TrackPopupMenu(hmenuTrack, TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, 0, hwnd, NULL);
            }
        }
        break;
        
    case WM_COMMAND:
        {
            WORD wID = LOWORD(wParam);

            switch (wID)
            {
            case IDM_FILE_NEW:
            case IDM_FILE_OPEN:
            case IDM_FILE_SAVE:
            case IDM_FILE_SAVE_ALL:
            case IDM_FILE_SAVE_AS:
                MessageBox(hwnd, TEXT("功能暂缺！敬请期待！"), TEXT("致谢"), MB_OK | MB_ICONASTERISK);

                break;

            case IDM_ALIGN_LEFT:
            case IDM_ALIGN_CENTER:
            case IDM_ALIGN_RIGHT:
                {
                    CheckMenuRadioItem(GetMenu(hwnd), IDM_ALIGN_LEFT, IDM_ALIGN_RIGHT, wID, MF_BYCOMMAND);
                }
                break;

            case IDM_STYLE_BOLD:
            case IDM_STYLE_ITALIC:
            case IDM_STYLE_UNDERLINE:
            case IDM_STYLE_DELLINE:
                {
                    HMENU hmenu = GetMenu(hwnd);

                    if (MFS_CHECKED & GetMenuState(hmenu, wID, MF_BYCOMMAND))
                        CheckMenuItem(hmenu, wID, MF_BYCOMMAND | MFS_UNCHECKED);
                    else
                        CheckMenuItem(hmenu, wID, MF_BYCOMMAND | MFS_CHECKED);
                }
                break;

            case IDM_DLG_MODE:
                {
                    DialogBox(hThisInst, TEXT("DLG_MAIN"), hwnd, DlgMain);
                }
                break;

            case IDM_DLG_MODELESS:
                {
                    if (hdlgModeLess == NULL)
                    {
                        hdlgModeLess = CreateDialog(hThisInst, TEXT("DLG_MAIN"), hwnd, DlgMainLess);
                        ShowWindow(hdlgModeLess, SW_SHOWNORMAL);
                    }
                    else
                    {
                        ShowWindow(hdlgModeLess, SW_HIDE);  /**< 如何直接激活对话框，而不是先隐藏一下 */
                        ShowWindow(hdlgModeLess, SW_SHOW);
                    }
                }
                break;

            case IDM_HELP:
                MessageBox(hwnd, TEXT("这是罗新征编写的！"), TEXT("About"), MB_OK | MB_ICONINFORMATION);

                break;

            case IDM_QUIT:
                SendMessage(hwnd, WM_CLOSE, 0, 0);
                break;

            default:
                break;
            }

        }
        break;

    case WM_DESTROY:
        DeleteObject(hbitmap);
        PostQuitMessage(0);        /* send a WM_QUIT to the message queue */
        break;

    default:                      /* for messages that we don't deal with */
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    UNREFERENCED_PARAMETER(cxChar);
    UNREFERENCED_PARAMETER(cxClient);
    UNREFERENCED_PARAMETER(cyClient);
    UNREFERENCED_PARAMETER(cyChar);
    UNREFERENCED_PARAMETER(nLinesOnePage);
    return 0;
}

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (uMsg)
    {
    case WM_INITDIALOG:
        {
        }

        return TRUE;

    case WM_CLOSE:
        {
            EndDialog(hwndDlg, 0);
        }

        return TRUE;

    case WM_COMMAND:   // 控件消息, 命令消息
        {
            switch (LOWORD(wParam))  // 消息参数
            {
            case IDOK:
                EndDialog(hwndDlg, 0);
                return TRUE;
            default:
                return TRUE;
            }
        }
        return TRUE;

    default:
        return FALSE;
    }
}

BOOL CALLBACK DlgMainLess(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (uMsg)
    {
    case WM_INITDIALOG:
        {
        }

        return TRUE;

    case WM_CLOSE:
        {
            DestroyWindow(hwndDlg);
            hdlgModeLess = NULL;
        }

        return TRUE;

    case WM_COMMAND:   // 控件消息
        {
            switch (LOWORD(wParam))  // 消息参数
            {
            case IDOK:
                {
                    DestroyWindow(hwndDlg);
                    hdlgModeLess = NULL;
                }

                return TRUE;
            default:
                return TRUE;
            }
        }
        return TRUE;

    default:
        return FALSE;
    }

    return FALSE;
}
