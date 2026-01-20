#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <memory>
#include <vector>

class PowerUp;

class Player {
protected:
    std::string name;
    double score;
    std::vector<std::shared_ptr<PowerUp>> powerUps;
    bool powerUpUsedThisRound;

public:
    Player(const std::string& playerName);
    virtual ~Player() = default;

    virtual void addPoints(int points) = 0;
    virtual void subtractPoints(int points) = 0;

    std::string getName() const { return name; }
    double getScore() const { return score; }
    bool hasPowerUpUsed() const { return powerUpUsedThisRound; }

    void resetPowerUpFlag() { powerUpUsedThisRound = false; }

    void addPowerUp(std::shared_ptr<PowerUp> powerUp);
    bool hasPowerUps() const { return !powerUps.empty(); }
    std::shared_ptr<PowerUp> usePowerUp(int index);
    void displayPowerUps() const;
    int getPowerUpCount() const { return static_cast<int>(powerUps.size()); }

    virtual void displayInfo() const;
    virtual std::string getType() const = 0;
};

class AggressivePlayer : public Player {
public:
    AggressivePlayer(const std::string& playerName);

    void addPoints(int points) override;
    void subtractPoints(int points) override;
    std::string getType() const override { return "Aggressive"; }
};

class DefensivePlayer : public Player {
public:
    DefensivePlayer(const std::string& playerName);

    void addPoints(int points) override;
    void subtractPoints(int points) override;
    std::string getType() const override { return "Defensive"; }
};

class BalancedPlayer : public Player {
public:
    BalancedPlayer(const std::string& playerName);

    void addPoints(int points) override;
    void subtractPoints(int points) override;
    std::string getType() const override { return "Balanced"; }
};

#endif