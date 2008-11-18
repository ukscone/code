/*****************************************************
 
	program:	Homework 6
	
	name:		Jonathan Plona
	email: 		Jonathan.Plona@GMail.com
	
	Description: 	Mimic an ATM
	
	Date: 		11-1-07

*****************************************************/


#include <stdio.h>

void fifties_twenties_tens(int total, int *fifty, int *twenty, int *ten);
/*Split total into fifties, twenties, and tens*/

void get_data(int *total);
/*Get input from the user*/

int put_data(int fifty, int twenty, int ten);
/*Format and print out data*/

int main(void)
{
	int totalOut, fifties, twenties, tens, another = 1;
	
	/*Loop while user wants another transaction*/
	while(another)
	{
		get_data(&totalOut);
	
		fifties_twenties_tens(totalOut, &fifties, &twenties, &tens);
	
		another = put_data(fifties, twenties, tens);
	}
	
	return 0;
}

void fifties_twenties_tens(int total, int *fifty, int *twenty, int *ten)
{
	*fifty = total / 50;
	*twenty = (total % 50) / 20;
	*ten = ((total % 50) % 20) / 10;
}

void get_data(int *total)
{
	int status = 0;
	
	printf("\n\n\nHow much cash do you need?  $");
	scanf("%d", total);
	
	/*Input must be a multiple of 10*/
	if ((*total % 10) == 0)
	{
		status = 1;
	}
	
	/*Ask until user enters valid input.
	 *If first input is valid, this loop never executes*/
	while(!status)
	{
		while (getchar() != '\n');
		printf("\nInvalid input.");
		printf("\nThis machine dispenses ONLY in multiples of $10.\n\n\n");
		printf("Please enter another value   $");
		scanf("%d", total);
		
		/*Input must be a multiple of 10*/
		if ((*total % 10) == 0)
		{
			status = 1;
		}
		
	}
	
	printf("\n\nThe amount you are withdrawing is: $%d\n\n", *total);
}

int put_data(int fifty, int twenty, int ten)
{
	char another;
	
	printf("\t*** Please take your cash ***\n\n");
	printf("\t%d fifties, %d twenties, and %d tens\n\n", fifty, twenty, ten);
	
	printf("Would you like another transaction(y/n)? ");
	scanf(" %c", &another);
	
	/*Check to see if user desires another transaction*/
	if((another == 'y') || (another == 'Y'))
	{
		return(1);
	}
	else if ((another == 'n') || (another == 'N'))
	{
		printf("\nThank You!");
		return(0);
	}
	else 
	{
		/*If user enters an invalid character, exit*/
		printf("\nAssuming no...");
		printf("\nThank You!");
		return(0);
	}
}
