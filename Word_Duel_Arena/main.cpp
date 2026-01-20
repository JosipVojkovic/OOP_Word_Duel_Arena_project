#include "Game.h"
#include "Player.h"
#include <iostream>
#include <limits>
#include <string>

void displayWelcome() {
    std::cout << "\n";
    std::cout << " ============================================================== \n";
    std::cout << "||                                                            ||\n";
    std::cout << "||              ||     ||  ||||||  ||||||  ||||||             ||\n";
    std::cout << "||              ||     || ||    || ||   || ||   ||            ||\n";
    std::cout << "||              ||  |  || ||    || ||||||  ||   ||            ||\n";
    std::cout << "||              || ||| || ||    || ||   || ||   ||            ||\n";
    std::cout << "||               ||| |||   ||||||  ||   || ||||||             ||\n";
    std::cout << "||                                                            ||\n";
    std::cout << "||                  ||||||  ||    || ||||||| ||               ||\n";
    std::cout << "||                  ||   || ||    || ||      ||               ||\n";
    std::cout << "||                  ||   || ||    || |||||   ||               ||\n";
    std::cout << "||                  ||   || ||    || ||      ||               ||\n";
    std::cout << "||                  ||||||   ||||||  ||||||| |||||||          ||\n";
    std::cout << "||                                                            ||\n";
    std::cout << "||               |||||  ||||||  ||||||| |||    ||  |||||      ||\n";
    std::cout << "||              ||   || ||   || ||      ||||   || ||   ||     ||\n";
    std::cout << "||              ||||||| ||||||  |||||   || ||  || |||||||     ||\n";
    std::cout << "||              ||   || ||   || ||      ||  || || ||   ||     ||\n";
    std::cout << "||              ||   || ||   || ||||||| ||   |||| ||   ||     ||\n";
    std::cout << "||                                                            ||\n";
    std::cout << " ============================================================== \n";
    std::cout << "\n";
    std::cout << "          Turn-based konzolna igra za tri igraca\n";
    std::cout << "          Pogadaj slova, koristi power-upove i pobijedi!\n\n";
}


void displayRules() {
    std::cout << "\n=== PRAVILA IGRE ===\n\n";
    std::cout << "- Igra se sastoji od odredenog broja rundi\n";
    std::cout << "- U svakoj rundi igraci naizmjenicno pogadaju rijec\n";
    std::cout << "- Mozes pogadati pojedina slova ili cijelu rijec\n";
    std::cout << "- Tocno pogodeno slovo: +1 bod\n";
    std::cout << "- Tocno pogodena rijec: +5 bodova\n";
    std::cout << "- Pogresno slovo: -1 bod\n";
    std::cout << "- Pogresna rijec: -2 boda\n";
    std::cout << "- Pobjeduje igrac s najvise bodova na kraju!\n\n";

    std::cout << "=== TIPOVI IGRAcA ===\n\n";
    std::cout << "1. AGGRESSIVE - Veci dobitak (+50%), veci gubitak (+50%)\n";
    std::cout << "2. DEFENSIVE  - Normalan dobitak, manji gubitak (-50%)\n";
    std::cout << "3. BALANCED   - Standardno bodovanje\n\n";

    std::cout << "=== POWER-UPOVI ===\n\n";
    std::cout << "- Reveal Letter - Otkriva jedno nasumicno slovo\n";
    std::cout << "- Double Score  - Udvostrucuje bodove sljedeceg poteza\n";
    std::cout << "- Extra Turn    - Daje dodatni potez\n";
    std::cout << "- Shield        - stiti od gubitka bodova\n\n";
}

Player* createPlayer(const std::string& playerNumber) {
    std::cout << "\n=== Konfiguracija igraca " << playerNumber << " ===\n";
    std::cout << "Unesi ime: ";
    std::string name;
    std::getline(std::cin, name);

    std::cout << "\nOdaberi tip igraca:\n";
    std::cout << "  1. Aggressive (veci dobitak, veci gubitak)\n";
    std::cout << "  2. Defensive (normalan dobitak, manji gubitak)\n";
    std::cout << "  3. Balanced (standardno bodovanje)\n";
    std::cout << "Odabir: ";

    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Player* player = nullptr;
    switch (choice) {
    case 1:
        player = new AggressivePlayer(name);
        break;
    case 2:
        player = new DefensivePlayer(name);
        break;
    case 3:
        player = new BalancedPlayer(name);
        break;
    default:
        std::cout << "Neispravan odabir! Koristi se Balanced tip.\n";
        player = new BalancedPlayer(name);
    }

    std::cout << "Igrac kreiran: " << player->getName()
        << " [" << player->getType() << "]\n";

    return player;
}

int main() {
    try {
        displayWelcome();

        std::cout << "zelis li vidjeti pravila igre? (d/n): ";
        char showRules;
        std::cin >> showRules;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (showRules == 'd' || showRules == 'D') {
            displayRules();
            std::cout << "Pritisni Enter za nastavak...";
            std::cin.get();
        }

        std::cout << "\nKoliko rundi zelis igrati? (preporuceno 3-5): ";
        int rounds;
        std::cin >> rounds;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (rounds < 1 || rounds > 10) {
            std::cout << "Broj rundi mora biti izmedu 1 i 10. Koristi se 3.\n";
            rounds = 3;
        }

        Game game(rounds);

        std::cout << "\n" << std::string(60, '=') << "\n";
        std::cout << "KREIRANJE IGRACA (potrebna su 3 igraca)\n";
        std::cout << std::string(60, '=') << "\n";

        for (int i = 1; i <= 3; ++i) {
            Player* player = createPlayer(std::to_string(i));
            game.addPlayer(player);
        }

        game.initialize();

        std::cout << "\n" << std::string(60, '=') << "\n";
        std::cout << "SVE JE SPREMNO! Zapocinjemo igru...\n";
        std::cout << std::string(60, '=') << "\n";
        std::cout << "\nPritisni Enter za pocetak...";
        std::cin.get();

        game.start();

        std::cout << "\nzelis li spremiti rezultate? (d/n): ";
        char saveChoice;
        std::cin >> saveChoice;

        if (saveChoice == 'd' || saveChoice == 'D') {
            game.saveResults("rezultati.txt");
        }

        std::cout << "\nzelis li igrati ponovno? (d/n): ";
        char playAgain;
        std::cin >> playAgain;

        if (playAgain == 'd' || playAgain == 'D') {
            std::cout << "\nPokreni program ponovo za novu igru!\n";
        }

        std::cout << "\nHvala na igranju! Dovidenja!\n\n";

    }
    catch (const std::exception& e) {
        std::cerr << "\nGreska: " << e.what() << "\n";
        return 1;
    }

    return 0;
}