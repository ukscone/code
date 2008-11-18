import javax.swing.*;
public class NameDropper
{
    public static void main(String [] args)
    {
        // create a frame
        JFrame frame = new JFrame("Name Dropper");

        // end the program when the frame is closed
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // create a NamePanel
        NamePanel panel = new NamePanel();

        // add the panel to the frame
        frame.getContentPane().add(panel);

        // set up size of frame
        frame.pack();

        // make it visible
        frame.setVisible(true);
    } // of main
} // of class 
