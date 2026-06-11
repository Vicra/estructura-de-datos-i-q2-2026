#include "Solution.h"
#include <iostream>
using namespace std;

int main() {
    vector<vector<int>> maze = {
        {1, 1, 1, 1, 0},
        {1, 0, 1, 1, 1},
        {1, 1, 1, 0, 1},
        {0, 1, 0, 1, 1},
        {1, 1, 1, 1, 1}
    };

    Solution sol;
    vector<string> paths = sol.ratInMaze(maze);

    if (paths.empty()) {
        cout << "No path exists\n";
    } else {
        cout << "Paths found:\n";
        for (const string& p : paths) {
            cout << p << '\n';
        }
    }

    return 0;
}
