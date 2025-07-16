#include "HangmanGame.h"
#include <ctime>
#include <cstdlib>
#include <cctype>

HangmanGame::HangmanGame() : maxGuesses(6), remainingGuesses(maxGuesses), gameWon(false), gameLost(false) {
	EASY = 1;
	MEDIUM = 2;
	HARD = 3;
	enableKey;
	selectedDifficulty = 0;
	loadWords();
}

void HangmanGame::targettedWord() {
	targetWord = chosenWord;
}

void HangmanGame::loadWords() {
	easyAnimals = { "CAT", "DOG", "RAT", "COW", "GOAT", "HORSE" };
	easyVerbs = { "RUN", "EAT", "SIT", "WALK", "SING", "COOK" };
	easyProfessions = { "BAKER", "NURSE", "CHEF", "FARMER", "DANCER", "PILOT" };

	mediumAnimals = { "SNAKE", "DEER", "PANDA", "TIGER", "LION", "FOX" };
	mediumVerbs = { "JUMP", "READ", "DRIVE", "STUDY", "SWIM", "THINK" };
	mediumProfessions = { "DOCTOR", "ACTOR", "TEACHER", "SCIENTIST", "ENGINEER", "MANAGER" };

	hardAnimals = { "MONKEY", "KANGAROO", "ELEPHANT", "ZEBRA", "LIZARD", "LEOPARD" };
	hardVerbs = { "NEGOTIATE", "UNDERSTAND", "DEVELOP", "WATCH", "CLIMB", "SMILE" };
	hardProfessions = { "ACCOUNTANT", "MUSICIAN", "CARPENTER", "ARCHITECT", "ELECTRICIAN", "PLUMBER" };
}

void HangmanGame::chooseWord() {
	srand(static_cast<unsigned>(time(nullptr)));
	int categoryIndex = rand() % 3;

	if (selectedDifficulty == EASY) {
		if (categoryIndex == 0) {
			chosenWord = easyAnimals[rand() % easyAnimals.size()];
			category = "Animal";
		}
		else if (categoryIndex == 1) {
			chosenWord = easyVerbs[rand() % easyVerbs.size()];
			category = "Verb";
		}
		else {
			chosenWord = easyProfessions[rand() % easyProfessions.size()];
			category = "Profession";
		}
	}
	else if (selectedDifficulty == MEDIUM) {
		if (categoryIndex == 0) {
			chosenWord = mediumAnimals[rand() % mediumAnimals.size()];
			category = "Animal";
		}
		else if (categoryIndex == 1) {
			chosenWord = mediumVerbs[rand() % mediumVerbs.size()];
			category = "Verb";
		}
		else {
			chosenWord = mediumProfessions[rand() % mediumProfessions.size()];
			category = "Profession";
		}
	}
	else if (selectedDifficulty == HARD) {
		if (categoryIndex == 0) {
			chosenWord = hardAnimals[rand() % hardAnimals.size()];
			category = "Animal";
		}
		else if (categoryIndex == 1) {
			chosenWord = hardVerbs[rand() % hardVerbs.size()];
			category = "Verb";
		}
		else {
			chosenWord = hardProfessions[rand() % hardProfessions.size()];
			category = "Profession";
		}
	}
	targetWord = chosenWord;
}

void HangmanGame::initializeGuessedWord() {
	guessedWord = string(chosenWord.length(), '_');
}

void HangmanGame::guess(char letter) {
	letter = toupper(letter);
	if (guessedLetters.find(letter) != guessedLetters.end()) {
		return;
	}
	guessedLetters.insert(letter);

	bool letterGuessed = false;
	enableKey = false;
	for (size_t i = 0; i < chosenWord.length(); ++i) {
		if (chosenWord[i] == letter) {
			guessedWord[i] = letter;
			letterGuessed = true;
			enableKey = true;
		}
	}

	if (!letterGuessed) {
		remainingGuesses--;
		if (remainingGuesses == 0) {
			gameLost = true;
		}
	}

	if (guessedWord == chosenWord) {
		gameWon = true;
	}
}

bool HangmanGame::isGameWon() const {
	return gameWon;
}

bool HangmanGame::isGameLost() const {
	return gameLost;
}

string HangmanGame::getGuessedWord() const {
	return guessedWord;
}

int HangmanGame::getRemainingGuesses() const {
	return remainingGuesses;
}

string HangmanGame::getCategory() const {
	return category;
}

void HangmanGame::restart() {
	chooseWord();
	initializeGuessedWord();
	remainingGuesses = maxGuesses;
	gameWon = false;
	gameLost = false;
	guessedLetters.clear();
}

bool HangmanGame::isLetterGuessed(char letter) const {
	return guessedLetters.find(toupper(letter)) != guessedLetters.end();
}

void HangmanGame::revealHint() {
	bool hintGiven = false;
	for (size_t i = 0; i < chosenWord.length(); ++i) {
		if (guessedWord[i] == '_') {
			guessedWord[i] = chosenWord[i];
			guessedLetters.insert(chosenWord[i]);
			remainingGuesses--;
			hintGiven = true;
			break;
		}
	}

	if (!hintGiven) {
		remainingGuesses--;
	}

	if (remainingGuesses == 0) {
		gameLost = true;
	}

	if (guessedWord == chosenWord) {
		gameWon = true;
	}
}

