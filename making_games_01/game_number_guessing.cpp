#include "./game_number_guessing.h"
#include <limits>

Game_cout::Game_cout() : std::ostream(this) {}

int
Game_cout::overflow(int c) {
    std::cout.put(c);
    return 0;
}

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
Game::_correct_answer() {
    _cout << "correct, you won!";
}

void
Game::_game_over() {
    _cout << "Game is over, answer was " << _number << "." << std::endl;
}

int8_t
Game::guess(const uint input_num) {
    if (_tries > 0) {
        --_tries;

        if (input_num == _number) {
            _tries = -1;
            return 0;
        }

        if (_tries == 0) {
            return -1;
        }
        return input_num < _number ? 1 : 2;
    }

    return -1;
}

void
Game::_hint(const uint min, const uint max) {
    if (min == max) {
        _cout << "it seems answer would be " << min << "." << std::endl;
    } else {
        _cout << "guess the number, it'd be between " << min
              << " and " << max << std::endl;
    }
}

const uint
Game::_get_num(const uint min, const uint max) {
    uint input_num;
    while (true) {
        if (std::cin >> input_num && input_num >= min && input_num <= max) {
            return input_num;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        _cout << "invalid input, please try again." << std::endl;
    }
}

bool
Game::play() {
    uint min = 0;
    uint max = MAX_NUMBER;
    uint input_num;
    while (true) {
        _hint(min, max);
        input_num = _get_num(min, max);
        _cout << std::endl;

        switch (guess(input_num)) {
            case -1:
                _game_over();
                return false;

            case 0:
                _correct_answer();
                return true;

            case 1:
                min = input_num + 1;
                _cout << "too low, ";
                break;

            case 2:
                max = input_num - 1;
                _cout << "too high, ";
                break;
        }

        if (_tries > 1) {
            _cout << _tries << " more guesses." << std::endl;

        } else {
            _cout << "one last guess?" << std::endl;
        }
    }
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
        if (game.play()) {
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

