import java.util.Scanner;
import java.lang.Math.*;
import java.text.DecimalFormat;

public class Project2 
{

	public static void main (String args[]) 
	{		
		final double pi = Math.PI;
		double radius, circumference, area;
		
		DecimalFormat fmt = new DecimalFormat("0.###");
		Scanner scan = new Scanner(System.in);
		
		//prompt user and read in value of radius
		System.out.print("Please enter the value of the radius: ");
		radius = scan.nextDouble();
		
		//compute circumference and area
		circumference = 2 * radius * pi;
		area = pi * radius * radius;
		
		//print out values
		System.out.println("\nRadius: \t" + fmt.format(radius));
		System.out.println("Circumference: \t" + fmt.format(circumference));
		System.out.println("Area: \t\t" + fmt.format(area));
	}
}
