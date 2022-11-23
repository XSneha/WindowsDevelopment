
1. csc.exe /t:library DotNetServer.cs
2. ildasm /adv DotNetServer.dll
3. admin cmd prompt : regasm.exe DotNetServer.dll /tlb
4. search oleview.exe in windows kit, current path :C:\Program Files (x86)\Windows Kits\10\bin\10.0.19041.0\x64
5. run as admin -> file -> view type libraray -> select current tlb 

6. run client : cl.exe /c /EHsc Window.cpp 
7. link : link.exe window.obj user32.lib gdi32.lib ole32.lib oleaut32.lib /SUBSYSTEM:WINDOWS