#include "Game.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cmath>

void Game::displayGameStatus() const {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "STANJE IGRE - Runda " << currentRound << "/" << totalRounds << "\n";
    std::cout << std::string(60, '=') << "\n";

    std::cout << "\nRijec (" << currentWord->getType() << " tip):\n";
    currentWord->display();

    std::cout << "\nIgraci:\n";
    for (size_t i = 0; i < players.size(); ++i) {
        if (static_cast<int>(i) == currentPlayerIndex) {
            std::cout << ">>> ";
        }
        else {
            std::cout << "    ";
        }
        players[i]->displayInfo();
    }
    std::cout << "\n";
}

void Game::displayRoundStart() const {
    std::cout << "\n" << std::string(60, '*') << "\n";
    std::cout << "*" << std::string(58, ' ') << "*\n";
    std::cout << "*" << std::string(20, ' ') << "RUNDA " << currentRound
        << "/" << totalRounds << std::string(20, ' ') << "*\n";
    std::cout << "*" << std::string(58, ' ') << "*\n";
    std::cout << std::string(60, '*') << "\n\n";
}

void Game::displayRoundEnd() const {
    std::cout << "\n" << std::string(60, '-') << "\n";
    std::cout << "KRAJ RUNDE " << currentRound << "\n";
    std::cout << "Bodovi:\n";
    for (const auto& player : players) {
        std::cout << "  " << player->getName() << ": ";
        std::cout << std::fixed << std::setprecision(1) << player->getScore();
        std::cout << std::defaultfloat << " bodova\n";
    }
    std::cout << std::string(60, '-') << "\n";
}

void Game::displayFinalResults() const {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << std::string(20, ' ') << "KRAJ IGRE\n";
    std::cout << std::string(60, '=') << "\n\n";

    std::vector<Player*> sortedPlayers = players;
    std::sort(sortedPlayers.begin(), sortedPlayers.end(),
        [](const auto& a, const auto& b) { return a->getScore() > b->getScore(); });

    std::cout << "KONACNI REZULTATI:\n\n";
    for (size_t i = 0; i < sortedPlayers.size(); ++i) {
        std::cout << (i + 1) << ". ";
        sortedPlayers[i]->displayInfo();
    }

    std::cout << "\n";
    if (sortedPlayers.size() >= 2 && sortedPlayers[0]->getScore() > sortedPlayers[1]->getScore()) {
        std::cout << "POBJEDNIK: " << sortedPlayers[0]->getName()
            << " s ";
        std::cout << std::fixed << std::setprecision(1) << sortedPlayers[0]->getScore();
        std::cout << std::defaultfloat << " bodova!\n";
    }
    else {
        std::cout << "NERIJESENO izmedu:\n";
        for (const auto& player : sortedPlayers) {
            if (fabs(player->getScore() - sortedPlayers[0]->getScore()) < 1e-9) {
                std::cout << "  - " << player->getName() << "\n";
            }
        }
    }
    std::cout << "\n";
}

void Game::saveResults(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Greska pri otvaranju datoteke za spremanje rezultata!\n";
        return;
    }

    file << "WORD DUEL ARENA - REZULTATI IGRE\n";
    file << "================================\n\n";

    auto sortedPlayers = players;
    std::sort(sortedPlayers.begin(), sortedPlayers.end(),
        [](const auto& a, const auto& b) { return a->getScore() > b->getScore(); });

    for (size_t i = 0; i < sortedPlayers.size(); ++i) {
        file << (i + 1) << ". " << sortedPlayers[i]->getName()
            << " [" << sortedPlayers[i]->getType() << "] - ";
        file << std::fixed << std::setprecision(1) << sortedPlayers[i]->getScore();
        file << std::defaultfloat << " bodova\n";
    }

    file.close();
    std::cout << "Rezultati spremljeni u: " << filename << "\n";
}