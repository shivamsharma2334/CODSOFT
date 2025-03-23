#include <iostream>
#include <random>
#include <limits>

class GuessingGame {
private:
    int targetNumber;
    std::uniform_int_distribution<> distribution;
    std::mt19937 generator;

public:
    GuessingGame() : distribution(1, 100) {
        std::random_device rd;
        generator = std::mt19937(rd());
        targetNumber = distribution(generator);
    }

    enum class GuessResult { TooHigh, TooLow, Correct };

    GuessResult checkGuess(int guess) const {
        if (guess > targetNumber) return GuessResult::TooHigh;
        if (guess < targetNumber) return GuessResult::TooLow;
        return GuessResult::Correct;
    }

    void play() const {
        int guess;
        while (true) {
            std::cout << "Enter your guess (1-100): ";
            std::cin >> guess;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number.\n";
                continue;
            }

            switch (checkGuess(guess)) {
                case GuessResult::Correct:
                    std::cout << "Congratulations! You guessed the correct number.\n";
                    return;
                case GuessResult::TooHigh:
                    std::cout << "Too high! Try again.\n";
                    break;
                case GuessResult::TooLow:
                    std::cout << "Too low! Try again.\n";
                    break;
            }
        }
    }
};

int main() {
	std::cout << "Welcome to the Number Guessing Game!" <<std:: endl;
    GuessingGame game;
    game.play();
    return 0;
}
