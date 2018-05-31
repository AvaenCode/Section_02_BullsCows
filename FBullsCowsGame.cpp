#pragma once
#include "FBullsCowsGame.h"
#include <map>
#include <fstream>
#define TMap std::map // this is just to adhere to the Unreal standard.

// Default constructor.
FBullsCowsGame::FBullsCowsGame() { Reset(); } 

// Keyword 'const' only works on member/class functions.
// The following one line methods are all 'getter methods'.
int32 FBullsCowsGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullsCowsGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
FString FBullsCowsGame::GetHiddenWord() const{ return MyHiddenWord; }
bool FBullsCowsGame::IsGameWon() const { return bGameIsWon; }

int32 FBullsCowsGame::GetMaxTries() const { 
	
	// A map data structure that maps the word length to the max tries.
	TMap<int32, int32> WordLengthToMaxTries{ {3,8}, {4,12}, {5,15}, {6,21}, {7,30}  };

	/** 
	* Notice by simply returning the word length, the second integer will be known.
	* That is, if we return a word length of 3 (key), the definition 5 will be the max tries.
	* This is because the definition of '3' in our map is 5.
	*/
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullsCowsGame::Reset() {
	FString HIDDEN_WORD = GenerateRandomWord();
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
}

FString FBullsCowsGame::GenerateRandomWord() const {
	
	// Generate a random number between 0 - 14 (note the array index starts at 0).
	int32 indexGenerator = rand() % 14 + 0;
	
	// Create an array of strings named 'words'.
	FString Words[15] = { 
		"red", 
		"blue", 
		"plan", 
		"plane", 
		"jump", 
		"naruto", 
		"planet", 
		"apex", 
		"pen", 
		"distance", 
		"come", 
		"right",
		"five",
		"phone",
		"mic",
	};

	return Words[indexGenerator];
}


EGuessStatus FBullsCowsGame::CheckGuessValidity(FString Guess) const {
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) {
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}
}

/**
*				--- BULLS & COWS MECHANICS ---
*
* Increment the turn number.
* Setup a return variable.
* Loop through all letters in the guess.
*	Compare letters against the hidden word.
*	If they match:
*		Increment bulls if they're in the same place.
*		Increment cows if not.
*/

FBullCowCount FBullsCowsGame::SubmitValidGuess(FString Guess){

	// Increment turn number.
	MyCurrentTry++;

	// Setup a return variable
	FBullCowCount BullCowCount;

	// Obtain the length of MyHiddenWord and store that in a variable called HiddenWordLength.
	int32 HiddenWordLength = MyHiddenWord.length();

	// Loop through all the letters in the hidden word.
	for (int32 HWChar = 0; HWChar < HiddenWordLength; HWChar++) {
		// Compare each letters against the guess.
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++) {
			// If the letters match.
			if (Guess[GChar] == MyHiddenWord[HWChar]) {
				// If the letters are the in same place, increment bulls.
				if (HWChar == GChar) {
					BullCowCount.Bulls++;
				}
				// Else they've matched but now in the same place, increment cows.
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}

	// Handling game win condition.
	if (BullCowCount.Bulls == HiddenWordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}

	return BullCowCount;
}

/**
* Note that for this method, if we return false our error handeling enum will immediately pass the 'Not_Isogram' status.
* In other words, the moment we get a false in our map the entire method exits.
*/
bool FBullsCowsGame::IsIsogram(FString Word) const {
	
	// Treat 0 and 1 letter words as isograms.
	if (Word.length() <= 1) { return true; }

	// Setup a map that ties a char to a bool and call the map "LetterSeen".
	TMap<char, bool> LetterSeen;
	
	// For all letters of the word (keyword auto - decides the data type for the variable).
	for (auto Letter : Word) {

		// Convert letters to lowercase to handle mixed case.
		Letter = tolower(Letter); 
		
		// If the letter is already the map this means we have a repeating letter, thus NOT an isogram.
		if (LetterSeen[Letter]) {
			return false;
		}
		// Otherwise, the letter hasn't been seen, map the char to true.
		else {
			LetterSeen[Letter] = true;
		}
	}
	return true; // for example in cases where /0 is entered.
}

bool FBullsCowsGame::IsLowercase(FString Word) const
{

	// Treat 0 and 1 letter words as isograms.
	if (Word.length() <= 1) { return true; }
	
	// For all letters of the word:
	for (auto Letter : Word) {

		// If the letter is not lower case we return false, otherwise we return true.
		if (!islower(Letter)) {
			return false;
		} else {
			return true;
		}
	}
	return true;
}
