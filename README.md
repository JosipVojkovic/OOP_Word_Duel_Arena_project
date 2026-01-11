# Word Duel Arena 🎮

**Turn-based konzolna igra za tri igrača napisana u C++**

Projekt za kolegij Objektno orijentirano programiranje - demonstracija OOP principa u C++.

---

## 📋 Opis projekta

Word Duel Arena je interaktivna konzolna igra u kojoj tri igrača natječu se kroz više rundi pogađajući riječi. Igrači mogu birati između različitih tipova karaktera, koristiti power-upove i strategijski pristupiti igri kako bi skupili najviše bodova.

### Ključne značajke:
- ✅ **Tri igrača** s različitim tipovima karaktera
- ✅ **Nasljeđivanje** - hijerarhije klasa za igrače, riječi i power-upove
- ✅ **Polimorfizam** - virtualne metode i dinamičko vezivanje
- ✅ **Enkapsulacija** - privatni članovi s javnim sučeljima
- ✅ **Apstraktne klase** - čista sučelja za Player, Word, PowerUp
- ✅ **Smart pointeri** - moderne C++ prakse upravljanja memorijom
- ✅ **STL kolekcije** - vector, set, string
- ✅ **Lambda funkcije** - za sortiranje i funkcijske objekte
- ✅ **Exception handling** - sigurno rukovanje greškama

---

## 🎯 Kako pokrenuti projekt

### Preduvjeti

- **C++17 kompajler** (Visual Studio 2017+)

### Visual Studio (Windows)

1. Otvori Visual Studio
2. Kreiraj novi **Console Application** projekt
3. Dodaj sve `.cpp` i `.h` datoteke u projekt
4. Postavi **C++ Language Standard** na **ISO C++17**
5. Build (Ctrl+Shift+B) i Run (F5)

---

## 🎮 Kontrole u igri

### Tijekom postavljanja:
- Unos imena igrača
- Odabir tipa igrača (1-3)
- Odabir broja rundi

### Tijekom igre:
- **1** - Pogodi slovo
- **2** - Pogodi cijelu riječ
- **3** - Koristi power-up (ako je dostupan)
- **Enter** - Nastavi na sljedeći potez

### Unos:
- **Slova**: Jedno slovo (npr. `A`)
- **Riječ**: Cijela riječ (npr. `PROGRAMIRANJE`)
- **Power-up**: Broj power-upa (1-N)

---

## 🏆 Pravila igre

### Bodovanje:
- ✅ **Točno slovo**: +1 bod (ostaneš na potezu)
- ✅ **Točna riječ**: +5 bodova
- ❌ **Pogrešno slovo**: -1 bod (red prelazi)
- ❌ **Pogrešna riječ**: -2 boda (red prelazi)

### Tipovi igrača:
1. **Aggressive** 🔥
   - Dobitak: +50% bodova
   - Gubitak: +50% bodova
   - *Strategija*: Visok rizik, visoka nagrada

2. **Defensive** 🛡️
   - Dobitak: Normalan
   - Gubitak: -50% bodova
   - *Strategija*: Sigurna igra, manja kazna

3. **Balanced** ⚖️
   - Dobitak: Normalan
   - Gubitak: Normalan
   - *Strategija*: Standardno bodovanje

### Power-upovi:
- **Reveal Letter** 🔍 - Otkriva jedno nasumično slovo
- **Double Score** ⚡ - Udvostručuje bodove sljedećeg poteza
- **Extra Turn** 🔄 - Daje dodatni potez
- **Shield** 🛡️ - Štiti od gubitka bodova sljedeći potez

*Napomena: Power-up možeš koristiti samo jednom po rundi!*

### Tipovi riječi:
- **Normal** 📝 - Standardna riječ
- **Encrypted** 🔐 - ROT13 šifrirana (teža za pogađanje)
- **Bonus** 💎 - Dvostruki bodovi za pogađanje cijele riječi

---

## 📁 Struktura projekta

```
word-duel-arena/
│
├── main.cpp          # Glavna aplikacija i izbornici
├── Game.h/.cpp       # Logika igre i upravljanje rundama
├── Player.h/.cpp     # Hijerarhija igrača (Aggressive/Defensive/Balanced)
├── Word.h/.cpp       # Hijerarhija riječi (Normal/Encrypted/Bonus)
├── PowerUp.h/.cpp    # Hijerarhija power-upova
├── Makefile          # Build skripta
└── README.md         # Dokumentacija
```

---

## 🔧 Ovisnosti

**Projekt nema vanjskih ovisnosti!**

Koristi samo standardnu C++ biblioteku:
- `<iostream>` - I/O operacije
- `<vector>` - Dinamičke kolekcije
- `<memory>` - Smart pointeri (shared_ptr)
- `<string>` - Rad s tekstom
- `<set>` - Skupovi za praćenje pogođenih slova
- `<algorithm>` - Algoritmi (sort, shuffle, transform)
- `<random>` - Generiranje nasumičnih brojeva
- `<fstream>` - Rad s datotekama

---

## 🐛 Rješavanje problema

### Problem: "g++ nije prepoznat kao naredba"
**Rješenje**: Instaliraj GCC kompajler
- **Linux**: `sudo apt install g++`
- **macOS**: `xcode-select --install`
- **Windows**: Instaliraj MinGW ili Visual Studio

### Problem: "make nije prepoznat kao naredba"
**Rješenje**: Koristi ručno kompajliranje ili instaliraj Make
- **Windows**: Instaliraj MinGW s make alatom
- **Alternative**: Koristi CMD naredbu iznad

### Problem: Program ne kompajlira zbog C++17
**Rješenje**: Provjeri da koristiš `-std=c++17` flag i dovoljno noviju verziju kompaijlera

### Problem: "Neispravan unos" tijekom igre
**Rješenje**: Unesi samo slova bez razmaka. Za riječi unesi cijelu riječ bez razmaka.

### Problem: Igra se crashira
**Rješenje**: Provjerite da unosite valjan unos (brojeve za izbornike, slova za pogađanje)

---

## 📊 Demonstracija OOP koncepata

### 1. Nasljeđivanje (Inheritance)
```cpp
class Player { /* bazna klasa */ };
class AggressivePlayer : public Player { /* izvedena klasa */ };
```

### 2. Polimorfizam (Polymorphism)
```cpp
virtual void addPoints(int points) = 0;  // Pure virtual
player->addPoints(5);  // Poziva se odgovarajuća implementacija
```

### 3. Enkapsulacija (Encapsulation)
```cpp
private:
    int score;
public:
    int getScore() const { return score; }
```

### 4. Apstrakcija (Abstraction)
```cpp
class Player { /* apstraktna bazna klasa */ };
// Ne može se instancirati direktno
```

### 5. RAII i Smart Pointeri
```cpp
std::shared_ptr<Player> player = std::make_shared<AggressivePlayer>(name);
// Automatsko oslobađanje memorije
```

---

## 🎓 Autor

**Josip Vojković**  
Akademska godina: 2025/2026  
Kolegij: Objektno orijentirano programiranje

---

## 📝 Licenca

Ovaj projekt je napravljen isključivo u edukacijske svrhe za kolegij OOP.

---

## 🎉 Uživaj u igri!

Ako naiđeš na probleme ili imaš prijedloge, slobodno otvori issue na GitHubu!

**Sretno i neka pobijedi najbolji! 🏆**
