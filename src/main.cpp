#include "TicTacToe.h"

int main() {
    int board_size, win_length;
    std::cout << "Size of the board: ";
    std::cin >> board_size;
    std::cout << std::endl;
    std::cout << "Length of winning characters: ";
    std::cin >> win_length;

    TicTacToe game(board_size, win_length);
    game.playGame();

    return 0;
}
