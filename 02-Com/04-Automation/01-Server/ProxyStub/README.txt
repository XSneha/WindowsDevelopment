2 nd cmd 
On X64 cmd promp 
cd C:\WinDev2022\02-Com\04-Automation\01-Server\ProxyStub

1. midl.exe \h automationProxyStubHeader.h \iid AutomationProxyStubGuids.c \dlldata automationProxyStubDllData.c \proxy AutomationProxyStub.c AutomationServerTypeLib.idl
//midl.exe is going to create these files for us from AutomationServerTypelib.idl

midl.exe /h automationProxyStubHeader.h /iid AutomationProxyStubGuids.c /dlldata automationProxyStubDllData.c /proxy AutomationProxyStub.c AutomationServerTypeLib.idl

6 files expected :
one .h , three .c , one tlb and one idl
