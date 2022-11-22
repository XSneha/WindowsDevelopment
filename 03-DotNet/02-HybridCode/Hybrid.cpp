#include<stdio.h>
#using<MSCorLib.dll>
using namespace System;

int main(void) {
	printf("This line is from native C++!!!\n");
	Console::WriteLine("This line is from DotNet Managed C++");
	return 0;
}

//cl.exe /clr Hybrid.cpp 
// /clr support is added from v13 and above
