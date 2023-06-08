#include <iostream>
#include <vector>

using namespace std;

enum class Player { None, X, O };

class TicTacToe {
private:
    vector<vector<Player>> board;
    Player currentPlayer;

public:
    TicTacToe() : board(3, vector<Player>(3, Player::None)), currentPlayer(Player::X) {}

    void play() {
        bool gameover = false;
        Player winner = Player::None;

        while (!gameover) {
            displayBoard();

            if (isBoardFull()) {
                gameover = true;
                cout << "It's a tie!" << endl;
                break;
            }

            int row, col;
            cout << "Player " << playerToString(currentPlayer) << ", enter your move (row and column): ";
            cin >> row >> col;

            if (isValidMove(row, col)) {
                makeMove(row, col);
                winner = checkWinner();
                if (winner != Player::None) {
                    gameover = true;
                    cout << "Player " << playerToString(winner) << " wins!" << endl;
                }
                switchPlayer();
            } else {
                cout << "Invalid move! Try again." << endl;
            }
        }
    }

private:
    void displayBoard() const {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << " " << playerToString(board[i][j]) << " ";
                if (j < 2)
                    cout << "|";
            }
            cout << endl;
            if (i < 2)
                cout << "---+---+---" << endl;
        }
    }

    bool isValidMove(int row, int col) const {
        if (row < 0 || row >= 3 || col < 0 || col >= 3)
            return false;
        if (board[row][col] != Player::None)
            return false;
        return true;
    }

    void makeMove(int row, int col) {
        board[row][col] = currentPlayer;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
    }

    Player checkWinner() const {
        // Check rows
        for (int i = 0; i < 3; i++) {
            if (board[i][0] != Player::None && board[i][0] == board[i][1] && board[i][0] == board[i][2])
                return board[i][0];
        }

        // Check columns
        for (int j = 0; j < 3; j++) {
            if (board[0][j] != Player::None && board[0][j] == board[1][j] && board[0][j] == board[2][j])
                return board[0][j];
        }

        // Check diagonals
        if (board[0][0] != Player::None && board[0][0] == board[1][1] && board[0][0] == board[2][2])
            return board[0][0];

        if (board[0][2] != Player::None && board[0][2] == board[1][1] && board[0][2] == board[2][0])
            return board[0][2];

        return Player::None;
    }

    bool isBoardFull() const {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == Player::None)
                    return false;
            }
        }
        return true;
    }

    string playerToString(Player player) const {
        if (player == Player::X)
            return "X";
        if (player == Player::O)
            return "O";
        return " ";
    }
};

int main() {
    TicTacToe game;
    game.play();

    return 0;
}
