/*****************************************************
 
	program:		Lab9
	
	name:			Jonathan Plona
	email: 			Jonathan.Plona@GMail.com
	
	Description: 	Practice with Arrays
	
	Date: 			11-4-2007

*****************************************************/


#include <stdio.h>
#define SIZE 10

void fill_Array(double *nums);
/* prompts the user to enter 10 double values.
   takes a double pointer */

void print_Table(double *nums);
/* calculates percent of total, formats output, and prints it to the screen.
   takes a double pointer */


int main(void)
{
	double N[SIZE];
	
	fill_Array(N);
	
	print_Table(N);	
	
	return 0;
}

void fill_Array(double *nums)
{
	int status;
	int i = 0;
	
	/* get data from user */
	do
	{
		printf("Please enter a double: ");
		status = scanf("%lf", &nums[i]);
		
		++i;
	} while(status && i < SIZE);
	
	if(!status)
	{
		printf("Warning:  Input Failed.\n");
	}
}

void print_Table(double *nums)
{
	double sum = 0;
	int i;

	/* sum up data */	
	for(i = 0; i < SIZE; ++i)
	{
		sum += nums[i];
	}
	
	printf("\nN\t\tpct. of total\n--------------------------\n");
	
	/*print out data*/
	for(i = 0; i < SIZE; ++i)
	{
		double percent = nums[i]/sum * 100;
		
		printf("%.1f\t\t%.2f\n", nums[i], percent);
	}
}
