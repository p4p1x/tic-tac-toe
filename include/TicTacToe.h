#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream>
#include <vector>

class TicTacToe {
private:
    const char EMPTY = ' ';
    const char HUMAN = 'O';
    const char AI = 'X';

    int board_size;
    int win_length;
    int max_depth = 7;
    std::vector<std::vector<char>> board;

public:
    TicTacToe(int boardSize, int winLength);
    void playGame();
    void initializeBoard();
    bool isMoveValid(int row, int col);
    void makeMove(int row, int col, char player);
    bool checkWin(int row, int col, char player);
    bool isBoardFull();
    char checkWinner();
    int minmax(int depth, int alpha, int beta, bool isMaximizing);
    std::pair<int, int> findBestMove();
    void printBoard();
    int evaluateBoard();
};
#endif  // TICTACTOE_H
