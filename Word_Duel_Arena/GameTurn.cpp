#include "Game.h"
#include "PowerUp.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <limits>

bool Game::handlePlayerTurn(Player* player) {
    displayGameStatus();

    std::cout << "\n>>> " << player->getName() << " je na potezu! <<<\n\n";

    std::cout << "sto zelis uciniti?\n";
    std::cout << "  1. Pogodi slovo\n";
    std::cout << "  2. Pogodi cijelu rijec\n";
    if (player->hasPowerUps() && !player->hasPowerUpUsed()) {
        std::cout << "  3. Koristi power-up\n";
    }
    std::cout << "\nOdabir: ";

    int choice;
    std::cin >> choice;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Neispravan unos!\n";
        return false;
    }

    if (choice == 1) {
        std::cout << "Unesi slovo: ";
        char letter;
        std::cin >> letter;

        bool correct = currentWord->guessLetter(letter);

        if (correct) {
            int points = 1 * scoreMultiplier;
            player->addPoints(points);
            std::cout << "\nTocno! +" << points << " bodova\n";
            resetPowerUpEffects();

            if (currentWord->isComplete()) {
                std::cout << "\n*** RIJEC JE POGODENA! ***\n";
                return true;
            }
            return false;
        }
        else {
            if (!shieldActive) {
                player->subtractPoints(1);
                std::cout << "\nNetocno! -1 bod\n";
            }
            else {
                std::cout << "\nNetocno! (Ali stit te zastitio)\n";
            }
            resetPowerUpEffects();
            return false;
        }

    }
    else if (choice == 2) {
        std::cout << "Unesi rijec: ";
        std::string guess;
        std::cin >> guess;

        bool correct = currentWord->guessWord(guess);

        if (correct) {
            int points = 5 * scoreMultiplier;

            auto bonusWord = dynamic_cast<BonusWord*>(currentWord);
            if (bonusWord) {
                points *= bonusWord->getBonusMultiplier();
            }

            player->addPoints(points);
            std::cout << "\n*** BRAVO! Pogodio si cijelu rijec! +" << points << " bodova ***\n";
            resetPowerUpEffects();
            return true;
        }
        else {
            if (!shieldActive) {
                player->subtractPoints(2);
                std::cout << "\nNetocno! -2 boda\n";
            }
            else {
                std::cout << "\nNetocno! (Ali stit te zastitio)\n";
            }
            resetPowerUpEffects();
            return false;
        }

    }
    else if (choice == 3 && player->hasPowerUps() && !player->hasPowerUpUsed()) {
        std::cout << "\nDostupni power-upovi:\n";
        player->displayPowerUps();

        std::cout << "\nOdaberi power-up (broj ili 0 za odustajanje): ";
        int powerUpChoice;
        std::cin >> powerUpChoice;

        if (powerUpChoice > 0 && powerUpChoice <= player->getPowerUpCount()) {
            PowerUp* powerUp = player->usePowerUp(powerUpChoice - 1);
            if (powerUp) {
                powerUp->apply(this, player, currentWord);

                delete powerUp;

                if (currentWord->isComplete()) {
                    std::cout << "\n*** RIJEC JE POGODENA! ***\n";
                    return true;
                }

                std::cout << "\nNakon power-upa napravi svoj potez!\n";
                std::cout << "Pritisni Enter...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();

                return handlePlayerTurn(player);
            }
        }
        return handlePlayerTurn(player);

    }
    else {
        std::cout << "Neispravan odabir!\n";
        return handlePlayerTurn(player);
    }
}

void Game::playRound() {
    currentRound++;

    delete currentWord;
    currentWord = selectRandomWord();

    currentPlayerIndex = 0;

    for (auto& player : players) {
        player->resetPowerUpFlag();
    }

    displayRoundStart();

    bool roundComplete = false;
    while (!roundComplete) {
        auto currentPlayer = players[currentPlayerIndex];
        bool wordCompleted = handlePlayerTurn(currentPlayer);

        if (wordCompleted || currentWord->isComplete()) {
            roundComplete = true;
        }
        else {
            nextPlayer();
        }

        if (!roundComplete) {
            std::cout << "\nPritisni Enter za nastavak...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }

    displayRoundEnd();
}

void Game::start() {
    for (int i = 0; i < totalRounds; ++i) {
        playRound();

        if (i < totalRounds - 1) {
            std::cout << "\nSpremni za sljedecu rundu? (Pritisni Enter)";
            std::cin.get();
        }
    }

    displayFinalResults();
}