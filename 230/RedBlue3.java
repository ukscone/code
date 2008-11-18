import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
/**
 * Shows a single listener for three buttons.
 * Implemented as an internal class.
 *
 * @author William Austad
 * 
 * modified by Jonathan Plona
 */
public class RedBlue3 extends JApplet
{
    private JButton redButton;
    private JButton blueButton;
    private JButton greenButton;
    private JLabel colorLabel;
    private int APPLET_WIDTH = 300, APPLET_HEIGHT = 100;
    private Container cp;

    /**
     * Called by the browser or applet viewer to inform this Applet 
     * that it has been loaded into the system. It is always called 
     * before the first time that the start method is called.
     */
    public void init()
    {
        // initialize red button
        redButton = new JButton("red");

        // add action listener
        redButton.addActionListener(new ButtonListener());

        // initialize blue button
        blueButton = new JButton("blue");

        // add action listener
        blueButton.addActionListener(new ButtonListener());

        //initialize green button
	greenButton = new JButton("green");

	//add action listener
	greenButton.addActionListener(new ButtonListener());

	//initialize color label
	colorLabel = new JLabel("");

	// get access to the applet's content pane
        cp = getContentPane();

        // set up the content pane
        cp.setBackground(Color.white);
        cp.setLayout (new FlowLayout());

        // add the buttons
        cp.add(redButton);
        cp.add(blueButton);
	cp.add(greenButton);
	cp.add(colorLabel);

        // set the size
        setSize (APPLET_WIDTH, APPLET_HEIGHT);
    }


    /**
     * ButtonListener implements a listener for both buttons
     */
    private class ButtonListener implements ActionListener
    {
        // performed when a button is pushed
        public void actionPerformed (ActionEvent event)
        {
            if(event.getSource() == redButton) {
                cp.setBackground(Color.red);
		colorLabel.setText("This color is Red.    ");
		colorLabel.setForeground(Color.black);
            } else if(event.getSource() == blueButton){
                cp.setBackground(Color.blue);
		colorLabel.setText("This color is Blue.   ");
		colorLabel.setForeground(Color.white);
            } else {
		cp.setBackground(Color.green);
		colorLabel.setText("This color is Green.  ");
		colorLabel.setForeground(Color.black);
	    }
            repaint ();
        }
    }
} 
