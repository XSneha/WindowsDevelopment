/*
* cl.exe /c /EHsc /D UNICODE icon.cpp
* rc.exe window.rc
* link.exe icon.obj window.res user32.lib gdi32.lib kernel32.lib /SUBSYSTEM:WINDOWS 
*/
//createThread is from kernal32.lib

// header file
#include<windows.h>
#include "window.h"

// functions declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);
// global variable declarations

// entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// local variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("WindowApp");

	// code
	// initialize wndclass
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	// register wndclass 
	RegisterClassEx(&wndclass);

	// create window
	hwnd = CreateWindow(szAppName,
		TEXT("SCS - First Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	// message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// local variable declaration
	HANDLE hThread1 = NULL;
	HANDLE hThread2 = NULL;

	// code
	switch (iMsg)
	{
	case WM_CREATE:
		hThread1 = CreateThread(NULL,					// 1. Security attributes			: NULL	->	default 
			0,											// 2. Thread stack size				: 0		->	default = process stack size
			(LPTHREAD_START_ROUTINE)ThreadProcOne,		// 3. callback function with rules	: 1. ip -> LPVOID 2. return -> DWORD 
			(LPVOID)hwnd,								// 4. 
			0,											// 5. flag for suspention			: 0		-> run on create, don't suspende 
			NULL);										// 6. thread id						: parameterized variable

		hThread2 = CreateThread(NULL,
			0,
			(LPTHREAD_START_ROUTINE)ThreadProcTwo,
			(LPVOID)hwnd,
			0,
			NULL);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("This is my Message-BOX"), TEXT("Message"), MB_OK);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
 	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI ThreadProcOne(LPVOID param) {
	//variabled declerations:
	HDC hdc;
	TCHAR str[255];
	long i = 0;
	//code
	hdc = GetDC((HWND)param);
	SetBkColor(hdc,RGB(0,0,0));
	SetTextColor(hdc, RGB(255,255,0));
	for (i = 0; i < LONG_MAX; i++) {
		wsprintf(str,TEXT("Numbers in incrementing Order : %d",i));
		TextOut(hdc,5,5,str,wcslen(str)); //altername  wcslen -> lstrlen
	}
	ReleaseDC((HWND)param,hdc);
	return 0;
}

DWORD WINAPI ThreadProcTwo(LPVOID param) {
	//variabled declerations:
	HDC hdc;
	TCHAR str[255];
	long i = 0;
	//code
	hdc = GetDC((HWND)param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 255));
	for (i = LONG_MAX; i >= 0; i--) { //LONG_MAX :4294967294
		wsprintf(str, TEXT("Numbers in decrementing Order : %d", i));
		TextOut(hdc, 5, 20, str, wcslen(str)); //altername  wcslen -> lstrlen
	}
	ReleaseDC((HWND)param, hdc);
	return 0;
}