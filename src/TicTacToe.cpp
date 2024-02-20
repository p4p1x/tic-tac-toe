#include "TicTacToe.h"

TicTacToe::TicTacToe(int board_size, int win_length) {
    this->board_size = board_size;
    this->win_length = win_length;
}

void TicTacToe::initializeBoard() {
    board.resize(board_size, std::vector<char>(board_size, EMPTY));
}

bool TicTacToe::isMoveValid(int row, int col) {
    return (row >= 0 && row < board_size && col >= 0 && col < board_size && board[row][col] == EMPTY);
}

void TicTacToe::makeMove(int row, int col, char player) {
    board[row][col] = player;
}

bool TicTacToe::checkWin(int row, int col, char player) {
    int count;
    // row
    count = 0;
    for (int c = 0; c < board_size; c++) {
        if (board[row][c] == player) {
            count++;
            if (count >= win_length) {
                return true;
            }
        } else {
            count = 0;
        }
    }
    // collumn
    count = 0;
    for (int r = 0; r < board_size; r++) {
        if (board[r][col] == player) {
            count++;
            if (count >= win_length) {
                return true;
            }
        } else {
            count = 0;
        }
    }
    // diagonal
    count = 0;
    int start_row = row - std::min(row, col);
    int start_col = col - std::min(row, col);
    for (int i = 0; i < board_size; i++) {
        if (start_row + i >= board_size || start_col + i >= board_size) {
            break;
        }
        if (board[start_row + i][start_col + i] == player) {
            count++;
            if (count >= win_length) {
                return true;
            }
        } else {
            count = 0;
        }
    }
    // diagonal
    count = 0;
    start_row = row - std::min(row, board_size - col - 1);
    start_col = col + std::min(row, board_size - col - 1);
    for (int i = 0; i < board_size; i++) {
        if (start_row + i >= board_size || start_col - i < 0) {
            break;
        }
        if (board[start_row + i][start_col - i] == player) {
            count++;
            if (count >= win_length) {
                return true;
            }
        } else {
            count = 0;
        }
    }
    return false;
}


