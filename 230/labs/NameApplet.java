import java.applet.Applet;
import java.awt.*;

public class NameApplet extends Applet 
{

	public void paint(Graphics g)
	{
		g.setColor(Color.blue);
		g.fillRect(0, 0, 200, 100);
		g.setColor(Color.white);
		g.drawString("Name:    Jonathan Plona", 30, 30);
		g.drawString("Class:     CS230 A07", 30, 45);
		g.drawString("Date:     11/5/2007", 30, 60);
		g.drawString("Title:      Lab 2", 30, 75);
	}
}
