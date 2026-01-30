#include <bits/stdc++.h>
using namespace std;

class User {
public:
    int id;
    User(int i) : id(i) {}
};

class Board {
private:
    vector<vector<int>> b;

public:
    Board() {
        b.assign(3, vector<int>(3, -1));
    }

    bool place(int pos, bool isone) {
        if (pos < 0 || pos >= 9) {
            cout << "Invalid position. Enter value from 0 to 8.\n";
            return false;
        }

        int i = pos / 3;
        int j = pos % 3;

        if (b[i][j] != -1) {
            cout << "Cell already taken. Try another.\n";
            return false;
        }

        b[i][j] = isone ? 1 : 0;
        return true;
    }

    bool check(bool isone) {
        int t = isone ? 1 : 0;

        // rows
        for (int i = 0; i < 3; i++) {
            if (b[i][0] == t && b[i][1] == t && b[i][2] == t)
                return true;
        }

        // columns
        for (int j = 0; j < 3; j++) {
            if (b[0][j] == t && b[1][j] == t && b[2][j] == t)
                return true;
        }

        // diagonals
        if (b[0][0] == t && b[1][1] == t && b[2][2] == t)
            return true;

        if (b[0][2] == t && b[1][1] == t && b[2][0] == t)
            return true;

        return false;
    }

    bool isFull() {
        for (auto &row : b)
            for (int cell : row)
                if (cell == -1)
                    return false;
        return true;
    }

    void display() {
        cout << "\nBoard:\n";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (b[i][j] == -1) cout << ". ";
                else if (b[i][j] == 1) cout << "X ";
                else cout << "O ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
};

class UI {
private:
    Board &b;
    User &u1;
    User &u2;

public:
    UI(Board &board, User &one, User &two)
        : b(board), u1(one), u2(two) {}

    void start() {
        bool isone = true;

        while (true) {
            b.display();

            int id = isone ? u1.id : u2.id;
            cout << "Player " << id << " turn (0-8): ";

            int pos;
            cin >> pos;

            while (!b.place(pos, isone)) {
                cin >> pos;
            }

            if (b.check(isone)) {
                b.display();
                cout << "Player " << id << " wins!\n";
                break;
            }

            if (b.isFull()) {
                b.display();
                cout << "Game Draw!\n";
                break;
            }

            isone = !isone;
        }
    }
};

int main() {
    Board board;
    User u1(1);
    User u2(2);

    UI game(board, u1, u2);
    game.start();

    return 0;
}
