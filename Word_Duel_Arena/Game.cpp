#include "Game.h"
#include "PowerUp.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <fstream>
#include <iomanip>
#include <limits>

Game::Game(int rounds)
    : currentPlayerIndex(0), totalRounds(rounds), currentRound(0),
    scoreMultiplier(1), shieldActive(false), extraTurnGranted(false) {
    initializeWordList();
}

void Game::initializeWordList() {
    wordList = {
        "PROGRAMIRANJE", "ALGORITAM", "STRUKTURA", "NASLJEDIVANJE",
        "POLIMORFIZAM", "ENKAPSULACIJA", "APSTRAKCIJA", "KONSTRUKTOR",
        "DESTRUKTOR", "POKAZIVAC", "REFERENCA", "LAMBDA", "EXCEPTION",
        "TEMPLATE", "NAMESPACE", "VIRTUALNA", "KOMPAJLIRANJE",
        "DEBUGIRANJE", "TESTIRANJE", "DOKUMENTACIJA", "VERZIONIRANJE"
    };
}

std::shared_ptr<Word> Game::selectRandomWord() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> wordDis(0, static_cast<int>(wordList.size()) - 1);
    std::uniform_int_distribution<> typeDis(0, 1);

    std::string selectedWord = wordList[wordDis(gen)];
    int wordType = typeDis(gen);

    switch (wordType) {
    case 0:
        return std::make_shared<NormalWord>(selectedWord);
    case 1:
        return std::make_shared<BonusWord>(selectedWord, 2);
    default:
        return std::make_shared<NormalWord>(selectedWord);
    }
}

void Game::distributePowerUps() {
    std::vector<std::shared_ptr<PowerUp>> availablePowerUps = {
        std::make_shared<RevealLetterPowerUp>(),
        std::make_shared<DoubleScorePowerUp>(),
        std::make_shared<ExtraTurnPowerUp>(),
        std::make_shared<ShieldPowerUp>()
    };

    std::random_device rd;
    std::mt19937 gen(rd());

    for (auto& player : players) {
        std::shuffle(availablePowerUps.begin(), availablePowerUps.end(), gen);
        int numPowerUps = 1 + (gen() % 2);

        for (int i = 0; i < numPowerUps && i < static_cast<int>(availablePowerUps.size()); ++i) {
            std::shared_ptr<PowerUp> powerUp;
            if (availablePowerUps[i]->getName() == "Reveal Letter") {
                powerUp = std::make_shared<RevealLetterPowerUp>();
            }
            else if (availablePowerUps[i]->getName() == "Double Score") {
                powerUp = std::make_shared<DoubleScorePowerUp>();
            }
            else if (availablePowerUps[i]->getName() == "Extra Turn") {
                powerUp = std::make_shared<ExtraTurnPowerUp>();
            }
            else {
                powerUp = std::make_shared<ShieldPowerUp>();
            }
            player->addPowerUp(powerUp);
        }
    }
}

void Game::addPlayer(std::shared_ptr<Player> player) {
    players.push_back(player);
}

void Game::initialize() {
    if (players.size() != 3) {
        throw std::runtime_error("Igra zahtijeva tocno 3 igraca!");
    }

    distributePowerUps();
    currentPlayerIndex = 0;
    currentRound = 0;
}

void Game::resetPowerUpEffects() {
    scoreMultiplier = 1;
    shieldActive = false;
    extraTurnGranted = false;
}

void Game::nextPlayer() {
    if (!extraTurnGranted) {
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }
    extraTurnGranted = false;
}

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
        std::cout << std::fixed << std::setprecision(1) << static_cast<double>(player->getScore());
        std::cout << std::defaultfloat << " bodova\n";
    }
    std::cout << std::string(60, '-') << "\n";
}

bool Game::handlePlayerTurn(std::shared_ptr<Player> player) {
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

            auto bonusWord = std::dynamic_pointer_cast<BonusWord>(currentWord);
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
            auto powerUp = player->usePowerUp(powerUpChoice - 1);
            if (powerUp) {
                powerUp->apply(this, player.get(), currentWord.get());

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

void Game::displayFinalResults() const {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << std::string(20, ' ') << "KRAJ IGRE\n";
    std::cout << std::string(60, '=') << "\n\n";

    std::vector<std::shared_ptr<Player>> sortedPlayers = players;
    std::sort(sortedPlayers.begin(), sortedPlayers.end(),
        [](const auto& a, const auto& b) { return a->getScore() > b->getScore(); });

    std::cout << "KONACNI REZULTATI:\n\n";
    for (size_t i = 0; i < sortedPlayers.size(); ++i) {
        std::cout << (i + 1) << ". ";
        sortedPlayers[i]->displayInfo();
    }

    std::cout << "\n";
    if (sortedPlayers[0]->getScore() > sortedPlayers[1]->getScore()) {
        std::cout << "POBJEDNIK: " << sortedPlayers[0]->getName()
            << " s ";
        std::cout << std::fixed << std::setprecision(1) << static_cast<double>(sortedPlayers[0]->getScore());
        std::cout << std::defaultfloat << " bodova!\n";
    }
    else {
        std::cout << "NERIJESENO izmedu:\n";
        for (const auto& player : sortedPlayers) {
            if (player->getScore() == sortedPlayers[0]->getScore()) {
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
        file << std::fixed << std::setprecision(1) << static_cast<double>(sortedPlayers[i]->getScore());
        file << std::defaultfloat << " bodova\n";
    }

    file.close();
    std::cout << "Rezultati spremljeni u: " << filename << "\n";
}