import java.util.Scanner;

public class Cents 
{
	public static void main (String args[]) 
	{	
		Scanner scan = new Scanner(System.in);
		System.out.print("Please enter the total number of cents: ");
		
		int totCents = scan.nextInt();
		int dollars = totCents / 100;
		int cents = totCents % 100;
		
		System.out.println("" + totCents + " cents is " + dollars + " dollars and " + cents + " cents.");	
	}
}
