using System;
using System.Runtime.InteropServices;

public class PInvoke
{
    [DllImport("User32.dll",CharSet=CharSet.Unicode)]
    public static extern int MessageBoxW(int handle, String message, String caption, int type);

    public static void Main()
    {
        MessageBoxW(0,"This is UNICODE MessageBox!","Message",0); //handle and type 0 means default
    }
}

//csc.exe PInvoke.cs
