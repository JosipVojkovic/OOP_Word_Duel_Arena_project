#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Word.h"
#include <vector>
#include <string>

class Game {
private:
    std::vector<Player*> players;
    std::vector<std::string> wordList;
    int currentPlayerIndex;
    int totalRounds;
    int currentRound;
    Word* currentWord;

    int scoreMultiplier;
    bool shieldActive;
    bool extraTurnGranted;

    void initializeWordList();
    Word* selectRandomWord();
    void distributePowerUps();
    void nextPlayer();
    bool handlePlayerTurn(Player* player);
    void displayGameStatus() const;
    void displayRoundStart() const;
    void displayRoundEnd() const;

public:
    Game(int rounds = 3);
    ~Game();

    void addPlayer(Player* player); // Game takes ownership
    void initialize();

    void start();
    void playRound();

    void displayFinalResults() const;
    void saveResults(const std::string& filename) const;

    void setScoreMultiplier(int multiplier) { scoreMultiplier = multiplier; }
    void activateShield() { shieldActive = true; }
    void grantExtraTurn() { extraTurnGranted = true; }
    void resetPowerUpEffects();

    int getCurrentRound() const { return currentRound; }
    int getTotalRounds() const { return totalRounds; }
};

#endif