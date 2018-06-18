#define STRICT
#include <windows.h>
#include <mmsystem.h>
int WINAPI
WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, PSTR szCmdLine, int nCmdShow)
{
    MessageBox(nullptr, TEXT("Hello, welcome to windows!"), TEXT("»¶Ó­"), MB_OK|MB_ICONINFORMATION);
    return 0;
}
