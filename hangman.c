#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>    
#include<string.h>
#include<stdlib.h>

void draw(int);
void showGuesses(char*, int);
void append(char*, char, int);
void printTitle();

int main(void)
{
	char wordToGuess[30];     //word to be guessed
	char compare[30];         //array to be compared to determine if win
	char displayWord[30];     //display of the word (_ for unguessed letters)
	char *guessedLetters;     //incorrect letters guessed
	const int MAX_LINES = 851;

	int guessedIndex = 0;
	int chancesLeft = 6;      //chances left to guess before losing
	int guess = 0;
	int index = 0;
	int position = 0;
	int ifWin;
	int length;
	int i;

	FILE *fPtr;

	char inputLetter;

	srand(time(NULL));
	system("cls");

	printTitle();

	printf("Press Enter to begin\n");

	getchar();

	// Read words.txt
	if ((fPtr = fopen("words.txt", "r")) == NULL) {
		puts("File could not be opened");
		return -1;
	}

	// Randomly pick a word from the list
	int line = rand() % MAX_LINES;
	for (int i = 0; i < line; i++) {
		fscanf(fPtr, "%s", &wordToGuess);
	}
	fclose(fPtr);

	length = strlen(wordToGuess);
	guessedLetters = (char *)malloc(sizeof(char) * 7);

	system("cls");

	printTitle();
	printf("\n\tEnter your guess.\n");
	draw(chancesLeft);

	printf("\n\n\t");
	for (i = 0; i < length; i++)
	{
		displayWord[i] = '_';
		displayWord[length] = '\0';
	}

	for (i = 0; i < length; i++)
	{
		printf(" ");
		printf("%c", displayWord[i]);

	}
	while (chancesLeft != 0)
	{
		guess = 0;
		printf("\n\nEnter your guess (one lowercase letter): ");
		fflush(stdin);

		scanf("%c", &inputLetter);
		if (inputLetter < 'a' || inputLetter > 'z')
		{
			system("cls");
			printTitle();
			printf("\n\tInvalid input. Enter a valid character.\n");
			draw(chancesLeft);
			guess = 2;  //guess is 2 when input is wrong
		}
		fflush(stdin);  //clears the buffer for the next input

		if (guess != 2)  //when guess is valid input, guess is 0 or 1
		{
			for (index = 0; index < length; index++) {  //checks if letter is in the word
				if (inputLetter == wordToGuess[index]) {
					guess = 1;  //guess is 1 when correct letter is guessed
				}
			}
			if (guess == 0) //guess remains 0 if guess is incorrect
			{
				append(guessedLetters, inputLetter, guessedIndex++); //add incorrect guess to guessedLetters array
				system("cls");
				printTitle();
				printf("\n\tIncorrect guess. Tries remaining: %d\n", --chancesLeft);
				draw(chancesLeft);
			}
			else  //when guess is correct
			{
				system("cls");
				printTitle();
				printf("\n\tCorrect!\n");
				draw(chancesLeft);
				for (index = 0; index < length; index++)
				{
					guess = 0; //set guess back to 0, then set to 1 if there is a match in the word
					if (inputLetter == wordToGuess[index])
					{
						position = index;
						guess = 1;
					}

					if (guess == 1)
					{
						for (i = 0; i < length; i++)
						{
							if (i == position)
							{
								displayWord[i] = inputLetter; //sets the correct letter in displayWord
							}
							else if (displayWord[i] >= 'a' && displayWord[i] <= 'z')
							{
								continue;
							}
							else
							{
								displayWord[i] = '_'; //places a blank for letters not guessed correctly
							}
						}

						compare[position] = inputLetter; //used to compare with wordToGuess
						compare[length] = '\0';
						ifWin = strcmp(compare, wordToGuess); //will return 0 if word matches

						if (ifWin == 0)
						{
							free(guessedLetters);
							system("cls");
							printTitle();
							draw(chancesLeft);
							printf("\n\n\t");
							for (i = 0; i < length; i++)
							{
								printf(" ");
								printf("%c", displayWord[i]);
							}
							printf("\n");

							printf("\n=====================\n");
							printf("   G A M E O V E R\n");
							printf("=====================\n");
							printf("\nYOU WON!");
							printf("\nYou guessed the word '%s' correctly!\n\n", wordToGuess);
							return 0;
						}
					}
				}
			}
		}
		printf("\n\n\t");
		for (i = 0; i < length; i++)
		{
			printf(" ");
			printf("%c", displayWord[i]);
		}
		printf("\n");
		if (guessedLetters[0] != '\0')
		{
			showGuesses(guessedLetters, guessedIndex);
		}
		getchar();
	}

	if (chancesLeft <= 0)
	{
		free(guessedLetters);
		printf("\n=====================\n");
		printf("   G A M E O V E R\n");
		printf("=====================\n");
		printf("\nYOU LOST!");
		printf("\nThe word was '%s'.\n\n", wordToGuess);
		return 0;
	}
}

void showGuesses(char* guessedLetters, int guessedIndex)
{
	printf("\nYour incorrect guesses: ");
	for (int n = 0; n < guessedIndex; n++)
	{
		printf("%c ", guessedLetters[n]);
	}
}

void append(char* s, char c, int guessedIndex)
{
	s[guessedIndex] = c;
	s[guessedIndex + 1] = '\0';
}

void draw(int numAttemptLeft)
{
	switch (numAttemptLeft)
	{
	case 0:
		printf("\n\t|----- ");
		printf("\n\t|    | ");
		printf("\n\t|   %cO/", '\\');
		printf("\n\t|    | ");
		printf("\n\t|   / %c", '\\');
		//printf("\n\t|      ");
		printf("\n      -----");
		break;

	case 1:
		printf("\n\t|----- ");
		printf("\n\t|    | ");
		printf("\n\t|   %cO/", '\\');
		printf("\n\t|    | ");
		printf("\n\t|     %c", '\\');
		//printf("\n\t|      ");
		printf("\n      -----");
		break;

	case 2:
		printf("\n\t|----- ");
		printf("\n\t|    | ");
		printf("\n\t|   %cO/", '\\');
		printf("\n\t|    | ");
		printf("\n\t|      ");
		//printf("\n\t|      ");
		printf("\n      -----");
		break;

	case 3:
		printf("\n\t|----- ");
		printf("\n\t|    | ");
		printf("\n\t|   %cO/", '\\');
		printf("\n\t|      ");
		printf("\n\t|      ");
		//printf("\n\t|      ");
		printf("\n      -----");
		break;

	case 4:
		printf("\n\t|----- ");
		printf("\n\t|    | ");
		printf("\n\t|   %cO ", '\\');
		printf("\n\t|      ");
		printf("\n\t|      ");
		//printf("\n\t|      ");
		printf("\n      -----");
		break;

	case 5:
		printf("\n\t|----- ");
		printf("\n\t|    | ");
		printf("\n\t|    O ");
		printf("\n\t|      ");
		printf("\n\t|      ");
		//printf("\n\t|      ");
		printf("\n      -----");
		break;

	case 6:
		printf("\n\t|----- ");
		printf("\n\t|    | ");
		printf("\n\t|      ");
		printf("\n\t|      ");
		printf("\n\t|      ");
		//printf("\n\t|      ");
		printf("\n      -----");
	}
	return;
}

void printTitle() {
	printf("\n===================\n");
	printf("   H A N G M A N \n");
	printf("===================\n");
}
