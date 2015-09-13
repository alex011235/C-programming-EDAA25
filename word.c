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
	word_array = (char *) malloc(size*sizeof(char));
	temp_array = (char *) malloc(size*sizeof(char));
}

/* Resize and copy if bigger word is found */
void resize(int len)
{
	size *= 2;
	word_array = (char *) realloc(word_array,size);
	strncpy(word_array,temp_array,size/2);
	temp_array = (char *) realloc(temp_array,size);
	strncpy(temp_array,word_array,size/2);
}

void find_longest_word()
{

	int temp = 0;
	int x;
	word_array[0] = '\0';
	temp_array[0] = '\0';

	while ((x = getchar()) != EOF) {

		if (!isalpha(x)) {
			if (temp > longest) {
				longest = temp;
				resize(temp);
			}
			temp = 0;

		}
		if (isalpha(x)) {
			if (temp == size) {
				resize(temp);
			}
			temp_array[temp++] = x;
		}
	}

	printf("%d characters in longest word: %s\n",longest,word_array);

}

int main(void)
{
	init();
	find_longest_word();
	free(word_array);
	free(temp_array);
	return 0;
}

