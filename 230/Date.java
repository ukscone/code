public class Date 
{
	private int year, month, day;
	
	public Date()
	{
		set(1970, 1, 1);
	}
	
	public Date(int y, int m, int d)
	{
		set(y, m, d);
	}
	
	public static boolean isLeapYear(int y)
	{
		//leap year logic
		if ( y % 400 == 0 ) return true;
    	if ( y % 100 == 0 ) return false;
 	    if ( y %   4 == 0 ) return true;
    						return false;
	}
	
	public static int daysInMonth(int y, int m)
	{
		//Array containing number of days in each month, in order
		int[] days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		
		//leap year logic
		if (m == 2 && isLeapYear(y))
		{
			return 29;
		}
		else
		{
			return days[m - 1];
		}
	}
	
	public static boolean isValid(int y, int m, int d)
	{
		//no negative or zero values
		if (y < 0 || m <= 0 || d <= 0) return false;
		//no months greater than 13
		if (m > 12) 				return false;
		//no days past the end of the month
		if (d > daysInMonth(y, m)) return false;
									return true;
	}
	
	public void set(int y, int m, int d)
	{
		//check for validity, if invalid leave date as is
		if(Date.isValid(y, m, d)
		{
			year = y;
			month = m;
			day = d;
		}
		else
		{
			System.out.println("Warning, invalid date entered.  Reverting to previous date...");
		}
	}
	
	public boolean isLeapYear()
	{
		return isLeapYear(year);
	}

	public int daysInMonth()
	{
		return daysInMonth(year, month);
	}

	public boolean isValid()
	{
		return isValid(year, month, day);
	}
	
	public String toString01()
	{
		//11/4/2007
		return "" + month + "/" + day + "/" + year;
	}
	
	public String toString()
	{
		//Sunday, November 4, 2007
		return dayName() + ", " + monthName() + " " + day + ", " + year;
	}
	
	public int dayInWeek()
	{
		//Formula from http://mathforum.org/dr.math/faq/faq.calendar.html
		//Modified to avoid a negative number
		
		int sum, mo, yr;
		
		//This formula starts the year in march, so adjust the month and year
		mo = month - 2;
		yr = year;
		
		//End case January and February
		if (mo < 1)
		{
			mo += 12;
			yr--;
		}
		
		int D = yr % 100;
		int C = yr / 100;
		
		sum = day + ((13*mo - 1)/5) + D + D/4 + C/4 + 5*C;
		
		return sum % 7;
	}
	
	public String dayName()
	{
		String[] day = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
		return day[dayInWeek()];
	}
	
	public String monthName()
	{
		String[] name = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
		return name[month - 1];
	}
	
	
	
}
