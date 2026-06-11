#ifndef SOLUTION_H
#define SOLUTION_H

#include <string>
#include <vector>
using std::string;
using std::vector;

class Solution {
public:
    vector<string> ans;
    int n;

    void dfs(int i, int j, vector<vector<int>>& maze,
             vector<vector<int>>& vis, string path) {

        if (i == n - 1 && j == n - 1) {
            ans.push_back(path);
            return;
        }

        vis[i][j] = 1;

        // D
        if (i + 1 < n && maze[i + 1][j] == 1 && !vis[i + 1][j]) {
            dfs(i + 1, j, maze, vis, path + 'D');
        }

        // L
        if (j - 1 >= 0 && maze[i][j - 1] == 1 && !vis[i][j - 1]) {
            dfs(i, j - 1, maze, vis, path + 'L');
        }

        // R
        if (j + 1 < n && maze[i][j + 1] == 1 && !vis[i][j + 1]) {
            dfs(i, j + 1, maze, vis, path + 'R');
        }

        // U
        if (i - 1 >= 0 && maze[i - 1][j] == 1 && !vis[i - 1][j]) {
            dfs(i - 1, j, maze, vis, path + 'U');
        }

        vis[i][j] = 0; // backtrack
    }

    vector<string> ratInMaze(vector<vector<int>>& maze) {
        n = maze.size();
        ans.clear();

        if (maze[0][0] == 0 || maze[n - 1][n - 1] == 0)
            return ans;

        vector<vector<int>> vis(n, vector<int>(n, 0));

        dfs(0, 0, maze, vis, "");

        return ans;
    }
};
#endif // SOLUTION_H
