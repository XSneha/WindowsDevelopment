//cl.exe /c /EHsc MyMathOne.c
//link.exe MyMathOne.obj /DLL User32.lib
//link.exe MyMathTwo.obj / DLL / DEF:MyMathTwo.def User32.lib /SUBSYSTEM : WINDOWS

//cl.exe / c / eHsc MyMathTwo.c
//link.exe MyMathTwo.obj / DLL / DEF:MyMathTwo.def / SUBSYSTEM : WINDOWS

#include<Windows.h>

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReveresed){
	//code
	switch (dwReason) {
		case DLL_PROCESS_ATTACH : 
			break;
		case DLL_THREAD_ATTACH :
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH :
				break;
		default :
			break;
	}

	return TRUE;
}

int makeCube(int num) {
	//code
	return num * num * num * num;
}
