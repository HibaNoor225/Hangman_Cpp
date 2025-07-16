#include "HangmanUI.h"
#include <iostream>
HangmanUI::HangmanUI() {
	score = 0;
	winSoundPlayed = false;
	loseSoundPlayed = false;
	createRestartQuitButtons();
	initWindow();
	loadFont();
	loadTextures();
	createHangmanSprite();
	createLetterButtons();
	initTextObjects();
	loadSounds();
}

void HangmanUI::createRestartQuitButtons() {
	restartButton.setFont(font);
	restartButton.setCharacterSize(30);
	restartButton.setString("Restart");
	restartButton.setFillColor(Color(0, 100, 0));
	restartButton.setPosition(200.f, 450.f);

	quitButton.setFont(font);
	quitButton.setCharacterSize(30);
	quitButton.setString("Quit");
	quitButton.setFillColor(Color(81, 4, 0));
	quitButton.setPosition(350.f, 450.f);
}

void HangmanUI::handleRestartButton() {
	selectedDifficulty = 0;
	restart();
	resetButtonColors();
	winSoundPlayed = false;
	loseSoundPlayed = false;
}

void HangmanUI::handleQuitButton() {
	window.close();
}

void HangmanUI::loadSounds() {
	if (!correctSoundBuffer.loadFromFile("correct.wav")) {
		cout << "Failed to load correct.wav" << endl;
	}
	if (!wrongSoundBuffer.loadFromFile("wrong.wav")) {
		cout << "Failed to load wrong.wav" << endl;
	}
	correctSound.setBuffer(correctSoundBuffer);
	wrongSound.setBuffer(wrongSoundBuffer);

	if (!winSoundBuffer.loadFromFile("win.wav")) {
		cerr << "Failed to load win.wav" << endl;
	}
	if (!loseSoundBuffer.loadFromFile("lose.wav")) {
		cerr << "Failed to load lose.wav" << endl;
	}
	winSound.setBuffer(winSoundBuffer);
	loseSound.setBuffer(loseSoundBuffer);
}

void HangmanUI::setScore(int s) {
	score = s;
}

int HangmanUI::getScore() {
	return score;
}

void HangmanUI::initWindow() {
	window.create(VideoMode(1000, 600), "Hangman");
	window.setFramerateLimit(60);
}

void HangmanUI::loadFont() {
	if (!font.loadFromFile("FORTE.ttf")) {
		cerr << "Failed to load font." << endl;
	}
}

void HangmanUI::loadTextures() {
	for (int i = 0; i < 7; ++i) {
		if (!hangmanTextures[i].loadFromFile("hangman" + to_string(i) + ".png")) {
			cerr << "Failed to load hangman texture " << i << endl;
		}
	}
}

void HangmanUI::createHangmanSprite() {
	hangmanSprite.setTexture(hangmanTextures[0]);
	hangmanSprite.setPosition(350, -50);
	hangmanSprite.setScale(1.0f, 1.0f);
}

void HangmanUI::displayStartScreen() {
	Text hangmanText;
	hangmanText.setFont(font);
	hangmanText.setCharacterSize(70);
	hangmanText.setString("HANGMAN");
	hangmanText.setFillColor(Color(81, 4, 0));
	hangmanText.setPosition(300.f, 50.f);

	Text selectText;
	selectText.setFont(font);
	selectText.setCharacterSize(30);
	selectText.setString("SELECT THE DIFFICULTY LEVEL:");
	selectText.setFillColor(Color(139, 69, 19));
	selectText.setPosition(200.f, 200.f);

	Text easyText;
	easyText.setFont(font);
	easyText.setCharacterSize(30);
	easyText.setString("1. Easy");
	easyText.setFillColor(Color(255, 69, 0));
	easyText.setPosition(200.f, 280.f);

	Text mediumText;
	mediumText.setFont(font);
	mediumText.setCharacterSize(30);
	mediumText.setString("2. Medium");
	mediumText.setFillColor(Color(255, 69, 0));
	mediumText.setPosition(200.f, 330.f);

	Text hardText;
	hardText.setFont(font);
	hardText.setCharacterSize(30);
	hardText.setString("3. Hard");
	hardText.setFillColor(Color(255, 69, 0));
	hardText.setPosition(200.f, 380.f);

	window.clear(Color(255, 250, 205));
	window.draw(hangmanText);
	window.draw(selectText);
	window.draw(easyText);
	window.draw(mediumText);
	window.draw(hardText);
	window.display();
}

void HangmanUI::createLetterButtons() {
	letterButtons.resize(26);
	float startX = 50.f;
	float startY = 400.f;
	float offsetX = 30.f;
	float offsetY = 40.f;

	for (int i = 0; i < 26; ++i) {
		letterButtons[i].setFont(font);
		letterButtons[i].setCharacterSize(26);
		letterButtons[i].setString(static_cast<char>('A' + i));
		letterButtons[i].setFillColor(Color::Black);

		float posX = startX + (i % 13) * offsetX;
		float posY = startY + (i / 13) * offsetY;
		letterButtons[i].setPosition(posX, posY);
	}

	hintButton.setFont(font);
	hintButton.setCharacterSize(50);
	hintButton.setString("Hint");
	hintButton.setFillColor(Color(255, 69, 0));
	hintButton.setPosition(400.f, 500.f);
}

