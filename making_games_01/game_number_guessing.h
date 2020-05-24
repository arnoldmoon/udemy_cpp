#ifndef GAME_NUMBER_GUESSING_H

#define GAME_NUMBER_GUESSING_H

#include <iostream>

class Game {
 public:
    static const int MAX_NUMBER = 100;

    static int random();
    static int random(const int min, const int max);

    Game();
    explicit Game(const int number);

    int play(const int guess);

 private:
    static const int MAX_TRIES = 3;

    void _correct_answer();
    void _hint(const int result);
    void _game_over();

    const int _number;
    int _tries = Game::MAX_TRIES;

    char _msg[15];
    std::size_t _msg_size = sizeof(_msg);
};


#endif
