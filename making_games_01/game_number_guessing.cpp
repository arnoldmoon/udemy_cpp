#include "./game_number_guessing.h"

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
Game::guess(const int guess) {
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

bool
Game::play() {
    int min = 0;
    int max = MAX_NUMBER;
    int input_num;
    while (true) {
        while (true) {
            _cout << "guess the number, it's between " << min
                      << " and " << max << std::endl;
            if (std::cin >> input_num && input_num >= min && input_num <= max) {
                break;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        _cout << std::endl;

        switch (guess(input_num)) {
            case -1:
                return false;

            case 0:
                return true;

            case 1:
                min = input_num + 1;
                break;

            case 2:
                max = input_num - 1;
                break;
        }
    }
}

int main() {

    bool won = false;
    int game_no = 0;
    while (true) {
        Game game;
        std::cout << "#########################################################"
                     "#######################" << std::endl;
        std::cout << "game " << ++game_no << std::endl << std::endl;
        if (game.play()) {
            break;
        }
    }

    return 0;
}

// alternate random function
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

