using System;
using System.Windows.Forms;
using System.Drawing;

public class CSharpWindow : Form
{
	public static void Main()
    {
        Application.Run(new CSharpWindow());
    }

    public CSharpWindow() 
    {
        Text = "My CSharp Window"; // this text is caption (create window 2nd parameter)
        BackColor = Color.Black; //hbr background - black brush
        ResizeRedraw = true;
        Width = 800;
        Height = 600;
    }

    //Win32-WM_PAINT
    protected override void OnPaint(PaintEventArgs pea)//Wparam and lparams of WM_PAINT
    {
        Graphics grfx = pea.Graphics;

        StringFormat strfmt = new StringFormat();
        strfmt.Alignment = StringAlignment.Center; //horizontal center
        strfmt.LineAlignment = StringAlignment.Center;//vertical center

        grfx.DrawString("Hello World!!!",
                        Font,
                        new SolidBrush(Color.Green),
                        ClientRectangle,
                        strfmt);
    }
}

//csc.exe /t:winexe CSharpWindow.cs
