using System;
using System.Runtime.InteropServices;

public class PInvoke
{
    [DllImport("User32.dll")]
    public static extern int MessageBoxA(int handle, String message, String caption, int type);

    public static void Main()
    {
        MessageBoxA(0,"This is ANSI MessageBox!","Message",0); //handle and type 0 means default
    }
}

//csc.exe PInvoke.cs
