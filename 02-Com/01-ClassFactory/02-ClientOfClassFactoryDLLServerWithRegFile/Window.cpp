/*
* Execution Steps :
* cl.exe /c /EHsc Window.cpp
* rc.exe window.rc
* link.exe window.obj window.res user32.lib gdi32.lib ole32.lib oleaut32.lib /SUBSYSTEM:WINDOWS
*/

// header file
#include<windows.h>
#include "window.h"
#include "ClassFactoryDLLServerWithRegFile.h"

// functions declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// global variable declarations

// entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// local variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("WindowApp");
	HRESULT hr;

	//COM library initialization
	hr = CoInitialize(NULL);
	if (FAILED(hr)) {
		MessageBox(NULL,TEXT("Com initialization Failed"),TEXT("ERROR"),MB_OK);
		exit(0);
	}
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
		TEXT("BSM - First Window"),
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

	//COM uninitialization 
	CoUninitialize();

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// local variable declaration
	ISum* pISum = NULL;
	ISubstract* pISubstract = NULL;
	HRESULT hr;
	int n1, n2, sum, subtract;
	TCHAR str[255];

	// code
	switch (iMsg)
	{
	case WM_CREATE :
		hr = CoCreateInstance(CLSID_SumSubstract,NULL,CLSCTX_INPROC_SERVER,IID_ISum,(void**)&pISum);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("ISum can not be obtained"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		n1 = 55;
		n2 = 45;
		pISum->SumOfTwoIntegers(n1,n2,&sum);
		wsprintf(str,TEXT("Sum of %d and %d is %d"),n1,n2,sum);
		MessageBox(hwnd, str , TEXT("Sum"), MB_OK);

		pISum->QueryInterface(IID_ISubstract,(void**)&pISubstract);
		pISubstract->SubstractionOfTwoIntegers(n1,n2,&subtract);
		wsprintf(str, TEXT("Substraction of %d and %d is %d"), n1, n2, subtract);
		MessageBox(hwnd, str, TEXT("Subtraction"), MB_OK);

		//safe release
		if (pISubstract) {
			pISubstract->Release();
			pISubstract = NULL;
		}
		if (pISum) {
			pISum->Release();
			pISum = NULL;
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
