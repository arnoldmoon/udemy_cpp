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
    srand(clock());
    return min + (rand() % (max - min));
}

namespace {

void
Game_log_msg(const char* _msg, bool endl = true) {
    if (endl) {
        std::cout << _msg << std::endl;
    } else {
        std::cout << _msg << " ";
    }
}

} /*namespace*/

void
Game::_correct_answer() {
    _tries = -1;
    Game_log_msg("correct, you won!");
}

void
Game::_hint(const int result) {
    switch (result) {

        case 1:
            Game_log_msg("too low.", false);
            break;

        case 2:
            Game_log_msg("too high.", false);
            break;
    }

    if (_tries > 1) {
        snprintf(_msg, _msg_size, "%d more guesses.", _tries);
        Game_log_msg(_msg);

    } else {
        Game_log_msg("one last guess?");
    }
}

void
Game::_game_over() {
    Game_log_msg("Game is over.", false);
    snprintf(_msg, _msg_size, "Answer was %d.", _number);
    Game_log_msg(_msg);
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

    bool won;

    do {
        Game game;
        std::cout << "#########################################################"
                     "#######################" << std::endl;
        int result = 0;
        int min = 0;
        int max = Game::MAX_NUMBER;
        do {
            int guess = Game::random(min, max);
            std::cout << guess << "?" << std::endl;
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
