//Compiler : cl.exe /c /EHsc  Window.cpp /D "UNICODE"
//Linker :link.exe  Window.obj  user32.lib gdi32.lib /Subsystem:Windows

//header files
#include<Windows.h>
#define ID_NUMBER 501

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
	static int iPaintFlag = 0;
	HBRUSH hbrush;

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
	TCHAR str[255];
	int num1, num2, num3;
	//code
	switch (iMsg) {
		case WM_CREATE:
			SetTimer(hwnd, ID_NUMBER, 1000, NULL);
			break;
		case WM_TIMER :
			KillTimer(hwnd,ID_NUMBER);
			IPaint();
			InvalidateRect();
			SetTimer(hwnd, ID_NUMBER, 1000, NULL);

			break;
		/*case WM_KEYDOWN:
			wsprintf(str, TEXT("WM_KEYDOWN message is received!"));
			MessageBox(hwnd, str, TEXT("Message"), MB_OK);
			break;
		
		case WM_RBUTTONDOWN :
			wsprintf(str, TEXT(" WM_RBUTTONDOWN message is received!"));
			MessageBox(hwnd, str, TEXT("Message"), MB_OK);
			break;*/
		
		case WM_CHAR :
			switch (wParam) {
				case 'R':
				case 'r':
					//red
					iPaintFlag = 1;

				break;

				case 'G':
				case 'g':
					//green
					iPaintFlag = 2;

					break;

				case 'B':
				case 'b':
					//blue
					iPaintFlag = 3;

					break;

				case 'C':
				case 'c':
					//cycen
					iPaintFlag = 4;

					break;

				case 'M':
				case 'm':
					//magenta
					iPaintFlag = 5;

					break;

				case 'Y':
				case 'y':
					//yellow
					iPaintFlag = 6;

					break;

				case 'K':
				case 'k':
					//
					iPaintFlag = 7;

					break;
		
				case 'W':
				case 'w':
					//white
					iPaintFlag = 8;

					break;

				default:
					iPaintFlag = 0;

					break;

			}
			break;
		case WM_PAINT :

				repaint(); 
				BeginPaint();
				if (iPaintFlag == 1) {
					hbrush = CreateSolidBrush(RGB(255, 0, 0));
					InvalidateRect();
				}
				else if (iPaintFlag == 2) {
					hbrush = CreateSolidBrush(RGB(0, 255, 0));
					InvalidateRect();
				}
				else if (iPaintFlag == 3) {
					hbrush = CreateSolidBrush(RGB(0, 0, 255));
					InvalidateRect();
				}
				else if (iPaintFlag == 4) {
					hbrush = CreateSolidBrush(RGB(0, 255, 255));
					InvalidateRect();
				}
				else if (iPaintFlag == 5) {
					hbrush = CreateSolidBrush(RGB(255, 0, 255));
					InvalidateRect();
				}
				else if (iPaintFlag == 6) {
					hbrush = CreateSolidBrush(RGB(255, 255, 0));
					InvalidateRect();
				}
				else if (iPaintFlag == 7) {
					hbrush = CreateSolidBrush(RGB(0, 0, 0));
					InvalidateRect();
				}
				else if (iPaintFlag == 8) {
					hbrush = CreateSolidBrush(RGB(255, 255, 255));
					InvalidateRect();
				}
				else {
					hbrush = CreateSolidBrush(RGB(127, 127, 127));
					InvalidateRect();
				}
				FillRect(hdc,&rc,hbrush);
			break;
		/*case WM_SETFOCUS:
			wsprintf(str, TEXT("WM_SETFOCUS message is received!"));
			MessageBox(hwnd, str, TEXT("Message"), MB_OK);
			break;
		case WM_KILLFOCUS:
			wsprintf(str, TEXT("WM_KILLFOCUS message is received!"));
			MessageBox(hwnd, str, TEXT("Message"), MB_OK);
			break;*/
		case WM_DESTROY:
			wsprintf(str, TEXT("WM_DESTROY message is received!"));
			MessageBox(hwnd, str, TEXT("Message"), MB_OK);
			PostQuitMessage(0);
			break;
		default : 
			break;
	}
	return DefWindowProc(hwnd,iMsg,wParam,lParam);
}
