#ifndef PIXELSET_H_INCLUDED
#define PIXELSET_H_INCLUDED

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msgID, WPARAM, LPARAM);

int  DrawMandelbrotSet(HDC , int , int , int , int );
int  DrawMyRect(HDC, int, int, int, int);


#endif // PIXELSET_H_INCLUDED
