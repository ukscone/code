import java.util.Scanner;

public class NameString
{
    public static void main(String[] args) 
    {
    	Scanner scan = new Scanner(System.in);
    	
    	//prompt user
    	System.out.print("Please enter your name: ");
    	
        // scan in String   
        String name = scan.nextLine();

        // find location of first blank in name
        int blankLoc1 = name.indexOf(" ");
        
        int blankLoc2 = name.indexOf(" ", blankLoc1 + 1);
        

        // pick off up to, but not including the first blank
        String firstName = name.substring(0, blankLoc1);
        
        //get middle initial
        String middleInitial = name.substring(blankLoc1 + 1, blankLoc2 - 1);
        
        // pick off all after the first blank
        String lastName = name.substring(blankLoc2 + 1);

        // display the results
        System.out.println("name:            " + name);
        System.out.println("firstName:       " + firstName);
        System.out.println("middleInitial:   " + middleInitial);
        System.out.println("lastName:        " + lastName);
    }
} 
