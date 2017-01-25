/* This is the console executable, that makes use of thee BullCow Class
This acts as the view in a MVC pattern, and is responsible for all 
User interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h" // functions from the header file should already be defined in FBullCowGame.cpp

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

FBullCowGame BCGame; // instantiate a new game, which we re-use across plays

// function prototypes as outside a class
void PrintIntro();
int main();
void PlayGame();
FText GetValidGuess(); 
bool AskToPlayAgain();
void PrintGameSummary();

// the entry point for our application
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0; // exit application
}

void PrintIntro()
{
	std::cout << "BETA VERSION 1.0";
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n\n";
	std::cout << "Hint: This thing is in outer space\n";
	std::cout << std::endl;
}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << MaxTries << std::endl;

	// loop asking for guesses while game is NOT won
	// and there are still tries remaning
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry () <= MaxTries) {
		FText Guess = GetValidGuess();

		// submit valid guess to the game
 		FBullCowCount FBullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << FBullCowCount.Bulls;
		std::cout << ". Cows = " << FBullCowCount.Cows << "\n\n";
	}

 	PrintGameSummary();
	return;
	}
// loop continually until user gives valid guess
FText GetValidGuess()  
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();

		//get a guess from player
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		// check for status and give feedback
		Status = BCGame.CheckGuesValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// assume guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN\n";
	}
	else
	{
		std::cout << "You Suck! Better luck next time\n";
	}
}
