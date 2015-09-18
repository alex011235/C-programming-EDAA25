/* Word-assignment, Alexander Karlsson */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
	int size = 128;
	char* word_array = (char *) malloc(size*sizeof(char));
	char* temp_array = (char *) malloc(size*sizeof(char));

	int temp_count = 0, longest = 0;
	int x;

	while ((x = getchar()) != EOF) {

		if (isalpha(x)) {
			if (temp_count >= size) {
				size *= 2;
				temp_array = (char *) realloc(temp_array,size);
			}
			temp_array[temp_count++] = x;
		}

		if (!isalpha(x)){
			if (temp_count > longest) {
				longest = temp_count;
				word_array = (char *) realloc(word_array,size);
				strncpy(word_array,temp_array,size);
			}
			temp_count = 0;
		}
	}

	printf("%d characters in longest word: %s\n",longest,word_array);
	free(word_array);
	free(temp_array);
	return 0;
}

