#include<iostream>

using namespace std;

using namespace Platform;

int main(Array<String^>^ args)
{
	//code
	String^ str = "Hello World!!!";
	wcout<<str->Data()<<endl;
	return 0;
}

//cl.exe /c /EHsc /ZW Hello.cpp
//link.exe Hello.obj vccorlib.lib runtimeobject.lib /SUBSYSTEM:CONSOLE
//link.exe Hello.obj vccorlib.lib /SUBSYSTEM:CONSOLE

