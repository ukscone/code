#include <stdio.h>
#include <stdlib.h>

#define SIZE 50
#define ROWS 17
#define COLS 8

/*global variable to store the number of items in the array*/
int items;

void fillRand(int *nums);
/*fill the array with random numbers*/

void aboveOrBelow(const int *nums);
/*print each element and whether it 
is above or below the average*/

void printReversed(const int *nums);
/*print array in reversed order*/

void sumEven(const int *nums);
/*print the sum of the even elements*/

void sumOdd(const int *nums);
/*print the sum of the odd elements*/

void diffSmallest(int *nums);
/*print each element and how much it
differs from the smallest element*/

void fillEven(int *nums);
/*fill the array with even numbers*/

void search(const int *nums);
/*search the array for a value.
returns the index of the first occurence as an int*/

double randDouble(int seed);
/*takes a seed between 0 and RAND_MAX.
returns a random double between 0 and 1*/

void displayMenu(void);
/*displays the menu*/


int main(void)
{
	int data[50];
	int quit = 0;
	
	while(!quit)
	{
		int choice = 0;
		
		displayMenu();

		printf("\nPlease enter your choice:    ");
		int status = scanf("%d", &choice);

		while(!status)
		{
			while (getchar() != '\n');
			displayMenu();
			printf("\nInvalid choice, please re-enter:\t");
			status = scanf("%d", &choice);
		}

		switch(choice)
		{
			case 1: fillRand(data);
					break;
			case 2: aboveOrBelow(data);
					break;
			case 3: printReversed(data);
					break;
			case 4: sumEven(data);
					break;
			case 5: sumOdd(data);
					break;
			case 6: diffSmallest(data);
					break;
			case 7: fillEven(data);
					break;
			case 8: search(data);
					break;
			default: quit = 1;
					printf("\n\nGoodbye!\n\n");
					break;
		}//switch(choice)
	}//while(!quit)

	return(0);
}//main

//UI functions with user input
void fillRand(int *nums)
{
	int min, max, status, i;
	
	printf("\n\nPlease enter the number of elements to fill:\t");
	status = scanf("%d", &items);
	
	if(items < 1 || items > SIZE)
 	{
		status = 0;			
	}
	
	while(!status)
	{
		displayMenu();
		while(getchar() != '\n');
		printf("\n\nInvalid input, please try again.");
		printf("\n\nPlease enter the number of elements to fill:\t");
		status = scanf("%d", &items);
		
		if(items < 1 || items > SIZE)
 		{
			status = 0;			
		}
	}
	
	printf("\nPlease enter the min and max values:\t");
	status = scanf("%d%d", &min, &max);
	
	if(min > max)
 	{
		status = 0;			
	}
	
	while(!status)
	{
		displayMenu();
		while(getchar() != '\n');
		printf("\n\nInvalid input, please try again.");
		printf("\n\nPlease enter the min and max values:\t");
		status = scanf("%d%d", &min, &max);
		
		if(min > max)
 		{
			status = 0;			
		}
	}

	for(i = 0; i < items; ++i)
	{
		nums[i] = min + randDouble(rand())*(max - min);
	}
	
	char ch;
	printf("\n\nHit [enter] to continue...");
	scanf("%ch", &ch);
}

void search(const int *nums)
{
	int num = 0, index = SIZE, status;
	
	
	printf("\n\nWhat number would you like to search for?\t");
	status = scanf("%d", &num);
	
	while(!status)
	{
		displayMenu();
		while(getchar() != '\n');
		printf("\n\nInvalid input, please try again.");
		printf("\n\nWhat number would you like to search for?\t");
		status = scanf("%d", &num);
	}
	
	int i;
	for(i = 0; i < items; ++i)
	{
		if(nums[i] == num)
		{
			index = i;
			break;
		}
	}
	
	if(index == SIZE) printf("\nThe number was not found");
	else printf("\nThe number was found at index %d", index);
	
	char ch;
	printf("\n\n\nHit [enter] to continue...");
	scanf("%ch", &ch);
}

