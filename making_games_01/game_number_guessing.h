#ifndef GAME_NUMBER_GUESSING_H
#define GAME_NUMBER_GUESSING_H

#include <iostream>
#include <string>

class Game {
 public:
    static const uint8_t MAX_NUMBER = 100;

    static uint8_t random();
    static uint8_t random(const uint8_t min, const uint8_t max);

    Game();
    explicit Game(const uint8_t number);

    const int8_t check_answer(const int input_num);
    const bool play();
    const bool game_is_over() const;
    const bool player_won() const;

 private:
    static const uint8_t MAX_TRIES = 6;

    const int _get_num() const;

    void _msg_answer_range() const;
    void _msg_try_again() const;
    void _msg_answer_too_low() const;
    void _msg_answer_too_high() const;
    void _msg_answer_correct() const;
    void _msg_game_over() const;

    void _cout() const;
    void _cout(const std::string& msg, const bool endl = true) const;

    const uint8_t _number;
    uint8_t _min = 0;
    uint8_t _max = MAX_NUMBER;
    uint8_t _guesses_left = MAX_TRIES;
    bool _won;
};


#endif
