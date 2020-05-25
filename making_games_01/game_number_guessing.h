#ifndef GAME_NUMBER_GUESSING_H
#define GAME_NUMBER_GUESSING_H

#include <iostream>
#include <string>

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

    const int8_t guess(const uint input_num);
    const bool play();

 private:
    static const uint MAX_TRIES = 6;

    const uint _get_num(const uint min = 0, const uint max = MAX_NUMBER);
    void _hint(const uint min, const uint max);
    void _correct_answer();
    void _game_over();

    void _cout() const;
    void _cout(const std::string& msg, const bool endl = true) const;

    const uint _number;
    uint _tries = Game::MAX_TRIES;
};


#endif
