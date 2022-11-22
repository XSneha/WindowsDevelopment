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
        Icon = new Icon("MyIcon.ico");
        Text = "My CSharp Window"; // this text is caption (create window 2nd parameter)
        BackColor = Color.Black; //hbr background - black brush
        ResizeRedraw = true;
        Width = 800;
        Height = 600;

        this.KeyDown += new KeyEventHandler(myKeyDown);
        this.MouseDown += new MouseEventHandler(myMouseDown);

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

    void myKeyDown(Object Sender,KeyEventArgs e)
    {
        MessageBox.Show("A key is Pressed!");
    }

    void myMouseDown(Object Sender, MouseEventArgs e) 
    {
        MessageBox.Show("Mouse key is clicked!");
    }
}

//csc.exe /t:winexe CSharpWindow.cs
