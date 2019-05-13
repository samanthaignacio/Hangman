#include <stdio.h>
#include <stdlib.h>

int main1(void) {
	char* guessed = (char*)malloc(sizeof(char) * 7);
	guessed[0] = '\0';
	printf("%zu\n", sizeof(char));
	printf("%zu\n", strlen(guessed));

	scanf("%s", guessed);

	for(int i = 0; i < 7; i++)
	printf("%c\n", guessed[i]);

	free(guessed);
}