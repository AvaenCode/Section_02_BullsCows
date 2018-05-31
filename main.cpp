/**
*						--- BULLS & COWS GAME SOURCE CODE ---
*
* Udemy Online Course - Unreal Engine Tutorial
* Section 2, Lecture 18, 19, 20, 21, ... + - C++ Code - Cows & Bulls
* Code w/ comments explaining each method/function
*/

// Preprocessor directives & Libraries
#include <iostream>
#include <string>
#include "FBullsCowsGame.h"

// Namespaces - disadvatange: if 2 libraries have the same namespace causing clashing.
// Using the namespace directive to adhere more to the Unreal standard. I.e: std::string is replaced with FText in main.cpp.
using FText = std::string;
using int32 = int;

// Declared prototype functions for usability in main function - actual functions are after the main function
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

/** 
* Create new instances from objects. The constructor method is called at this point. 
* When the objected is constructed the values are known. In this case the constructor calls the Reset(); method.
*/
FBullsCowsGame BCGame;

// Main function
int main() {
	do {
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain() == true); // Invokes the method and ensures it's true to loop
	return 0;
}


// Print introduction routine
void PrintIntro() {
	
	// Print introduction for game & clear screen upon reseting the game.
	system("cls");
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
}

void PlayGame() {

	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// Print placement so that the GetHiddenWordLength() is correctly loaded to display the right answer.
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl;
	std::cout << std::endl;

	// Loop asking for guess while the game is NOT 'won', and there are still tries remaining.
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries){
		FText Guess = GetValidGuess(); // invokes GetGuess(); method
		
		// Capture counts into a variable, and submit valid guess to the game.
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// Print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " | Cows = " << BullCowCount.Cows << std::endl;
		std::cout << std::endl;
	}
	PrintGameSummary();
}

// Loop continullay until the user gives a valid guess.
FText GetValidGuess() {

	FText Guess = "";

	// Declaring and initializing our enumeration to an invalid status so that it can have a bigger scope and work correctly in our do-while loop.
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	
	do {
		// Get guess from player - Uses getline('getting it from', 'putting it to') method to take user input.
		int32 CurrentTry = BCGame.GetCurrentTry();
		
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: " << std::endl;
		std::getline(std::cin, Guess);

		// Capture the status from the CheckGuessValidity function into a variable
		Status = BCGame.CheckGuessValidity(Guess);

		// Switch statement to enforce the enumeration error checking. Remember, each enum value returns an integer.
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. " << std::endl;
			std::cout << std::endl;
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters. " << std::endl;
			std::cout << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters. " << std::endl;
			std::cout << std::endl;
			break;
		default:
			// Assumes the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // Keep looping until we get no errors.
	return Guess;
}

bool AskToPlayAgain() {

	std::cout << "Do you want to play again with a different isogram (y/n)?" << std::endl;
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	std::cout << std::endl;
	// Get the first character of response with: Response[0]
	// If this is true, Response[0] will return a 1 for true
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "GAME OVER - You win!" << std::endl;
		std::cout << std::endl;
	}
	else {
		std::cout << "GAME OVER - Out of tries, you lost!" << std::endl;
		std::cout << "The hidden isogram was - " << BCGame.GetHiddenWord() << ". " << std::endl;
		std::cout << std::endl;
	}
}
