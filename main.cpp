#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <list>

using namespace std;

vector<vector<int>> matrix;

void dfs(int start, vector<bool> &visited) {
    visited[start] = true;

    for(int i = 0; i < matrix[start].size(); ++i) {
        if(matrix[start][i] == 1 && (!visited[i])) {
            dfs(i, visited);
        }
    }
}

void accesible(int numberOfStates, int numberOfSymbols, int numberofSource) {
    matrix = vector<vector<int>>(numberOfStates, vector<int>(numberOfStates, 0));
    vector<bool> visited(numberOfStates, false);
    for(int i = 0; i < numberOfStates; ++i) {
        for(int j =0; j < numberOfSymbols; ++j) {
            int value0;
            cin >> value0;
            matrix[i][value0] = 1;
        }
    }
    int data;
    for(int i = 0 ;i < numberofSource; ++i) {
        cin >> data;
        if(!visited[data]) {
            dfs(data, visited);
        }
    }
    for(int i = 0; i < numberOfStates; ++i) {
        if(visited[i]) {
            cout << i << "\n";
        }
    }
}

bool BFS_sync(int first, int second,
              vector<pair<int, int>>& visited, vector<int>& symbols, int numberOfSymbols) {

    visited.push_back({first, second});

    if (first == second) {
        return true;
    }

    for (int i = 0; i < numberOfSymbols; i++) {
        int first_neigh = matrix[first][i];
        int second_neigh = matrix[second][i];
        int data_1 = 0;
        for(auto& data: visited) {
            if(data.first == first_neigh && data.second == second_neigh) {
                data_1 = 1;
                break;
            }
        }
        if(data_1 == 1) {
            continue;
        }
        symbols.push_back(i);
        if (BFS_sync(first_neigh, second_neigh, visited, symbols, numberOfSymbols)) {
            return true;
        }
        symbols.pop_back();
    }
    return false;
}

void synchronize(int numberOfStates, int numberOfSymbols, int numberofSource) {
    matrix = vector<vector<int>>(numberOfStates);
    set<int> states;

    for (int i = 0; i < numberOfStates; ++i) {
        for (int j = 0; j < numberOfSymbols; ++j) {
            int state;
            cin >> state;
            matrix[i].push_back(state);
        }
    }

    for (int i = 0; i < numberofSource; ++i) {
        int state;
        cin >> state;
        states.insert(state);
    }

    if (numberofSource == 0) {
        for (int i = 0; i < numberOfStates; ++i) {
            states.insert(i);
        }
    }

    while (states.size() > 1) {
        vector<int> word;
        vector<pair<int, int>> visited;

        int firstState = *(states.begin());
        states.erase(firstState);
        int second = *(states.begin());

        BFS_sync(firstState, second, visited, word, numberOfSymbols);

        for(int i = 0 ; i < word.size(); ++i) {
            set<int> update;
            for(auto& state: states) {
                update.insert(matrix[state][word[i]]);
            }
            states = update;
        }

        for(int i = 0; i < word.size(); ++i) {
            cout << word[i] << " ";
        }
        cout << "\n";
    }
}

int main(int argc, char *args[]) {
    int numberOfStates;
    int numberOfSymbols;
    int numberOfSource;

    cin >> numberOfStates >> numberOfSymbols >> numberOfSource;
    if(strcmp(args[1], "accessible") == 0) {
        accesible(numberOfStates, numberOfSymbols, numberOfSource);
    } else if(strcmp(args[1], "synchronize") == 0) {
        synchronize(numberOfStates, numberOfSymbols, numberOfSource);
    }
    return 0;
}
