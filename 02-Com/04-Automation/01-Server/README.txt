//Use VisualStudio64 bit cmd prompt 
1. AutomationServer.cpp , AutomationServer.h , AutomationServer.def 
build dll using above files

2. AutomationServerType.idl 
buil .tlb and 3 c file using midl.exe

3. create def file for proxy stub dll
Compile : cl.exe /c /EHsc /D REGISTER_PROXY_DLL AutomationProxyStub.c AutomationProxyStubGuids.c automationProxyStubDllData.c
link 	: link.exe AutomationProxyStub.obj AutomationProxyStubGuids.obj automationProxyStubDllData.obj /Dll /Def:AutomationProxyStub.def user32.lib Ole32.lib OleAut32.lib advapi32.lib RpcNS4.lib RpcRT4.lib /SUBSYSTEM:WINDOWS
link 	:(with custom dll name) 
link.exe AutomationProxyStub.obj AutomationProxyStubGuids.obj automationProxyStubDllData.obj /Dll /Def:AutomationProxyStub.def /out:myDll.dll user32.lib Ole32.lib OleAut32.lib advapi32.lib RpcNS4.lib RpcRT4.lib /SUBSYSTEM:WINDOWS

4. Register file

5. move below 3 files in C:/Windows/System32
DLL : AutomationServer.dll , ProxyStub/AutomationProxyStub.dll 
tlb : ProxyStub/AutomationServerTypeLib.tlb

6.close all other windows
one 64 bit commond with Administrator permission(Run as administrator)
check files with : dir automation*
Cmd : regsvr32.exe AutomationProxyStub.dll 
(register server 23 AutomationProxyStub.dll)
(message box will appear to register the entry, proceed with the registartion) 

 


