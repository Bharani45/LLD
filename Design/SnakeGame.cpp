#include <bits/stdc++.h>
using namespace std;

/* ---------- Dice ---------- */
class Dice {
public:
    int roll() {
        return rand() % 6 + 1;
    }
};

/* ---------- Player ---------- */
class Player {
public:
    int id;
    int position;

    Player(int id) : id(id), position(0) {}
};

/* ---------- Board ---------- */
class Board {
    unordered_map<int, int> jumps;
    static const int BOARD_SIZE = 100;

public:
    Board() {
        // Ladders
        jumps[3] = 23;
        jumps[32] = 82;
        jumps[77] = 98;

        // Snakes
        jumps[43] = 24;
        jumps[25] = 9;
    }

    int getNextPosition(int curr, int diceValue) {
        if (curr + diceValue >= BOARD_SIZE)
            return curr;  // stay at same position

        int next = curr + diceValue;

        if (jumps.count(next)) {
            if (jumps[next] > next)
                cout << "Ladder! ";
            else
                cout << "Snake! ";
            return jumps[next];
        }
        return next;
    }
};

/* ---------- Game ---------- */
class Game {
    Board board;
    Dice dice;
    vector<Player> players;
    int currentTurn;

public:
    Game(int playerCount) : currentTurn(0) {
        for (int i = 1; i <= playerCount; i++) {
            players.emplace_back(i);
        }
    }

    void start() {
        while (true) {
            Player &p = players[currentTurn];
            int diceValue = dice.roll();

            cout << "Player " << p.id << " rolls " << diceValue << " -> ";

            p.position = board.getNextPosition(p.position, diceValue);
            cout << "Position: " << p.position << endl;

            if (p.position == 99) {
                cout << "\n🏆 Player " << p.id << " wins the game!\n";
                break;
            }

            currentTurn = (currentTurn + 1) % players.size();
        }
    }
};

/* ---------- Main ---------- */
int main() {
    srand(time(0));

    int playerCount = 3;
    Game game(playerCount);
    game.start();

    return 0;
}