//UI functions without user input
void displayMenu(void)
{
	fflush(stdout);
	system("clear");
	printf("\t\t\tMENU\n\n");
	printf("1. Fill the array with random numbers\n");
	printf("2. Display above or below average\n");
	printf("3. Print array in reverse order\n");
	printf("4. Calculate the sum of even values in the array\n");
	printf("5. Calculate the sum of elements with odd indices\n");
	printf("6. Display each element and the amount by which it differs from the smallest\n");
	printf("7. Initialize the whole array with even values\n");
	printf("8. Search the array for a value\n");
	printf("9. Quit\n");
}

void sumEven(const int *nums)
{
	int sum = 0;
	int i = 0;
	while(i < items)
	{
		if(nums[i] % 2 == 0) sum += nums[i];
		++i;
	}
	
	printf("\nThe sum of the even values is %d", sum);
	
	char ch;
	printf("\n\n\nHit [enter] to continue...");
	scanf("%ch", &ch);
}

void sumOdd(const int *nums)
{
	int sum = 0;
	int i = 0;
	while(i < items)
	{
		if(i % 2 == 1) sum += nums[i];
		++i;
	}
	
	printf("\nThe sum of the values with odd indices is %d", sum);
	
	char ch;
	printf("\n\n\nHit [enter] to continue...");
	scanf("%ch", &ch);
}

void fillEven(int *nums)
{	
	int i;
	for(i = 0; i < SIZE; ++i)
	{
		nums[i] = (i+1)*2;
	}
	
	items = SIZE;
	
	printf("\nThe array has been filled with even numbers.");
	
	char ch;
	printf("\n\n\nHit [enter] to continue...");
	scanf("%ch", &ch);
}

void printReversed(const int *nums)
{
	printf("\n\n");
	
	int i = items - 1;
	
	while(i >= 0)
	{
		printf("%d ", nums[i]);
		if((items - i) % 20 == 0) printf("\n\n");
		--i;
	}
	
	char ch;
	printf("\n\n\nHit [enter] to continue...");
	scanf("%ch", &ch);
}

void aboveOrBelow(const int *nums)
{
	system("clear");
	int i, repeats, sum = 0;
	double average;
	
	for(i = 0; i < items; ++i)
	{
		sum  += nums[i];
	}
	
	average = sum/(items);
	
	printf("'+' is above average.    '-' is below average.    '0' is equal to average.\n\n");
	
	if(items % COLS == 0) repeats = items/COLS;
	else repeats = items/COLS +1; 
	
	int z;
	for(z = 0; z < repeats; ++z)
	{
		
		for(i = COLS*z; i < COLS*(z + 1) && i < items && i < SIZE; ++i)
		{
			printf("%d\t", nums[i]);
		}
		
		printf("\n");
		
		for(i = COLS*z; i < COLS*(z+1)  && i < items && i < SIZE; ++i)
		{
			if(nums[i] < average) printf("-");
			else if(nums[i] > average) printf("+");
			else printf("0");
			printf("\t");
		}
		
		printf("\n\n");
	}
	
	char ch;
	printf("Hit [enter] to continue...");
	scanf("%ch", &ch);
}

void diffSmallest(int *nums)
{
	int min = nums[0];
	int i;
	
	for(i = 0; i < items; ++i)
	{
		if(nums[i] < min) min = nums[i];
	}
	
	system("clear");
	printf("  Val.\t  Diff.");
	
	for(i = 0; i < ROWS && i < items ; ++i)
	{
		printf("\n   %d\t   %d\t", nums[i], nums[i] - min);
		
		if(i + ROWS < items)
		{
			printf("|   %d\t   %d\t", nums[i +  ROWS], nums[i + ROWS] - min);
		}
		
		if(i + 2*ROWS < items)
		{
			printf("|   %d\t   %d", nums[i +  2*ROWS], nums[i + 2*ROWS] - min);
		}
	}
	
	char ch;
	printf("\n\nHit [enter] to continue...");
	scanf("%ch", &ch);
}

//utility functions
double randDouble(int seed)
{
	return seed * ( 1.0 / ( RAND_MAX + 1.0 ) );
}
