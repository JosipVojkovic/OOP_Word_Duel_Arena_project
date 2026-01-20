#include "Word.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <random>

Word::Word(const std::string& word) : secretWord(word) {
    std::transform(secretWord.begin(), secretWord.end(), secretWord.begin(), ::toupper);
    initializeDisplayWord();
}

void Word::initializeDisplayWord() {
    displayWord = "";
    for (char c : secretWord) {
        if (std::isalpha(c)) {
            displayWord += '_';
        }
        else {
            displayWord += c;
        }
    }
}

bool Word::guessLetter(char letter) {
    letter = std::toupper(letter);

    if (guessedLetters.find(letter) != guessedLetters.end()) {
        return false;
    }

    guessedLetters.insert(letter);

    bool found = false;
    for (size_t i = 0; i < secretWord.length(); ++i) {
        if (secretWord[i] == letter) {
            displayWord[i] = letter;
            found = true;
        }
    }

    return found;
}

bool Word::guessWord(const std::string& guess) {
    std::string upperGuess = guess;
    std::transform(upperGuess.begin(), upperGuess.end(), upperGuess.begin(), ::toupper);

    if (upperGuess == secretWord) {
        displayWord = secretWord;
        return true;
    }
    return false;
}

void Word::revealLetter() {
    std::vector<size_t> hiddenIndices;
    for (size_t i = 0; i < displayWord.length(); ++i) {
        if (displayWord[i] == '_') {
            hiddenIndices.push_back(i);
        }
    }

    if (!hiddenIndices.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, static_cast<int>(hiddenIndices.size()) - 1);
        size_t index = hiddenIndices[dis(gen)];

        char letter = secretWord[index];
        guessedLetters.insert(letter);

        for (size_t i = 0; i < secretWord.length(); ++i) {
            if (secretWord[i] == letter) {
                displayWord[i] = letter;
            }
        }
    }
}

bool Word::isComplete() const {
    return displayWord.find('_') == std::string::npos;
}

int Word::getRemainingLetters() const {
    return static_cast<int>(std::count(displayWord.begin(), displayWord.end(), '_'));
}

void Word::display() const {
    std::cout << "  ";
    for (char c : displayWord) {
        std::cout << c << " ";
    }
    std::cout << "\n";
}

NormalWord::NormalWord(const std::string& word) : Word(word) {}

BonusWord::BonusWord(const std::string& word, int multiplier)
    : Word(word), bonusMultiplier(multiplier) {
}