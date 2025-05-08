#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <cmath>
#include <sstream>

using namespace std;

const int N = 3; // Size of the puzzle
vector<vector<int>> goal(N, vector<int>(N)); // Goal state

// Directions for moving the empty space
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
string direction[] = {"Up", "Down", "Left", "Right"};

// A structure to represent the puzzle state
struct Puzzle {
    vector<vector<int>> state;  // Current puzzle configuration
    int emptyX, emptyY;         // Position of the empty space
    int g, h;                   // Cost to reach this (current) state and heuristic (Manhattan distance)

    // Function to calculate total cost (f = g + h)
    int f(){
        return g + h;
    }

    // Check if the current state is the goal state
    bool isGoal() {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if(state[i][j] != goal[i][j]) return false;
        return true;
    }

    // Convert the current state to a string for easy hashing/comparison
    string stateToString() {
        string s;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                s += to_string(state[i][j]) + " ";
            }
        }
        return s;
    }
};

// Comparator for priority_queue (min-heap based on f value)
struct ComparePuzzle {
    bool operator()(Puzzle& a, Puzzle& b) {
        return a.f() > b.f(); // smaller f has higher priority
    }
};

// Print the puzzle state
void printPuzzle(vector<vector<int>>& puzzle) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cout << puzzle[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Calculate the Manhattan distance (heuristic)
int calculateHeuristic(vector<vector<int>>& puzzle) {
    int h = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            int val = puzzle[i][j];
            if(val != 0) {
                for(int x = 0; x < N; x++) {
                    for(int y = 0; y < N; y++) {
                        if(goal[x][y] == val) {
                            h += abs(i - x) + abs(j - y);
                        }
                    }
                }
            }
        }
    }
    return h;
}

// Find position of 0 (empty tile)
pair<int, int> findEmptySpace(vector<vector<int>>& puzzle) {
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if (puzzle[i][j] == 0) return {i, j};
    return {-1, -1}; // Should not happen
}

// Solve using A* search
bool solvePuzzle(vector<vector<int>>& initialState) {
    priority_queue<Puzzle, vector<Puzzle>, ComparePuzzle> pq;
    unordered_set<string> visited;

    pair<int, int> emptyPos = findEmptySpace(initialState);
    Puzzle start = {initialState, emptyPos.first, emptyPos.second, 0, calculateHeuristic(initialState)};
    pq.push(start);
    visited.insert(start.stateToString());

    while(!pq.empty()) {
        Puzzle current = pq.top();
        pq.pop();

        cout << "Current state (f = " << current.f() << "):" << endl;
        printPuzzle(current.state);

        if(current.isGoal()) {
            cout << "Solution found!" << endl;
            printPuzzle(current.state);
            return true;
        }

        for(int i = 0; i < 4; i++) {
            int newX = current.emptyX + dx[i];
            int newY = current.emptyY + dy[i];

            if(newX >= 0 && newX < N && newY >= 0 && newY < N) {
                vector<vector<int>> newState = current.state;
                swap(newState[current.emptyX][current.emptyY], newState[newX][newY]);

                Puzzle nextState = {newState, newX, newY, current.g + 1, calculateHeuristic(newState)};
                string stateStr = nextState.stateToString();

                if(visited.find(stateStr) == visited.end()) {
                    pq.push(nextState);
                    visited.insert(stateStr);
                    cout << "Move " << direction[i] << " (f = " << nextState.f() << "):" << endl;
                    printPuzzle(newState);
                }
            }
        }
    }

    return false; // No solution found
}

int main() {
    cout << "Enter the goal state (3x3 grid):\n";
    for(int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> goal[i][j];

    vector<vector<int>> initial(N, vector<int>(N));
    cout << "Enter the initial state (3x3 grid):\n";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> initial[i][j];

    if(!solvePuzzle(initial)) {
        cout << "No solution found.\n";
    }

    return 0;
}

//Time Complexity: O(b^d) where b is the branching factor and d is the depth of the solution.
//Space Complexity: O(b^d) for the priority queue and visited set.