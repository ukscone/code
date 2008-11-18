/********************************************************************

	program name: Utility Bill Homework 2

	date: 9-14-07

	author: Jonathan Plona

	description: Compute Utility bill given no. of kW/hr

********************************************************************/


#include <stdio.h>

#define TAX_RATE .03
#define DISCOUNT .1
#define COST .16

int main(void)
{
	char char1, char2, char3;
	double hours, subtotal;

	printf("\nEnter the first three letters of the month: ");
	scanf("%c%c%c", &char1, &char2, &char3);
	printf("\nEnter the number of kW/hrs: ");
	scanf("%lf", &hours);

	subtotal = hours*COST;

	printf("\n\n********   Athens Utility Company   ********\n");
	printf("********  Bill for the month of %c%c%c ********\n\n", char1, char2, char3);
	printf("Number of kW/hrs used\t\t\t%.2f\n\n", hours);
	printf("Tax Rate\t\t\t\t%.2f\n\n", TAX_RATE);
	printf("Discount Rate\t\t\t\t%.2f\n\n", DISCOUNT);
	printf("Cost per kW/hr\t\t\t\t$%.2f\n\n", COST);
	printf("Subtotal\t\t\t\t$%.2f\n\n", subtotal);
	printf("Tax\t\t\t\t\t$%.2f\n\n", TAX_RATE*subtotal);
	printf("Discount\t\t\t\t$%.2f\n", DISCOUNT*subtotal);
	printf("\t\t\t\t\t________\n");
	printf("Final Bill\t\t\t\t$%.2f\n\n\n\n", subtotal*(1.0-DISCOUNT)*(1.0+TAX_RATE));

	return(0);
}
