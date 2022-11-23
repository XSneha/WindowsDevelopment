public class DotNetServer 
{ 
    public int SumOfTwoIntegers(int num1,int num2)
    {
        return num1 + num2;
    }

    public int SubtractionOfTwoIntegers(int num1, int num2)
    {
        return num1 - num2;
    }
}


//csc.exe /t:library DotNetServer.cs
//ildasm /adv DotNetServer.dll
// admin cmd prompt : regasm.exe DotNetServer.dll /tlb
//search oleview.exe in windows kit, current path :C:\Program Files (x86)\Windows Kits\10\bin\10.0.19041.0\x64
//run as admin -> file -> view type libraray -> select current tlb 
