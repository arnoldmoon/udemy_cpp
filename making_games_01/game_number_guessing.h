#ifndef GAME_NUMBER_GUESSING_H
#define GAME_NUMBER_GUESSING_H

#include <iostream>

class Game_cout : private std::streambuf , public std::ostream {
 public:
    Game_cout();

 private:
    int overflow(int c);
};

class Game {
 public:
    static const uint MAX_NUMBER = 100;

    static uint random();
    static uint random(const uint min, const uint max);

    Game();
    explicit Game(const uint number);

    int8_t guess(const uint guess);
    bool play();

 private:
    static const uint MAX_TRIES = 6;

    void _correct_answer();
    void _game_over();

    Game_cout _cout;

    const uint _number;
    uint _tries = Game::MAX_TRIES;
};


#endif
