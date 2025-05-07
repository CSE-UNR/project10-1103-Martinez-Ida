//Author: Ida Martinez
//Date: 4/27/2025
//Purpose: Project 10/Final Project

#include <stdio.h>
#define FILE_NAME "mystery.txt"
#define NUM_CHARS 5
#define MAX_GUESSES 6

//functions (at least 6)
char lower(char letter);
char upper(char letter);
int checkLetter(char letter);
int getGuess(char guess[]);
int compareWords(char guess[], char mystery[]);
void showGuesses(char allGuesses[][NUM_CHARS], int numGuesses, char mystery[]);
int loadWord(char mystery[]);

//convert letters to lowercase
char lower(char letter){
	if(letter >= 'A' && letter <= 'Z') return letter + 32;
	return letter;
}

//convert letters to uppercase
char upper(char letter){
	if(letter >= 'a' && letter <= 'z') return letter - 32;
	return letter;
}

//check if guess contains only letters and no other characters
int checkLetter(char letter){
	return(letter >= 'a' && letter <= 'z' || (letter >= 'A' && letter <= 'Z'));
}

//get mystery word from file
int loadWord(char mystery[]){
FILE *fptr = fopen("mystery.txt", "r");
if(fptr == NULL){
	printf("Can't open file.\n");
	return 0;
}

char array[100];
if(fgets(array, sizeof(array), fptr) != NULL){

	int i = 0;
	while(array[i] != '\n' && array[i] != '\0') i++;
	array[i] = '\0';
	
	int length = 0;
	for(i = 0; array[i] != '\0'; i++){
		if(checkLetter(array[i]) == 0){
			printf("*** stack smashing detected ***: terminated\n Aborted\n");
			fclose(fptr);
			return 0;
		}
		length++;
	}
	
	if(length != NUM_CHARS){
		printf("*** stack smashing detected ***: terminated\n Aborted\n");
		fclose(fptr);
		return 0;
	}
	
	for(i = 0; i < NUM_CHARS; i++){
		mystery[i] = lower(array[i]);
	}
	fclose(fptr);
	return 1;
}

printf("Can't open file.\n");
fclose(fptr);
return 0;
}

//get guess from user and check if guess is valid
int getGuess(char guess[]){
char array[100];
int length = 0;

fgets(array, sizeof(array), stdin);

for(int i = 0; i < NUM_CHARS; i++){
	if(array[i] == '\n' || array[i] == '\0') break;
	guess[i] = array[i];
	length++;
}

int nonLetter = 0;
for(int i = 0; i < length; i++){
	if(checkLetter(guess[i]) == 0){
	nonLetter = 1;
	break;
	}
}

if(length != NUM_CHARS || nonLetter){
	if(length != NUM_CHARS){
		printf("Your guess must be 5 letters long.");
	} else if(nonLetter){
		printf("Your guess must contain only letters.");
	}
	return 0;
}
return 1;
}

//give user feedback on their guess
int compareWords(char guess[], char mystery[]){

for(int i = 0; i < NUM_CHARS; i++){
	if(lower(guess[i]) != mystery[i]) return 0;
}
return 1;
}

void showGuesses(char allGuesses[][NUM_CHARS], int numGuesses, char mystery[]){

for(int j = 0; j < numGuesses; j++){
	char lowerGuess[NUM_CHARS];
	for(int i = 0; i < NUM_CHARS; i++){
		lowerGuess[i] = lower(allGuesses[j][i]);
		}
	
for(int i = 0; i < NUM_CHARS; i++){
	if(lowerGuess[i] == mystery[i]){
		printf("%c", upper(allGuesses[j][i]));
	} else {
		printf("%c", lower(allGuesses[j][i]));
	}
}
printf("\n");

for(int i = 0; i < NUM_CHARS; i++){
	if(lowerGuess[i] != mystery[i]){
		int found = 0;
		for(int j = 0; j < NUM_CHARS; j++){
			if(lowerGuess[i] == mystery[j] && lowerGuess[j] != mystery[j]){
				found = 1;
				break;
			}
		}
		if(found) printf("^");
		else printf(" ");
		} else {
			printf(" ");
		}
}
printf("\n");
}
}

int main(){

char mystery[NUM_CHARS];
char guesses[MAX_GUESSES][NUM_CHARS];
int attempts = 0;

if(loadWord(mystery) == 0){
return 1;
}

while(attempts < MAX_GUESSES){
	if(attempts == MAX_GUESSES - 1){
		printf("FINAL GUESS! Enter your guess:");
	} else {
		printf("GUESS %d! Enter your guess: ", attempts + 1);
	}
	
	while(1){
	if(getGuess(guesses[attempts]) == 0){
		printf("\nPlease try again: ");
	} else {
		break;
	}
	}

	attempts++;
	
	printf("================================\n");
	
	if(compareWords(guesses[attempts - 1], mystery)){
		printf("                ");
		for(int i = 0; i < NUM_CHARS; i++){
			printf("%c", upper(mystery[i]));
		}
		printf("\n");
		
		if(attempts == 1){
			printf("	You won in 1 guess!\n		GOATED!\n");
		} else if (attempts == 2 || attempts == 3){
			printf("	You won in %d guesses!\n		Amazing!\n", attempts);
		} else if (attempts == 4 || attempts == 5){
			printf("	You won in %d guesses!\n		Nice!\n", attempts);
		} else if (attempts == 6){
			printf("	You won in 6 guesses!\n");
		}
		return 0;
	}
	showGuesses(guesses, attempts, mystery);
}

printf("You lost, better luck next time!\n");
return 0;
}

