/*
* Execution Steps :
* cl.exe /c /EHsc Window.cpp
* rc.exe window.rc
* link.exe window.obj  window.res user32.lib gdi32.lib ole32.lib oleaut32.lib /SUBSYSTEM:WINDOWS
*/

// header file
#include<windows.h>
#include"window.h"
#import "DotNetServer.tlb" no_namespace named_guids raw_interfaces_only


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
		MessageBox(NULL, TEXT("Com initialization Failed"), TEXT("ERROR"), MB_OK);
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
	//IMyMath* pIMath = NULL;
	IDispatch* pIDispatch = NULL;
	HRESULT hr;
	int num1, num2, sum, subtract;
	TCHAR str[255];
	OLECHAR* szFunctionName1 = L"SumOfTwoIntegers"; //BSTR - Binary string or basic string
	OLECHAR* szFunctionName2 = L"SubtractionOfTwoIntegers"; //BSTR - Binary string or basic string
	VARIANT vArg[2];
	VARIANT vResult;
	DISPID dispid;
	DISPPARAMS params;

	// code
	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoInitialize(NULL);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("Coinitialize Failed"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		//MessageBox(hwnd, TEXT("Coinitialize Done"), TEXT("Debug"), MB_OK);


		hr = CoCreateInstance(CLSID_DotNetServer, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch, (void**)&pIDispatch);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("Failed to get IDispatch Interface"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		//MessageBox(hwnd, TEXT("CoCreateInstance Done"), TEXT("Debug"), MB_OK);

		num1 = 275;
		num2 = 225;
		//pIMath->SumSumOfTwoIntegers(num1, num2, &sum);
		//get id of SumOfTwoIntegers

		//call SumOfTwoIntegers() by passing its ID to invoke
		VariantInit(vArg);						//initialize varg with default value
		vArg[0].vt = VT_INT;					//vt - variant type
		vArg[0].intVal = num2;					//value of argument
		vArg[1].vt = VT_INT;
		vArg[1].intVal = num1;
		params.rgvarg = vArg; 				//register varient arguments
		params.cArgs = 2; 						// count of arguments in vArg assigned to rgvarg
		params.rgdispidNamedArgs = NULL; 		//no named arguments
		params.cNamedArgs = 0;
		VariantInit(&vResult); 					//initialization of varient result

		hr = pIDispatch->GetIDsOfNames(IID_NULL,
			&szFunctionName1,//array base address
			1,//count of elements in 2nd parameter
			GetUserDefaultLCID(),//
			&dispid);

		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("Get IDs of Names failed to give ids of SumOfTwoIntegers()"), TEXT("ERROR"), MB_OK);
			pIDispatch->Release();
			pIDispatch = NULL;
			DestroyWindow(hwnd);
		}

		hr = pIDispatch->Invoke(dispid,
			IID_NULL,
			GetUserDefaultLCID(),
			DISPATCH_METHOD,
			&params,
			&vResult,
			NULL,
			NULL);
		sum = vResult.lVal;
		wsprintf(str, TEXT("Sum of %d and %d is %d"), num1, num2, sum);
		MessageBox(hwnd, str, TEXT("Sum"), MB_OK);

		//call SumOfTwoIntegers() by passing its ID to invoke
		//pIMath->SubtractionOfTwoIntegers(num1, num2, &subtract);
		//get id of SubtractionOfTwoIntegers
		hr = pIDispatch->GetIDsOfNames(IID_NULL,
			&szFunctionName2,//array base address
			1,//count of elements in 2nd parameter
			GetUserDefaultLCID(),//
			&dispid);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("Get IDs of Names failed to give ids of SubtractionOfTwoIntegers()"), TEXT("ERROR"), MB_OK);
			pIDispatch->Release();
			pIDispatch = NULL;
			DestroyWindow(hwnd);
		}
		//call SubtractionOfTwoIntegers() by passing its ID to invoke
		VariantInit(vArg);						//initialize varg with default value
		vArg[0].vt = VT_INT;					//vt - variant type
		vArg[0].intVal = num2;					//value of argument
		vArg[1].vt = VT_INT;
		vArg[1].intVal = num1;
		VariantInit(&vResult); 					//initialization of varient result
		params.rgvarg = vArg; 				//register varient arguments
		params.cArgs = 2; 						// count of arguments in vArg assigned to rgvarg
		params.rgdispidNamedArgs = NULL; 		//no named arguments
		params.cNamedArgs = 0;
		hr = pIDispatch->Invoke(dispid,
			IID_NULL,
			GetUserDefaultLCID(),
			DISPATCH_METHOD,
			&params,
			&vResult,
			NULL,
			NULL);
		subtract = vResult.lVal;

		wsprintf(str, TEXT("Substraction of %d and %d is %d"), num1, num2, subtract);
		MessageBox(hwnd, str, TEXT("Subtraction"), MB_OK);

		VariantClear(&vResult);
		VariantClear(vArg);
		pIDispatch->Release();
		pIDispatch = NULL;
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		CoUninitialize();
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}