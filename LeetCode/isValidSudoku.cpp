#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool isValidBlock(vector<vector<string>>& board, 
        int start_i, int end_i, int start_j, int end_j) {
        unordered_set<int> s;
        for (int i = start_i; i < end_i; i++) {
            for (int j = start_j; j < end_j; j++) {
                char b = board[i][j][0];
                if (b != '.') {
                    if (!s.insert(b).second) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool isValidSudoku(vector<vector<string>>& board) {
        // BLOCKS
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (!isValidBlock(board, 3 * i, 3 * i + 3, 3 * j, 3 * j + 3))
                    return false;
            }
        }
        // ROWS
        for (int i = 0; i < 9; i++) {
            if (!isValidBlock(board, i, i + 1, 0, 9))
                return false;
        }
        // COLS
        for (int j = 0; j < 9; j++) {
            if (!isValidBlock(board, 0, 9, j, j + 1))
                return false;
        }
        return true;
    }
};

int main() {
    vector< vector<string>> board =
    { {"8","3",".",".","7",".",".",".","."},
      {"6",".",".","1","9","5",".",".","."},
      {".","9","8",".",".",".",".","6","."},
      {"8",".",".",".","6",".",".",".","3"},
      {"4",".",".","8",".","3",".",".","1"},
      {"7",".",".",".","2",".",".",".","6"},
      {".","6",".",".",".",".","2","8","."},
      {".",".",".","4","1","9",".",".","5"},
      {".",".",".",".","8",".",".","7","9"} };
    auto  s = Solution();
    bool x = s.isValidSudoku(board);
    cout << "x = " << x << endl;
    return 0;
}