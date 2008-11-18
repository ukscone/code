/*****************************************************
 
	program:	lab7
	
	name:		Jonathan Plona
	email: 		Jonathan.Plona@GMail.com
	
	Description: 	Return the max and average of 
			three numbers.
	
	Date: 		10-24-07

*****************************************************/


#include <stdio.h>

void max_n_avg(int num1, int num2, int num3, double *avg, int *max);

int main(void)
{
	int numone, numtwo, numthree, maximum;
	double average;

	printf("Please enter three integers: ");
	scanf("%d%d%d", &numone, &numtwo, &numthree);

	max_n_avg(numone, numtwo, numthree, &average, &maximum);

	printf("\n\nThe maximum among %d, %d, and %d is %d", numone, numtwo, numthree, maximum); 
	printf("\n\nThe average is %.2f", average);

	return(0);
}


void max_n_avg(int num1, int num2, int num3, double *avg, int *max)
{
	if ((num1 > num2) && (num1 > num3))
		max = num1;
	else if (num2 > num3)
		max = num2;
	else
		max = num3;

	avg = (num1 + num2 + num3)/3.0;
}
