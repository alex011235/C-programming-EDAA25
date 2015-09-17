/* Poly-assignment, Alexander Karlsson*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "error.h"
#include "poly.h"

#define MAX_SIZE 25

struct poly_t {
	int coeff[MAX_SIZE];
	int expo[MAX_SIZE];
};

/* Creates a polynomial from a string */
poly_t* new_poly_from_string(const char* xx)
{
	int x; 			// for storing read chars
	int sign = 1; 	// for indicating pos/negative values
	int y = ' '; 	// for saving an old char
	int nbr = 0; 	// for storing numbers
	int pos  = 0;
	int index = 0;	// for indexing the inpyt char*

	poly_t* poly = malloc(2*MAX_SIZE*sizeof(int));


	while ((x = xx[index++])) {

		if (isdigit(x))
			nbr = nbr*10 + x - '0';

		switch (x) {
			case 'x':
				if (!nbr)
					poly->coeff[pos++] = sign;
				else
					poly->coeff[pos++] = sign*nbr;

				nbr = 0;
				sign = 1;
				break;

			case '-': // Change sign
				sign = -1;
				break;

			case ' ':
				nbr = 0;
				break;
		}
	}

	if (nbr)
		poly->coeff[pos++] = sign*nbr;

	poly->coeff[pos] = 0;

	index = 0;
	int exp_value = 0; 			// for storing the exponent value
	int exp_position = 0; 		// used for indexing exp-array
	int exp = 0; 				// indicating if exponent exists
	int one_exp = 0; 			// used for x^0 = 1

	while ((x = xx[index++])) {

		if (x == '^') {
			exp = 1;
			one_exp = 0;
		} 

		if (x == ' ') {
			exp = 0;
			one_exp = 0;
		}

		if (y == 'x')
			one_exp = 1;

		if (exp) {
			if (isdigit(x))
				exp_value = exp_value*10 + x - '0';

		} else if (exp_value) {
			poly->expo[exp_position++] = exp_value;
			exp_value = 0;

		} else if (one_exp) {
			poly->expo[exp_position++] = 1;
			one_exp = 0;
			exp_value = 0;
		} 

		y = x; // save last char
	}

	if (!exp && !one_exp)
		poly->expo[exp_position] = 0;

	return poly;
}

void free_poly(poly_t* poly)
{
	free(poly);
}

/* Returns the length of a polynomial (nbr of coefficients) */
int get_length(poly_t* poly)
{
	int i = 0;
	while(poly->coeff[i++] != 0);
	return i-1;
}

/* Multiplies two polinomial */
poly_t*	mul(poly_t* poly1, poly_t* poly2)
{
	int length1 = get_length(poly1);
	int length2 = get_length(poly2);

	int i, j, coffi, expi, posk = 0;

	poly_t* polyk = malloc(2*MAX_SIZE*sizeof(int));

	/* O(n^2) polynomial multiplication */
	for (i = 0; i < length1; ++i) {
		coffi = poly1->coeff[i];
		expi = poly1->expo[i];

		for (j = 0; j < length2; ++j) {
			polyk->coeff[posk] = coffi * poly2->coeff[j];
			polyk->expo[posk++] = expi + poly2->expo[j];
		}
	}

	int length3 = get_length(polyk);

	poly_t* poly_ans = malloc(2*MAX_SIZE*sizeof(int));

	// Position and value of current exponent
	int found_pos = 0, exp_max = 1;

	/* Sorting the exponents, largest first */
	for (i = 0; i < length3; ++i) {
		for (j = 0; j < length3; ++j) {

			int curr = polyk->expo[j];

			if (curr > exp_max) {
				exp_max = polyk->expo[j];
				found_pos = j;
			}
		}

		poly_ans->expo[i] = polyk->expo[found_pos];
		poly_ans->coeff[i] = polyk->coeff[found_pos];

		polyk->expo[found_pos] = 0; 
		polyk->coeff[found_pos] = 0;

		/* Finding the parts with the same degree */
		for (j = 0; j < length3; j++) {

			int curr2 = polyk->expo[j];

			if (curr2 == exp_max) {
				poly_ans->coeff[i] += polyk->coeff[j];
				polyk->expo[j] = 0; 
				polyk->coeff[j] = 0;

			}
		}

		exp_max = 0;
		found_pos = 0;
	}

	free(polyk);

	return poly_ans;
}

/* Prints the polynomial */
void print_poly(poly_t* poly) 
{
	int length = get_length(poly);
	int coeff = 1, expo;
	
	int i;
	for (i = 0; i < length; i++) {
		coeff = poly->coeff[i];
		expo = poly->expo[i];

		if (coeff < 0)
			printf(" - %d",-1*coeff);
 
		if (coeff > 0 && i > 0)
			printf(" + %d",coeff);

		if (coeff > 0 && i == 0)
			if (coeff != 1)
				printf("%d",coeff);

		if (expo != 0) {
			if (expo == 1)
				printf("x");
			else
				printf("x^%d",expo);
		}
	}
	printf("\n");
}