bool TicTacToe::isBoardFull() {
    for (int r = 0; r < board_size; r++) {
        for (int c = 0; c < board_size; c++) {
            if (board[r][c] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

char TicTacToe::checkWinner() {
    for (int r = 0; r < board_size; r++) {
        for (int c = 0; c < board_size; c++) {
            if (board[r][c] != EMPTY && (checkWin(r, c, HUMAN) || checkWin(r, c, AI))) {
                return board[r][c];
            }
        }
    }
    if (isBoardFull()) {
        return 'T'; //remis
    }
    return EMPTY; 
}

int TicTacToe::minmax(int depth, int alpha, int beta, bool isMaximizing) {
    char result = checkWinner();
    if (result == HUMAN) {
        return -1;
    } else if (result == AI) {
        return 1;
    } else if (result == 'T') {
        return 0;
    }

    if (depth == max_depth) {
        if (isMaximizing)
            return evaluateBoard();
        else
            return -evaluateBoard();
    }

    if (isMaximizing) {
        int best_score = -1000;
        for (int row = 0; row < board_size; row++) {
            for (int col = 0; col < board_size; col++) {
                if (board[row][col] == EMPTY) {
                    board[row][col] = AI;
                    int score = minmax(depth + 1, alpha, beta, false);
                    board[row][col] = EMPTY;
                    best_score = std::max(score, best_score);
                    alpha = std::max(alpha, best_score);
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
        }
        return best_score;
    } else {
        int best_score = 1000;
        for (int row = 0; row < board_size; row++) {
            for (int col = 0; col < board_size; col++) {
                if (board[row][col] == EMPTY) {
                    board[row][col] = HUMAN;
                    int score = minmax(depth + 1, alpha, beta, true);
                    board[row][col] = EMPTY;
                    best_score = std::min(score, best_score);
                    beta = std::min(beta, best_score);
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
        }
        return best_score;
    }
}

std::pair<int, int> TicTacToe::findBestMove() {
    int best_score = -1000;
    std::pair<int, int> best_move;

    for (int row = 0; row < board_size; row++) {
        for (int col = 0; col < board_size; col++) {
            if (board[row][col] == EMPTY) {
                board[row][col] = AI;
                int score = minmax(0, -1000, 1000, false);
                board[row][col] = EMPTY;
                if (score > best_score) {
                    best_score = score;
                    best_move = std::make_pair(row, col);
                }
            }
        }
    }
    return best_move;
}

void TicTacToe::printBoard() {
    for (int r = 0; r < board_size; r++) {
        for (int c = 0; c < board_size; c++) {
            std::cout << board[r][c];
            if (c != board_size - 1) {
                std::cout << "  | ";
            }
        }
        std::cout << std::endl;
        if (r != board_size - 1) {
            for (int i = 0; i < board_size; i++) {
                std::cout << "----";
            }
            std::cout << std::endl;
        }
    }
}

void TicTacToe::playGame() {
    initializeBoard();

    std::cout << "You play as 'O'. Type row and collumn  (0 to " << board_size - 1 << ")." << std::endl;

    char current_player = HUMAN;

    while (true) {
        printBoard();

        if (current_player == HUMAN) {
            int row, col;
            std::cout << "Move: ";
            std::cin >> row >> col;

            if (isMoveValid(row, col)) {
                makeMove(row, col, current_player);
                if (checkWin(row, col, current_player)) {
                    printBoard();
                    std::cout << "You won!" << std::endl;
                    return;
                }
                else if (isBoardFull()) {
                    printBoard();
                    std::cout << "Tie!" << std::endl;
                    return;
                }
                current_player = AI;
            }
            else {
                std::cout << "Incorrect move, try again:" << std::endl;
            }
        }
        else {
            std::pair<int, int> move = findBestMove();
            makeMove(move.first, move.second, current_player);

            if (checkWin(move.first, move.second, current_player)) {
                printBoard();
                std::cout << "You lost! AI won." << std::endl;
                return;
            }
            else if (isBoardFull()) {
                printBoard();
                std::cout << "Tie!" << std::endl;
                return;
            }
            current_player = HUMAN;
        }
    }
}

int TicTacToe::evaluateBoard() {
    int score = 0;

    for (int i = 0; i < board_size; i++) {
        int ai_row_count = 0, ai_col_count = 0;
        int human_row_count = 0, human_col_count = 0;

        for (int j = 0; j < board_size; j++) {
            //rows
            if (board[i][j] == AI)
                ai_row_count++;
            else if (board[i][j] == HUMAN)
                human_row_count++;
            //collumns
            if (board[j][i] == AI)
                ai_col_count++;
            else if (board[j][i] == HUMAN)
                human_col_count++;
        }
        //rows
        if (ai_row_count == win_length - 1 && human_row_count == 0)
            score += 100;
        else if (human_row_count == win_length - 1 && ai_row_count == 0)
            score -= 100;
        //collumns
        if (ai_col_count == win_length - 1 && human_col_count == 0)
            score += 100;
        else if (human_col_count == win_length - 1 && ai_col_count == 0)
            score -= 100;
    }

    int ai_diagonal_count = 0, ai_anti_diagonal_count = 0;
    int human_diagonal_count = 0, human_anti_diagonal_count = 0;

    for (int i = 0; i < board_size; i++) {
        //diagonal
        if (board[i][i] == AI)
            ai_diagonal_count++;
        else if (board[i][i] == HUMAN)
            human_diagonal_count++;
        //anti-diagonal
        if (board[i][board_size - i - 1] == AI)
            ai_anti_diagonal_count++;
        else if (board[i][board_size - i - 1] == HUMAN)
            human_anti_diagonal_count++;
    }
    //diagonal
    if (ai_diagonal_count == win_length - 1 && human_diagonal_count == 0)
        score += 100;
    else if (human_diagonal_count == win_length - 1 && ai_diagonal_count == 0)
        score -= 100;
    //anti-diagonal
    if (ai_anti_diagonal_count == win_length - 1 && human_anti_diagonal_count == 0)
        score += 100;
    else if (human_anti_diagonal_count == win_length - 1 && ai_anti_diagonal_count == 0)
        score -= 100;

    return score;
}
