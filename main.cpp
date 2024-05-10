#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<vector<string>> board {
        {"O", "O", "O", "O", "O", "O", "O"}, // 0
        {"O", "O", "O", "O", "O", "O", "O"}, // 1
        {"O", "O", "O", "O", "O", "O", "O"}, // 2
        {"O", "O", "O", "O", "O", "O", "O"}, // 3
        {"O", "O", "O", "O", "O", "O", "O"}, // 4
        {"O", "O", "O", "O", "O", "O", "O"}  // 5
        //0    1    2    3    4    5    6
};

string turn = "R";

void showBoard() {
    for (int x = 0; x < 6; x++) {
        for (int y = 0; y < 7; y++) {
            cout << "| " << board[x][y] << " ";
        }

        cout << "|" << endl;
        // cout << "-----------------------------" << endl;
    }

}

bool digit(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (!isdigit(s[i]) == false) {
            return false;
        }
    }

    return true;
}

bool freeSpace(int x, int y, vector<vector<string>> board) {
    if (board[x][y] == "O") {
        return true;
    } else {
        return false;
    }
} 

int placeChip(vector<vector<string>> b, int c) {
    for (int i = 5; i > -1; i--) {
        if (freeSpace(i, c, b)) {
            board[i][c] = turn;
            return 0;
        }
    }

    return -1;
}

void switchTurn() {
    if (turn == "R") {
        turn = "Y";
    } else {
        turn = "R";
    }
}

string checkWin(vector<vector<string>> board) {
    for (int r = 5; r > -1; r--) {
        for (int c = 0; c < 7; c++) {
            // Horizontal
            if (c < 4) {
                if (board[r][c] != "O" && board[r][c] == board[r][c+1] && board[r][c+1] == board[r][c+2] && board[r][c+2] == board[r][c+3]) {
                    return board[r][c];
                }
            }

            // Vertical
            if (r > 2) {
                if (board[r][c] != "O" && board[r][c] == board[r-1][c] && board[r-1][c] == board[r-2][c] && board[r-2][c] == board[r-3][c]) {
                    return board[r][c];
                }
            }

            // Diagonal (left)
            if (c < 4 && r > 2) {
                if (board[r][c] != "O" && board[r][c] == board[r-1][c+1] && board[r-1][c+1] == board[r-2][c+2] && board[r-2][c+2] == board[r-3][c+3]) {
                    return board[r][c];
                }
            }

            // Diagonal (right)
            if (c > 2 && r > 2) {
                if (board[r][c] != "O" && board[r][c] == board[r-1][c-1] && board[r-1][c-1] == board[r-2][c-2] && board[r-2][c-2] == board[r-3][c-3]) {
                    return board[r][c];
                }
            }
        }
    }

    return "";
}

int minimax(vector<vector<string>> b, int depth, bool max) {
    string win = checkWin(b);
    if (win != "") {
        if (win == "Y") {
            return 1;
        } else {
            return -1;
        }
    }

    if (depth > 5) {
        return 0;
    }
    if (max) {
        int score = 0;
        int bestScore = -1000;
        for (int c = 0; c < 7; c++) {
            for (int r = 5; r > -1; r--) {
                if (freeSpace(r, c, board)) {
                    board[r][c] = "Y";
                    score = minimax(board, depth+1, false);
                    board[r][c] = "O";
                    if (score > bestScore) {
                        bestScore = score;
                    }

                    break;
                } else {
                    continue;
                }
            }
        }

        return bestScore;
    } else {
        int score = 0;
        int bestScore = 1000;
        for (int c = 0; c < 7; c++) {
            for (int r = 5; r > -1; r--) {
                if (freeSpace(r, c, board)) {
                    board[r][c] = "R";
                    score = minimax(board, depth+1, true);
                    board[r][c] = "O";
                    if (score < bestScore) {
                        bestScore = score;
                    }

                    break;
                } else {
                    continue;
                }
            }
        }

        return bestScore;
    }
}

void aiTurn() {
    int score = 0;
    int bestScore = -1000;
    int bestMove = 4;
    for (int c = 0; c < 7; c++) {
        for (int r = 5; r > -1; r--) {
            if (freeSpace(r, c, board)) {
                board[r][c] = "Y";
                score = minimax(board, 0, false);
                board[r][c] = "O";
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = c;
                }

                break;
            } else {
                continue;
            }
        }
    }

    placeChip(board, bestMove);
}

void playerTurn() {
    string c;
    system("clear");
    showBoard();
    cout << "\nSelect a Column: ";
    while (true) {
        cin >> c;
        if (digit(c)) {
            system("clear");
            showBoard();
            cout << "\nSorry, pelase select a different column..." << endl;
            cout << "Select a Column: ";
            continue;
        } else if (stoi(c) > 7 || stoi(c) < 1) {
            system("clear");
            showBoard();
            cout << "\nSorry, pelase select a different column..." << endl;
            cout << "Select a Column: ";
            continue;
        }

        if (placeChip(board, stoi(c)-1) == -1) {
            system("clear");
            showBoard();
            cout << "\nSorry, pelase select a different column..." << endl;
            cout << "Select a Column: ";
            continue;
        } else {
            return;
        }
    }
}

int main() {
    while (true) {
        if (turn == "R") {
            playerTurn();
        } else {
            aiTurn();
        }

        switchTurn();

        string win = checkWin(board);
        if (win != "") {
            if (win == "R") {
                cout << "Red wins!" << endl;
                exit(0);
            } else {
                cout << "Yellow wins!" << endl;
                exit(0);
            }
        }
    }
    
    return 0;
}