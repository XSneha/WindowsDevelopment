using System;
using System.Runtime.InteropServices;

public class PInvoke
{
    [DllImport("MyMathTwo.dll")]
    public static extern int makeCube(int num);

    public static void Main()
    {
        int num1 = 5;
        int num2 = makeCube(num1);
        Console.WriteLine("Cube of "+num1 +" is "+num2+" !!!");
    }
}

//csc.exe PInvoke.cs
