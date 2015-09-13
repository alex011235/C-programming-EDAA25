/* Exercise 1.2.4, find the hexadecimal digit sum */
#include <stdio.h>

// A == 10, B 11, C 12, D 13, E 14, F 15

void hex_digit_sum(unsigned int number)
{
	unsigned int sum = 0;
	
	while (number) {
		sum += number & 0xf;
		number = number >> 4; // divide by 16
	}

	printf("%d\n",sum);
}

int main(void)
{
	hex_digit_sum(11256099); //39
	return 0;
}

