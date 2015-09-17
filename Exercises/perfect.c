/* Exercise 1.2.7 Perfect numbers, Alexander Karlsson */
#include <stdio.h>
#include <stdlib.h>

#define LIMIT 10000

/* Prints all perfect numbers below LIMIT */
void perfect_numbers()
{
		int divisor_sum = 0;
		int curr_divisor = 1;
		
		int num;
		for (num = 2; num < LIMIT; num++) {

				while (curr_divisor < num) {

						if (num % curr_divisor == 0)
								divisor_sum += curr_divisor;

						curr_divisor++;
				}	

				if (divisor_sum == num)
						printf("%d\n", num);

				divisor_sum = 0;
				curr_divisor = 1;
		}
}


int main(void)
{
		perfect_numbers();
		return 0;
}