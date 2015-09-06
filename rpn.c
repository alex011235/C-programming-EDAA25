/* RPN-calculator by ALEXANDER KARLSSON */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Stack --------------------------------

#define MAX_SIZE 10

int stack[MAX_SIZE];
int pos;

void init() {
	pos = 0;
}

void push(int num)
{
stack[pos++] = num;
}

int peek()
{
	return stack[pos-1];
}

int pop() {
	return stack[--pos];
}

int size()
{
	return pos;
}

// -------------------------------------

void rpn_calculator()
{
	int num = 0, x = 0, prev_num = 0;
	char y = ' ';
	int line_count = 0;

	init();

	while ((x = getchar()) != EOF) {

		if (isdigit(x)) {
			num = num*10 + x - '0';

		} else {

			if (num || (isdigit(y) && num == 0)) {
				push(num);
				prev_num = num; // Save previous number
				num = 0;
			}

			if (size() > MAX_SIZE) {
				while ( getchar() != '\n' ); // flush input
				init();
				printf("line %d: error at %d\n",++line_count,prev_num);
			} else {

			int a = 0;
			int p = peek();
			int s = size();

			switch (x) {

				case '+':
					push(pop()+pop());
					break;

				case '-':
					a = pop();
					push(pop() - a);
					break;

				case '*':
					push(pop()*pop());
					break;

				case '/':
					if (peek() == 0) {
						printf("line %d: error at /\n",++line_count);
						init();

					} else {
						a = pop();
						push(pop() / a);
					}
					break;

				case '\n':
					/* Mostly error finding here */

					/* No operator */
					if (isdigit(y)) {
						printf("line %d: error at \\n\n",++line_count);
						init();
						break;
					}

					/* Single operand and operator */
					else if (p && s < 1 && (y == '+' || y == '-' || y == '*' || y == '/')) {
						printf("line %d: error at %c\n",++line_count,y);
						init();
						break;

					}
					else if (y == x) { /* Empty line case */
						printf("line %d: error at \\n\n",++line_count);
						y = ' ';
						init();
						break;
					}

					/* Pop result from stack */
					else if (size() > 0) {
						printf("line %d: %d\n",++line_count,pop());
						init();
						break;
					}

					init();
					break;

				default:
					/* Illegal char */
					if (x != ' ') {
						printf("line %d: error at %c\n",++line_count,x);
						init();
					}
					break;
				}
			}
		}
		y = x; //save previous char
	}
}

int main(void)
{
	rpn_calculator();
	return 0;
}

