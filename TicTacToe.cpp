
#include <iostream>
#include <ctime>

// Good practice to instntiate function in th ebegginingg and code them at the end
void drawBoard(char *spaces);
void playerMove(char *spaces, char player);
void computerMove(char *spaces, char computer);
bool checkWinner(char *spaces, char player, char computer);
bool checkTie(char *spaces);

int main() {
    // Initialize the game board with empty spaces
    char spaces[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    char player = 'X'; // Player's marker
    char computer = 'O'; // Computer's marker
    bool running = true; // Game running flag

    // Draw the initial game board
    drawBoard(spaces);

    // Main game loop
    while (running) {
        // Player's move
        playerMove(spaces, player);
        drawBoard(spaces);
        // Check if player wins or if it's a tie
        if (checkWinner(spaces, player, computer)) {
            running = false;
            break;
        } else if (checkTie(spaces)) {
            running = false;
            break;
        }

        // Computer's move
        computerMove(spaces, computer);
        drawBoard(spaces);
        // Check if computer wins or if it's a tie
        if (checkWinner(spaces, player, computer)) {
            running = false;
            break;
        } else if (checkTie(spaces)) {
            running = false;
            break;
        }
    }

    // End of game message
    std::cout << "Thanks for playing!\n";

    return 0;
}

// Function to draw the game board
void drawBoard(char *spaces) {
    std::cout << '\n';
    std::cout << "     |     |     " << "\n";
    std::cout << "   " << spaces[0] << " |  " << spaces[1] << "  |  " << spaces[2] << "   " << "\n";
    std::cout << "_____|_____|_____" << "\n";
    std::cout << "     |     |     " << "\n";
    std::cout << "   " << spaces[3] << " |  " << spaces[4] << "  |  " << spaces[5] << "   " << "\n";
    std::cout << "_____|_____|_____" << "\n";
    std::cout << "     |     |     " << "\n";
    std::cout << "   " << spaces[6] << " |  " << spaces[7] << "  |  " << spaces[8] << "   " << "\n";
    std::cout << '\n';
}

// Function to handle player's move
void playerMove(char *spaces, char player) {
    int number;
    do {
        std::cout << "Enter a spot to place a marker (1-9): ";
        std::cin >> number;
        number--;
        // Check if the chosen spot is empty
        if (spaces[number] == ' ') {
            spaces[number] = player;
            break;
        }
    } while (number < 0 || number > 8);
}

// Function to handle computer's move
void computerMove(char *spaces, char computer) {
    int number;
    srand(time(0)); // Seed the random number generator
    while (true) {
        number = rand() % 9; // Generate a random number between 0 and 8
        // Check if the chosen spot is empty
        if (spaces[number] == ' ') {
            spaces[number] = computer;
            break;
        }
    }
}

// Function to check if there is a winner
bool checkWinner(char *spaces, char player, char computer) {
    // Check all possible winning combinations
    if ((spaces[0] != ' ') && (spaces[0] == spaces[1]) && (spaces[1] == spaces[2])) {
        spaces[0] == player ? std::cout << "YOU WIN!\n" : std::cout << "YOU LOSE!\n";
    } else if ((spaces[3] != ' ') && (spaces[3] == spaces[4]) && (spaces[4] == spaces[5])) {
        spaces[3] == player ? std::cout << "YOU WIN!\n" : std::cout << "YOU LOSE!\n";
    } else if ((spaces[6] != ' ') && (spaces[6] == spaces[7]) && (spaces[7] == spaces[8])) {
        spaces[6] == player ? std::cout << "YOU WIN!\n" : std::cout << "YOU LOSE!\n";
    } else if ((spaces[0] != ' ') && (spaces[0] == spaces[3]) && (spaces[3] == spaces[6])) {
        spaces[0] == player ? std::cout << "YOU WIN!\n" : std::cout << "YOU LOSE!\n";
    } else if ((spaces[1] != ' ') && (spaces[1] == spaces[4]) && (spaces[4] == spaces[7])) {
        spaces[1] == player ? std::cout << "YOU WIN!\n" : std::cout << "YOU LOSE!\n";
    } else if ((spaces[2] != ' ') && (spaces[2] == spaces[5]) && (spaces[5] == spaces[8])) {
        spaces[2] == player ? std::cout << "YOU WIN!\n" : std::cout << "YOU LOSE!\n";
    } else if ((spaces[0] != ' ') && (spaces[0] == spaces[4]) && (spaces[4] == spaces[8])) {
        spaces[0] == player ? std::cout << "YOU WIN!\n" : std::cout << "YOU LOSE!\n";
    } else if ((spaces[2] != ' ') && (spaces[2] == spaces[4]) && (spaces[4] == spaces[6])) {
        spaces[2] == player ? std::cout << "YOU WIN!\n" : std::cout << "YOU LOSE!\n";
    } else {
        return false;
    }
    return true;
}

// Function to check if the game is a tie
bool checkTie(char *spaces) {
    // Check if all spots are filled
    for (int i = 0; i < 9; i++) {
        if (spaces[i] == ' ') {
            return false;
        }
    }
    std::cout << "IT'S A TIE!\n";
    return true;
}
