import java.util.Scanner;

public class Project1
{
	public static void main(String[] args)
	{
		int total, hours, minutes, seconds;
		Scanner scan = new Scanner(System.in);
		
		//Prompt user and read in total number of seconds
		System.out.print("Please enter an integer number of seconds: ");
		total = scan.nextInt();
		
		hours = total / 3600;
		minutes = (total % 3600) / 60;
		seconds = (total % 3600) % 60;
		
		System.out.println(hours + " hours " + minutes + " minutes and " + seconds + " seconds");
	}
}
