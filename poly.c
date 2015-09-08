/* Poly-assignment, Alexander Karlsson*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "error.h"
#include "poly.h"

#define MAX_SIZE 50

int length = 0;

struct poly_t {
	int coeff[MAX_SIZE];
	int expo[MAX_SIZE];
};

/* Creates a polynomial from a string */
poly_t* new_poly_from_string(const char* xx) 
{
	int x, sign = 1, y = ' ', nbr = 0, pos  = 0;
	const char* xx2 = xx;

	poly_t* poly = malloc(2*MAX_SIZE*sizeof(int));

	while ((x = *xx++)) {

		if (isdigit(x)) {
			nbr = nbr*10 + x - '0';
		}

		switch (x) {
			case 'x':
				if (!nbr) {
					poly->coeff[pos++] = sign;
				} else {
					poly->coeff[pos++] = sign*nbr;
				}
				nbr = 0;
				break;

			case '-': // Change sign
				sign = -1;
				break;

			case '+':
				sign = 1;
				break;

			case ' ':
				nbr = 0;
				break;
		}
	}

	if (nbr) {
		poly->coeff[pos++] = sign*nbr;
	}
	
	// force last item to zero
	poly->coeff[pos] = 0;

	nbr = 0;
	int pos2 = 0;	
	bool exp = false, one_exp = false;

	while ((x = *xx2++)) {

		if (x == '^') {
			exp = true;
			one_exp = false;
		} 

		if (x == ' ') {
			exp = false;
			one_exp = false;
		}

		if (y == 'x') {
			one_exp = true;
		}

		if (exp) {
			if (isdigit(x)) {
				nbr = nbr*10 + x - '0';
			}

		} else if (nbr) {
			poly->expo[pos2++] = nbr;
			nbr = 0;

		} else if (one_exp) {
			poly->expo[pos2++] = 1;
			one_exp = false;
			nbr = 0;
		} 

		y = x; // save last char
	}

	if (!exp && !one_exp) {
		poly->expo[pos2] = 0;
	}

	length = pos;
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
	int length1 = get_length(poly1), length2 = get_length(poly2);
	int i, j, coffi, coffj, coffk, expi, expj, expk, posk = 0;

	poly_t* polyk = malloc(2*MAX_SIZE*sizeof(int));

	/* O(n^2) polynomial multiplication */
	for (i = 0; i < length1; ++i) {
		coffi = poly1->coeff[i];
		expi = poly1->expo[i];

		for (j = 0; j < length2; ++j) {
			coffj = poly2->coeff[j];
			expj = poly2->expo[j];

			coffk = coffi * coffj;
			expk = expi + expj;

			polyk->coeff[posk] = coffk;
			polyk->expo[posk++] = expk;
		}
	}

	int length3 = get_length(polyk);

	poly_t* poly_ans = malloc(2*MAX_SIZE*sizeof(int));

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
	int len = get_length(poly);	
	int i = 0, coeff = 1, expo;
	for (i = 0; i < len; i++) {
		coeff = poly->coeff[i];
		expo = poly->expo[i];

		if (coeff < 0) {
			printf(" - %d",-1*coeff);

		} 
		if (coeff > 0 && i > 0) {
			printf(" + %d",coeff);

		}

		if (coeff > 0 && i == 0) {
			if (coeff != 1) {
				printf("%d",coeff);
			}
		}

		if (expo != 0) {
			if (expo == 1) {
				printf("x");
			} else {
				printf("x^%d",expo);
			}
		}
	}
	printf("\n");
}

