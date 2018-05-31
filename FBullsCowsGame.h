#pragma once

/**
* Header files will contain protype functions and class blue prints that will be
* 'included' & defined in different .cpp files. This header file is NOT compiled.
*/

#include <string>

// Using namespace directive to safely subsitute type aliases. I.e: int32 = int, everywhere we see int32 it's actually int.
using FString = std::string;
using int32 = int;

// Using a struct to provide two intialized integers in one run. Structs are like classes but all it's members are public.
struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

// Check FBullsCowsGame.cpp for the actual function definitions. These are blueprints.
class FBullsCowsGame {
public:
	FBullsCowsGame(); // constructor
	
	// Keyword 'const' on the end prevents modifying the member variable.
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	int32 GetMaxTries() const;
	void Reset(); 
	FString GetHiddenWord() const;
	FString GenerateRandomWord() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	// Signature of type FBullCowCount for counting bulls and cows, and increasing tries.
	FBullCowCount SubmitValidGuess(FString);
	
// Ensure 'encapsulation' by keeping variables on a private access modifier.
private:

	// See constructor for initialisation values.
	int32 MyCurrentTry;
	bool bGameIsWon;
	FString MyHiddenWord;

	// Supporting functions / helper methods - similiar to private fields, used for declaring private functions.
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
