// #include <random>

// int
// Game::random() {
//     std::random_device rand_dev;

//     std::default_random_engine
//         rand_gen(rand_dev());

//     std::uniform_int_distribution<int>
//         rand_dist(0, Game::MAX_NUMBER);

//     return rand_dist(rand_gen);
// }

#include "./game_number_guessing.h"
#include <iostream>

Game_cout::Game_cout() : std::ostream(this) {}

int
Game_cout::overflow(int c) {
    std::cout.put(c);
    return 0;
}

Game::Game() : _number(random()) {
}

Game::Game(const int number) : _number(number) {
}

int
Game::random() {
    srand(clock());
    return rand() % Game::MAX_NUMBER;
}

int
Game::random(const int min, const int max) {
    if (max <= min) {
        return min;
    }
    srand(clock());
    return min + (rand() % (max - min));
}

void
Game::_correct_answer() {
    _tries = -1;
    _cout << "correct, you won!";
}

void
Game::_hint(const int result) {
    switch (result) {

        case 1:
            _cout << "too low, ";
            break;

        case 2:
            _cout << "too high, ";
            break;
    }

    if (_tries > 1) {
        _cout << _tries << " more guesses." << std::endl;

    } else {
        _cout << "one last guess?" << std::endl;
    }
}

void
Game::_game_over() {
    _cout << "Game is over, answer was " << _number << "." << std::endl;
}

int
Game::play(const int guess) {
    int result = -1;

    if (_tries > 0) {
        --_tries;

        if (guess == _number) {
            _correct_answer();
            return 0;
        }

        result = guess < _number ? 1 : 2;
    }

    if (_tries > 0) {
        _hint(result);
        return result;
    }

    _game_over();
    return -1;
}

int main() {

    bool won = false;
    int game_no = 0;
    do {
        Game game;
        std::cout << "#########################################################"
                     "#######################" << std::endl;
        std::cout << "game " << ++game_no << std::endl << std::endl;

        int tries = 0;
        int result = 0;
        int min = 0;
        int max = Game::MAX_NUMBER;
        do {
            int guess = ++tries < 3
                            ? (min + max) * 0.5
                            : Game::random(min, max);
            std::cout << "(" << min << " ~ " << max << ") "
                      << guess << "?" << std::endl;
            result = game.play(guess);
            switch (result) {
                case -1:
                    break;

                case 0:
                    won = true;
                    result = -1;

                case 1:
                    min = guess + 1;
                    break;

                case 2:
                    max = guess - 1;
                    break;
            }
            std::cout << std::endl;
        } while (result != -1);
    } while (!won);

    return 0;
}
