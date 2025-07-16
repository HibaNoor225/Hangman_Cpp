#ifndef HANGMANGAME_H
#define HANGMANGAME_H

#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class HangmanGame {
protected:
	vector<string> easyAnimals;
	vector<string> easyVerbs;
	vector<string> easyProfessions;

	vector<string> mediumAnimals;
	vector<string> mediumVerbs;
	vector<string> mediumProfessions;

	vector<string> hardAnimals;
	vector<string> hardVerbs;
	vector<string> hardProfessions;

	string targetWord;
	string chosenWord;
	string guessedWord;
	string category;

	int maxGuesses;
	int remainingGuesses;
	int selectedDifficulty;

	int EASY;
	int MEDIUM;
	int HARD;

	bool gameWon;
	bool gameLost;
	bool enableKey;

	unordered_set<char> guessedLetters;

public:
	HangmanGame();

	void targettedWord();

	void loadWords();

	void chooseWord();

	void initializeGuessedWord();

	void guess(char letter);

	bool isGameWon() const;

	bool isGameLost() const;

	string getGuessedWord() const;

	int getRemainingGuesses() const;

	string getCategory() const;

	void restart();

	bool isLetterGuessed(char letter) const;

	void revealHint();
};

#endif 