void HangmanUI::initTextObjects() {
	title.setFont(font);
	title.setCharacterSize(50);
	title.setString("HANGMAN");
	title.setFillColor(Color(81, 4, 0));
	title.setPosition(50.f, 50.f);

	guessedWordText.setFont(font);
	guessedWordText.setCharacterSize(25);
	guessedWordText.setFillColor(Color(128, 0, 0));
	guessedWordText.setPosition(200.f, 300.f);

	remainingGuessesText.setFont(font);
	remainingGuessesText.setCharacterSize(25);
	remainingGuessesText.setFillColor(Color(139, 69, 19));
	remainingGuessesText.setPosition(30.f, 250.f);

	categoryText.setFont(font);
	categoryText.setCharacterSize(25);
	categoryText.setFillColor(Color(139, 69, 19));
	categoryText.setPosition(30.f, 200.f);

	scoreText.setFont(font);
	scoreText.setCharacterSize(25);
	scoreText.setFillColor(Color(139, 69, 19));
	scoreText.setPosition(30.f, 150.f);
}

void HangmanUI::drawGameObjects() {
	window.clear(Color(255, 250, 205));
	window.draw(title);
	window.draw(hangmanSprite);

	guessedWordText.setString(getFormattedGuessedWord());
	window.draw(guessedWordText);

	remainingGuessesText.setString("Remaining Guesses: " + to_string(getRemainingGuesses()));
	window.draw(remainingGuessesText);

	categoryText.setString("Category: " + getCategory());
	window.draw(categoryText);
	scoreText.setString("Score: " + to_string(getScore()));
	window.draw(scoreText);

	for (auto& button : letterButtons) {
		window.draw(button);
	}

	window.draw(hintButton);

	window.display();
}

string HangmanUI::getFormattedGuessedWord() const {
	string formattedWord;
	for (char c : guessedWord) {
		formattedWord += c;
		formattedWord += " ";
	}
	return formattedWord;
}

void HangmanUI::updateHangmanSprite() {
	int incorrectGuesses = maxGuesses - getRemainingGuesses();
	hangmanSprite.setTexture(hangmanTextures[incorrectGuesses]);
}

void HangmanUI::highlightButton(Text& button, Color color) {
	button.setFillColor(color);
}

void HangmanUI::resetButtonColors() {
	for (auto& button : letterButtons) {
		button.setFillColor(Color::Black);
	}
}

void HangmanUI::displayWinMessage() {
	Text winText;
	winText.setFont(font);
	winText.setCharacterSize(40);
	winText.setString("Congratulations! You Win...\n");
	winText.setFillColor(Color(0, 100, 0));
	winText.setPosition(120.f, 180.f);

	window.clear(Color(255, 250, 205));
	window.draw(winText);
	window.draw(restartButton);
	window.draw(quitButton);
	window.display();
}

void HangmanUI::displayLoseMessage() {
	Text loseText;
	loseText.setFont(font);
	loseText.setCharacterSize(40);
	loseText.setString("Sorry! You Lose...\n");
	loseText.setFillColor(Color::Red);
	loseText.setPosition(120.f, 180.f);

	Text wordText;
	wordText.setFont(font);
	wordText.setCharacterSize(40);
	wordText.setString("The word was: " + targetWord);
	wordText.setFillColor(Color::Red);
	wordText.setPosition(120.f, 330.f);

	window.clear(Color(255, 250, 205));
	window.draw(loseText);
	window.draw(wordText);
	window.draw(restartButton);
	window.draw(quitButton);
	window.display();
}

void HangmanUI::updateScore(bool correctGuess) {
	if (correctGuess) {
		increaseScore();
	}
	else {
		decreaseScore();
	}
}

void HangmanUI::increaseScore() {
	cout << "Score increased!" << endl;
	score += 10;
}

void HangmanUI::decreaseScore() {
	cout << "Score decreased!" << endl;
	if (score >= 10) {
		score -= 10;
	}
	else {
		score = 0;
	}
}

void HangmanUI::run() {
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					Vector2f mousePos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
					if (hintButton.getGlobalBounds().contains(mousePos)) {
						revealHint();
						updateHangmanSprite();
					}
					if (restartButton.getGlobalBounds().contains(mousePos)) {
						handleRestartButton();
					}
					else if (quitButton.getGlobalBounds().contains(mousePos)) {
						handleQuitButton();
					}
				}
			}
		}

		if (selectedDifficulty == 0) {
			displayStartScreen();
			if (Keyboard::isKeyPressed(Keyboard::Num1)) {
				selectedDifficulty = EASY;
				restart();
				winSoundPlayed = false;
				loseSoundPlayed = false;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Num2)) {
				selectedDifficulty = MEDIUM;
				restart();
				winSoundPlayed = false;
				loseSoundPlayed = false;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Num3)) {
				selectedDifficulty = HARD;
				restart();
				winSoundPlayed = false;
				loseSoundPlayed = false;
			}
		}
		else {
			if (gameWon) {
				if (!winSoundPlayed) {
					winSound.play();
					winSoundPlayed = true;
				}
				displayWinMessage();
			}
			else if (gameLost) {
				if (!loseSoundPlayed) {
					loseSound.play();
					loseSoundPlayed = true;
				}
				displayLoseMessage();
			}
			else {
				for (int i = 0; i < 26; ++i) {
					if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(Keyboard::A + i))) {
						char guessedLetter = static_cast<char>('A' + i);
						bool letterWasAlreadyGuessed = isLetterGuessed(guessedLetter);

						if (!letterWasAlreadyGuessed) {
							guess(guessedLetter);
							if (enableKey) {
								highlightButton(letterButtons[i], Color::Green);
								updateScore(true);
							}
							else {
								highlightButton(letterButtons[i], Color::Red);
								updateScore(false);
							}
						}
					}
				}

				updateHangmanSprite();
				drawGameObjects();
			}
		}
	}
}

void HangmanUI::guess(char letter) {
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

	if (letterGuessed) {
		correctSound.play();
	}
	else {
		wrongSound.play();
		remainingGuesses--;
		if (remainingGuesses == 0) {
			gameLost = true;
		}
	}

	if (guessedWord == chosenWord) {
		gameWon = true;
	}
}
