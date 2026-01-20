#include "Player.h"
#include "PowerUp.h"
#include <iostream>
#include <iomanip>
#include <cmath>

Player::Player(const std::string& playerName)
    : name(playerName), score(0.0), powerUpUsedThisRound(false) {
}

Player::~Player() {
    for (auto p : powerUps) {
        delete p;
    }
    powerUps.clear();
}

void Player::addPowerUp(PowerUp* powerUp) {
    powerUps.push_back(powerUp);
}

PowerUp* Player::usePowerUp(int index) {
    if (index >= 0 && index < static_cast<int>(powerUps.size())) {
        PowerUp* powerUp = powerUps[index];
        powerUps.erase(powerUps.begin() + index);
        powerUpUsedThisRound = true;
        return powerUp;
    }
    return nullptr;
}

void Player::displayPowerUps() const {
    if (powerUps.empty()) {
        std::cout << "  Nema dostupnih power-upova\n";
        return;
    }

    std::cout << "  Dostupni power-upovi:\n";
    for (size_t i = 0; i < powerUps.size(); ++i) {
        std::cout << "    " << (i + 1) << ". " << powerUps[i]->getName()
            << " - " << powerUps[i]->getDescription() << "\n";
    }
}

void Player::displayInfo() const {
    std::cout << name << " [" << getType() << "] - Bodovi: ";
    std::cout << std::fixed << std::setprecision(1) << score << std::defaultfloat << "\n";
}

AggressivePlayer::AggressivePlayer(const std::string& playerName)
    : Player(playerName) {
}

void AggressivePlayer::addPoints(int points) {
    score += points * 1.5;
}

void AggressivePlayer::subtractPoints(int points) {
    score -= points * 1.5;
    if (score < 0.0) score = 0.0;
}

DefensivePlayer::DefensivePlayer(const std::string& playerName)
    : Player(playerName) {
}

void DefensivePlayer::addPoints(int points) {
    score += points;
}

void DefensivePlayer::subtractPoints(int points) {
    score -= points * 0.5;
    if (score < 0.0) score = 0.0;
}

BalancedPlayer::BalancedPlayer(const std::string& playerName)
    : Player(playerName) {
}

void BalancedPlayer::addPoints(int points) {
    score += points;
}

void BalancedPlayer::subtractPoints(int points) {
    score -= points;
    if (score < 0.0) score = 0.0;
}