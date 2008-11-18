/*****************************************************
 
	program:	Homework 5
	
	name:		Jonathan Plona
	email: 		Jonathan.Plona@GMail.com
	
	Description: 	Read in a list of numbers and
			output whether or not they
			are perfect.

	Date: 		10-24-07

*****************************************************/



#include <stdio.h>

int sumOfDivisors(int num);
/*Return the sum of an integer's divisors*/

int main(void)
{
   FILE *inp, *outp;
   int numIn, status;

   /*Open files*/
   inp = fopen("perfect.dat", "r");
   outp = fopen("perfect.out", "w");

   status = fscanf(inp, "%d", &numIn);
   
   /*While there are no errors, output results to output file*/
   while(status == 1)
   {
     if (numIn == sumOfDivisors(numIn))
       fprintf(outp, "%d is a perfect number\n", numIn);
     else
       fprintf(outp, "%d is not a perfect number\n", numIn);
     status = fscanf(inp, "%d", &numIn);
   }

   if (status != EOF)
     printf("There was an error in the input.  \n\nExiting.");

   /*Close files*/
   fclose(inp);
   fclose(outp);

   return(0);
}

int sumOfDivisors(int num)
{
   int temp = 0;

   /*Loop through all integers and add the perfect divisors*/
   int x;
   for (x = 1; x <= num/2.0; ++x)
   {
     if (num % x == 0)
       temp += x;
   }
   
   return(temp);
}
