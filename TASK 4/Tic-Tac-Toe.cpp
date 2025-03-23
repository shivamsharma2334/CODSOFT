#include <iostream>
#include <vector>
using namespace std;

class TicTacToe {
private:
    vector<vector<char>> board;  // 3x3 game board
    char currentPlayer;  // Current player's symbol ('X' or 'O')
    int turns;  // Counter to track the number of turns played

public:
    // Constructor to initialize the board and the first player
    TicTacToe() {
        board = vector<vector<char>>(3, vector<char>(3, ' '));  // 3x3 grid filled with spaces
        currentPlayer = 'X';  // Player 'X' starts the game
        turns = 0;  // No moves played yet
    }

    // Function to display the game board
    void displayBoard() {
        cout << "\nCurrent Board:\n";
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << " " << board[i][j] << " ";
                if (j < 2) cout << "|";
            }
            cout << endl;
            if (i < 2) cout << "---|---|---\n";
        }
        cout << endl;
    }

    // Function to switch players
    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    // Function to prompt the current player for input and update the board
    bool playerMove() {
        int row, col;
        cout << "Player " << currentPlayer << ", enter your move (row and column: 1-3): ";
        cin >> row >> col;
        row--; col--;  // Convert to 0-based index

        // Check for valid move
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
            cout << "Invalid move, try again.\n";
            return false;
        }

        // Update the board with the current player's move
        board[row][col] = currentPlayer;
        turns++;
        return true;
    }

    // Function to check if a player has won
    bool checkWin() {
        // Check rows, columns, and diagonals
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) {
                return true;  // Row win
            }
            if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer) {
                return true;  // Column win
            }
        }

        // Diagonal wins
        if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) {
            return true;
        }
        if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer) {
            return true;
        }

        return false;
    }

    // Function to check if the game is a draw
    bool checkDraw() {
        return turns == 9;  // If all 9 cells are filled, it's a draw
    }

    // Function to reset the game
    void resetGame() {
        board = vector<vector<char>>(3, vector<char>(3, ' '));  // Reset the board
        turns = 0;  // Reset the number of turns
    }

    // Function to play a game
    void playGame() {
        while (true) {
            displayBoard();  // Display the current state of the board

            // Get the current player's move
            while (!playerMove()) {}

            // Check if the current player has won
            if (checkWin()) {
                displayBoard();
                cout << "Player " << currentPlayer << " wins!\n";
                break;
            }

            // Check if it's a draw
            if (checkDraw()) {
                displayBoard();
                cout << "It's a draw!\n";
                break;
            }

            // Switch to the other player for the next turn
            switchPlayer();
        }
    }
};

int main() {
    TicTacToe game;

    while (true) {
        game.playGame();  // Play a game

        // Ask if the players want to play again
        char playAgain;
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
        if (playAgain != 'y' && playAgain != 'Y') {
            cout << "Thanks for playing! Goodbye!\n";
            break;  // Exit the game
        }

        game.resetGame();  // Reset the game board for a new round
    }

    return 0;
}
