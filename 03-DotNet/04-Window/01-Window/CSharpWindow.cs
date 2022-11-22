using System;
using System.Windows.Forms;

public class CSharpWindow : Form
{
	public static void Main()
    {
        Application.Run(new CSharpWindow());
    }

    public CSharpWindow() 
    {
        Text = "My CSharp Window"; // this text is caption (create window 2nd parameter)
        BackColor = System.Drawing.Color.Black; //hbr background - black brush
        ResizeRedraw = true; 
    }
}

//csc.exe /t:winexe CSharpWindow.cs
