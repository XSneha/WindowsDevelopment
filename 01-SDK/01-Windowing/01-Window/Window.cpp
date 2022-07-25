//Compiler : cl.exe /c /EHsc  Window.cpp
//Linker :link.exe  Window.obj  user32.lib gdi32.lib /Subsystem:Windows

//header files
#include<Windows.h>

//global function declerations
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

//global variable declerations

//entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance , LPSTR lpszCmdLine, int iCmdShow) {
	//local variable declerations
	WNDCLASSEX wndClass;
	HWND hwnd;
	MSG msg;
	TCHAR szAPPName[] = TEXT("WINDEV-01-SDK-WINDOW");


	//code
	//wndclassEx initialization
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = hInstance;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndClass.lpszClassName = szAPPName;
	wndClass.lpszMenuName = NULL;
	wndClass.hIconSm = LoadIcon(NULL,IDI_APPLICATION);


	//registration of WNDClassEX
	RegisterClassEx(&wndClass);

	//creating the window
	hwnd = CreateWindow(szAPPName,
		TEXT("SCS:Window") ,
						WS_OVERLAPPEDWINDOW ,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						NULL,
						NULL,
						hInstance,
						NULL);

	//show window
	ShowWindow(hwnd, iCmdShow);


	//update the window
	UpdateWindow(hwnd);

	//message loop
	while(GetMessage(&msg,NULL,0,0)) {
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	//local variable declerations

	//code
	switch (iMsg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default : 
			break;
	}
	return DefWindowProc(hwnd,iMsg,wParam,lParam);
}
