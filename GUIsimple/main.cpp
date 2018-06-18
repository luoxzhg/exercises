#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"

HINSTANCE hInst;

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HCURSOR hOldCursor = NULL,
                   hNewCursor = LoadCursor(hInst, TEXT("myCursor"));

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

//    case WM_LBUTTONDOWN:
//    case WM_LBUTTONUP:
//    case WM_MOUSEMOVE:
//        {
//            hOldCursor = SetCursor(hNewCursor);
//        }
//
//        return TRUE;
    case WM_COMMAND:   // 控件消息
        {
            switch (LOWORD(wParam))  // 消息参数
            {
            case IDOK:
                EndDialog(hwndDlg, 0);
                return TRUE;

            }
        }

        return TRUE;
    }

    return FALSE;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE , LPSTR lpCmdLine, int nShowCmd)
{
    hInst = hInstance;
    InitCommonControls();

    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}
