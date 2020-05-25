#include "./game_number_guessing.h"
#include <limits>

Game::Game() : _number(random()) {
}

Game::Game(const uint number) : _number(number) {
}

uint
Game::random() {
    srand(clock());
    return rand() % Game::MAX_NUMBER;
}

uint
Game::random(const uint min, const uint max) {
    if (max <= min) {
        return min;
    }
    srand(clock());
    return min + (rand() % (max - min));
}

void
Game::_cout() const {
    std::cout << std::endl;
}

void
Game::_cout(const std::string& msg, const bool endl) const {
    std::cout << msg;
    if (endl) {
        std::cout << std::endl;
    }
}

void
Game::_msg_answer_correct() const {
    _cout("correct, you won!");
}

void
Game::_msg_game_over() const {
    _cout("game is over, answer was " + std::to_string(_number) + ".");
}

void
Game::_msg_answer_range() const {
    if (_min != _max) {
        _cout("guess the number, it'd be between "
              + std::to_string(_min) + " and " + std::to_string(_max) + ".");
    } else {
        _cout("it seems answer would be " + std::to_string(_min));
    }
}

void
Game::_msg_answer_too_low() const {
    _cout("too low, ", false);
}

void
Game::_msg_answer_too_high() const {
    _cout("too high, ", false);
}

void
Game::_msg_try_again() const {
    if (_guesses_left > 1) {
        _cout(std::to_string(_guesses_left) + " more guesses.");

    } else {
        _cout("one last guess?");
    }
}

const uint
Game::_get_num() const {
    uint input_num;
    while (true) {
        if (std::cin >> input_num) {
            return input_num;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        _cout("invalid input, please try again.");
    }
}

const bool
Game::game_is_over() const {
    return _guesses_left <= 0 || _won == true;
}

const bool
Game::player_won() const {
    return _won;
}

const int8_t
Game::check_answer(const uint input_num) {
    if (!game_is_over()) {
        --_guesses_left;

        if (input_num == _number) {
            _guesses_left = -1;
            _won = true;
            return 0;
        }

        return input_num < _number ? 1 : 2;
    }

    return -1;
}

const bool
Game::play() {
    uint input_num;
    while (!game_is_over()) {
        _msg_answer_range();
        input_num = _get_num();
        _cout();

        switch (check_answer(input_num)) {
            case 0:
                _msg_answer_correct();
                return true;

            case 1:
                _msg_answer_too_low();
                if (input_num >= _min) {
                    _min = input_num + 1;
                }
                break;

            case 2:
                _msg_answer_too_high();
                if (input_num <= _max) {
                    _max = input_num - 1;
                }
                break;
        }
        if (!game_is_over()) {
            _msg_try_again();
            continue;
        }
        break;
    }
    _msg_game_over();
    return false;
}

int main() {

    bool won = false;
    uint game_no = 0;
    while (true) {
        Game game;

        // clear screen
        std::cout << "\033[2J\033[1;1H";
        std::cout << "#########################################################"
                     "#######################" << std::endl;
        std::cout << "game " << ++game_no << std::endl << std::endl;
        game.play();
        if (game.player_won()) {
            break;
        }
        std::cout << "press enter to continue..." << std::endl;
        std::cin.get();
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
}

// alternate random function
// #include <random>

// uint
// Game::random() {
//     std::random_device rand_dev;

//     std::default_random_engine
//         rand_gen(rand_dev());

//     std::uniform_int_distribution<uint>
//         rand_dist(0, Game::MAX_NUMBER);

//     return rand_dist(rand_gen);
// }

