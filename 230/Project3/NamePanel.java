import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
/**
 * NamePanel shows use of a JTextField to read in a String.
 * It contains a private listener class.
 *
 * @author William Austad
 * @version 12/7/04 ff
 */
public class NamePanel extends JPanel 
{
    // constants known through all of the class
    private final int PANEL_HEIGHT = 100;
    private final int PANEL_WIDTH = 250;
    private final Color BACK_COLOR = Color.ORANGE;

    // the text field when the user types input
    private JTextField text;

    // labels used to display messages
    private JLabel hello, name, request;

    /**
     * Constructor for NamePanel initializes the text field
     * several labels and such.
     */ 
    public NamePanel()
    {
        // initialize text area
        text = new JTextField(10);

        // hook up a listener
        text.addActionListener(new TextListener());

        // initialize the labels
        request = new JLabel("Please enter total inches.");
        hello = new JLabel("");

        // add components to this panel
        add(request);
        add(text);
        add(hello);

        // set the size
        setPreferredSize(new Dimension(PANEL_WIDTH, PANEL_HEIGHT));

        // set the color
        setBackground(BACK_COLOR);
    } // of constructor
    
    private String formatInches(int totalInches)
    {
    	int feet, inches;
    	feet = totalInches / 12;
    	inches = totalInches % 12;
    	String returnStr = "" + feet + " feet, and " + inches + " inches.";
    	return returnStr;
    }

    // This internal listener has access to any variables declared
    // outside of the main. This is quite convenient.
    private class TextListener implements ActionListener
    {
        public void actionPerformed(ActionEvent event)
        {
            String inputInches = text.getText();
            int totalInches = Integer.parseInt(inputInches);
            String outputStr  = formatInches(totalInches);
            hello.setText(outputStr);
        } // of actionPerformed
    } // of class TextListener
} // of class NamePanel
