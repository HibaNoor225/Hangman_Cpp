#ifndef HANGMANUI_H
#define HANGMANUI_H

#include "HangmanGame.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

using namespace std;
using namespace sf;

class HangmanUI : public HangmanGame {
	int score;
	bool winSoundPlayed;
	bool loseSoundPlayed;

public:
	RenderWindow window;
	Font font;
	Text title;
	Text guessedWordText;
	Text remainingGuessesText;
	Text categoryText;
	Text scoreText;
	vector<Text> letterButtons;
	Texture hangmanTextures[7];
	Sprite hangmanSprite;

	Text hintButton;
	Text restartButton;
	Text quitButton;

	SoundBuffer correctSoundBuffer;
	SoundBuffer wrongSoundBuffer;
	Sound correctSound;
	Sound wrongSound;
	SoundBuffer winSoundBuffer;
	SoundBuffer loseSoundBuffer;
	Sound winSound;
	Sound loseSound;

	HangmanUI();

	void createRestartQuitButtons();
	void handleRestartButton();
	void handleQuitButton();
	void loadSounds();
	void setScore(int s);
	int getScore();
	void initWindow();
	void loadFont();
	void loadTextures();
	void createHangmanSprite();
	void displayStartScreen();
	void createLetterButtons();
	void initTextObjects();
	void drawGameObjects();
	string getFormattedGuessedWord() const;
	void updateHangmanSprite();
	void highlightButton(Text& button, Color color);
	void resetButtonColors();
	void displayWinMessage();
	void displayLoseMessage();
	void updateScore(bool correctGuess);
	void increaseScore();
	void decreaseScore();
	void run();
	void guess(char letter);
};
#endif
