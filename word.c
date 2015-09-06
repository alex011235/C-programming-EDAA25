/* Word-assignment, Alexander Karlsson */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* word_array;
char* temp_array;
int size = 8;
int longest = 0;

void init()
{
	word_array = (char *) calloc(size, sizeof(char));
	temp_array = (char *) calloc(size, sizeof(char));
}

/* Resize if bigger word is found */
void resize()
{
	size *= 2;
	char* temp_arr = calloc(size, sizeof(char));
	strncpy(temp_arr,temp_array,size/2);
	free(temp_array);
	free(word_array);
	word_array = (char *) calloc(size, sizeof(char));
	strncpy(word_array,temp_arr,size/2);
	temp_array = (char *) calloc(size, sizeof(char));
	strncpy(temp_array,temp_arr,size/2);
	free(temp_arr);
}

void find_longest_word()
{
	int temp = 0;
	int x;

	while ((x = getchar()) != EOF) {

		if (x == ' ' || x == '\n') {
			if (temp > longest) {
				longest = temp;
				resize();
			}
			temp = 0;
		}

		if (isalpha(x)) {
			if (temp == size) {
				resize();
			}
			temp_array[temp++] = x;
		}
	}

	printf("%d",longest);
	printf(" characters in longest word: %s\n",word_array);
}

int main(void)
{
	init();
	find_longest_word();
	free(word_array);
	free(temp_array);
	return 0;
}

