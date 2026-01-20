#ifndef WORD_H
#define WORD_H

#include <string>
#include <vector>
#include <set>

class Word {
protected:
    std::string secretWord;
    std::string displayWord;
    std::set<char> guessedLetters;

    void initializeDisplayWord();

public:
    Word(const std::string& word);
    virtual ~Word() = default;

    virtual bool guessLetter(char letter);
    virtual bool guessWord(const std::string& guess);
    virtual void revealLetter();

    std::string getDisplayWord() const { return displayWord; }
    std::string getSecretWord() const { return secretWord; }
    bool isComplete() const;
    int getRemainingLetters() const;

    virtual void display() const;
    virtual std::string getType() const = 0;
};

class NormalWord : public Word {
public:
    NormalWord(const std::string& word);
    std::string getType() const override { return "Normal"; }
};

class BonusWord : public Word {
private:
    int bonusMultiplier;

public:
    BonusWord(const std::string& word, int multiplier = 2);
    int getBonusMultiplier() const { return bonusMultiplier; }
    std::string getType() const override { return "Bonus"; }
};

#endif