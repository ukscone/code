import java.util.Scanner;

public class DateTester 
{
	//isLeapYear, daysInMonth, isValid, toString, toString01, dayInWeek, dayName, monthName

	public static void main (String args[]) 
	{		
		Date date = new Date();
		int month, day, year;
		month = 1;
		day = 1;
		year = 1970;
		Scanner scan = new Scanner(System.in);
		
		while(year != 15)
		{
			month = scan.nextInt();
			day = scan.nextInt();
			year = scan.nextInt();
			date.set(year, month, day);
			
			System.out.println(date.isValid());
			System.out.println(date.toString());
			System.out.println(date.toString01());
			System.out.println(date.daysInMonth());
			System.out.println(date.isLeapYear());
			System.out.println(date.dayInWeek());
			System.out.println(date.dayName());
			System.out.println(date.monthName());
		}
	}
}
