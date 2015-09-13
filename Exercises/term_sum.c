/* Exercise 1.2.3, Alexander Karlsson, compile with -o3 for optim. */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define LIMIT 18

void term_sum()
{
	clock_t t0, t1;
	double time;
	
	long double sum = 0.0;	
	unsigned int denom = 1;	

	t0 = clock();

	while (sum < LIMIT) {
		sum += 1.0/denom;
		denom++;
	}
	
	t1 = clock();
	time = (t1 - t0) / (double)CLOCKS_PER_SEC;
	printf("Used %1.3lf s\n", time);
	printf("Terms: %d\n",denom-1);
}

int main(void)
{

	term_sum();
	return 0;
}


