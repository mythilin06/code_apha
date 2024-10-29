#include <iostream>
#include <vector>
#include <cmath>
#include <limits> // For std::numeric_limits

bool isSafe(const std::vector<std::vector<int>>& board, int size, int row, int col, int num) {
    int boxSize = std::sqrt(size);
    for (int x = 0; x < size; x++) {
        if (board[row][x] == num || board[x][col] == num ||
            board[row - row % boxSize + x / boxSize][col - col % boxSize + x % boxSize] == num) {
            return false;
        }
    }
    return true;
}

bool solveSudoku(std::vector<std::vector<int>>& board, int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= size; num++) {
                    if (isSafe(board, size, row, col, num)) {
                        board[row][col] = num;
                        if (solveSudoku(board, size))
                            return true;
                        board[row][col] = 0; // Backtrack
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void printBoard(const std::vector<std::vector<int>>& board, int size) {
    int boxSize = std::sqrt(size);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            std::cout << board[row][col] << " ";
            if ((col + 1) % boxSize == 0) std::cout << "| "; // Box separator
        }
        std::cout << std::endl;
        if ((row + 1) % boxSize == 0) std::cout << std::string(size * 2 + boxSize - 1, '-') << std::endl; // Row separator
    }
}

bool readPuzzle(std::vector<std::vector<int>>& board, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cin >> board[i][j];
            if (std::cin.fail() || board[i][j] < 0 || board[i][j] > size) {
                std::cin.clear(); // Clear error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                std::cout << "Invalid input. Please enter numbers between 0 and " << size << ".\n";
                return false;
            }
        }
    }
    return true;
}

int main() {
    int size;
    std::cout << "Enter the size of the Sudoku (must be a perfect square, e.g., 4, 9, 16, etc.): ";
    std::cin >> size;

    if (size < 1 || std::sqrt(size) != static_cast<int>(std::sqrt(size))) {
        std::cout << "Invalid size. Please enter a perfect square size." << std::endl;
        return 1;
    }

    std::vector<std::vector<int>> board(size, std::vector<int>(size, 0));

    std::cout << "Enter the Sudoku puzzle (use 0 for empty cells):" << std::endl;
    if (!readPuzzle(board, size)) {
        return 1;
    }

    if (solveSudoku(board, size)) {
        std::cout << "Solved Sudoku:" << std::endl;
        printBoard(board, size);
    } else {
        std::cout << "No solution exists." << std::endl;
    }

    return 0;
}