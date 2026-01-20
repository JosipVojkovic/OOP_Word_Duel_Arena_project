#include "PowerUp.h"
#include "Game.h"
#include "Player.h"
#include "Word.h"
#include <iostream>

PowerUp::PowerUp(const std::string& name, const std::string& desc)
    : name(name), description(desc) {
}

RevealLetterPowerUp::RevealLetterPowerUp()
    : PowerUp("Reveal Letter", "Otkriva jedno nasumicno slovo") {
}

void RevealLetterPowerUp::apply(Game* game, Player* player, Word* word) {
    std::cout << "\n>>> " << player->getName() << " koristi 'Reveal Letter' power-up!\n";
    word->revealLetter();
    std::cout << "Otkriveno slovo!\n";
}

DoubleScorePowerUp::DoubleScorePowerUp()
    : PowerUp("Double Score", "Udvostrucuje bodove sljedeceg poteza") {
}

void DoubleScorePowerUp::apply(Game* game, Player* player, Word* word) {
    std::cout << "\n>>> " << player->getName() << " koristi 'Double Score' power-up!\n";
    game->setScoreMultiplier(2);
    std::cout << "Sljedeci potez donosi dvostruke bodove!\n";
}

ExtraTurnPowerUp::ExtraTurnPowerUp()
    : PowerUp("Extra Turn", "Daje dodatni potez") {
}

void ExtraTurnPowerUp::apply(Game* game, Player* player, Word* word) {
    std::cout << "\n>>> " << player->getName() << " koristi 'Extra Turn' power-up!\n";
    game->grantExtraTurn();
    std::cout << "Dobiven dodatni potez!\n";
}

ShieldPowerUp::ShieldPowerUp()
    : PowerUp("Shield", "stiti od gubitka bodova sljedeci potez") {
}

void ShieldPowerUp::apply(Game* game, Player* player, Word* word) {
    std::cout << "\n>>> " << player->getName() << " koristi 'Shield' power-up!\n";
    game->activateShield();
    std::cout << "stit aktiviran - nema gubitka bodova sljedeci potez!\n";
}