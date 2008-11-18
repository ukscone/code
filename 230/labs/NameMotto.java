import java.awt.*;
import javax.swing.*;

public class NameMotto
{
	public static void main(String[] args)
	{
		JFrame frame = new JFrame("Name Label");
		
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JPanel panel = new JPanel();
		panel.setBackground(Color.blue);
		panel.setPreferredSize(new Dimension(350, 50));
		
		JLabel name = new JLabel("Jonathan Plona");
		name.setForeground(Color.white);
		JLabel motto = new JLabel("What's a motto?");
		motto.setForeground(Color.white);
		JLabel motto1 = new JLabel("Nothin! What's a'motto with you?");
		motto1.setForeground(Color.white);
		
		panel.add(name);
		panel.add(motto);
		panel.add(motto1);
		
		frame.getContentPane().add(panel);
		
		frame.pack();
		
		frame.setVisible(true);
	}
}
