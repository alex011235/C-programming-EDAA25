/* Factorial exercise, Alexander Karlsson */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 10000

typedef struct number 
{
	int size;
	int nbr[MAX_SIZE];
} number;


/* Prints a number, number are stored in the reversed order */
void print_number(number* n) 
{
	int i;
	int lead = 0;
	for (i = n->size; i >= 0; i--) {
		if (n->nbr[i]) {
			lead = 1;
		}
		if (lead) {
			printf("%d",n->nbr[i]);
		}

	}
	printf("\n");
}


/* Multiplies a number with a scalar */
void mult_num(number* n, int num)
{
	int i = 0;
	int size = n->size;
	int carry = 0, m, to_add;	

	for (i = 0; i < size; i++) 
	{
		m = n->nbr[i] * num + carry;
		to_add = m % 10;
		carry = (m - to_add) / 10;	
		n->nbr[i] = to_add;
	}

	while (carry)
	{
		n->nbr[n->size++] = carry % 10;
		carry = carry / 10;
	}
} 


/* Facatorial n! */
void factorial(int n)
{
	number* nbr = malloc(MAX_SIZE*sizeof(int));
	nbr->size = 1;
	nbr->nbr[0] = 1;
	
	int num = 2;

	while ((num <= n)) 
	{
		mult_num(nbr,num++);
	}
	
	print_number(nbr);

	free(nbr);
}


int main(void) 
{	
	int n;
    scanf("%d", &n);
	printf("%d! = \n",n);

	factorial(n);

	return 0;
}
