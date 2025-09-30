#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void setZeros(vector<vector<int>>& a) {
        int m = a.size(), n = a[0].size();
        bool is_row_zero = false, is_col_zero = false;

        // Check col for zero
        for (int i = 0; i < m; i++) {
            if (a[i][0] == 0)
                is_col_zero = true;
        }
        // Check row for zero
        for (int i = 0; i < n; i++) {
            if (a[0][i] == 0)
                is_row_zero = true;
        }

        // set the row and col markers
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (a[i][j] == 0)
                    a[0][j] = a[i][0] = 0;
            }
        }

        // set the row to all zeros
        for (int i = 1; i < m; i++) {
            if (a[i][0] == 0)
                for (int j = 1; j < n; j++)
                    a[i][j] = 0;
        }
        // set the col to all zeros
        for (int j = 1; j < n; j++) {
            if (a[0][j] == 0)
                for (int i = 1; i < m; i++)
                    a[i][j] = 0;
        }

        // set first row to zeros if needed
        if (is_row_zero) {
            for (int j = 0; j < n; j++) {
                a[0][j] = 0;
            }
        }
        // set first col to zeros if needed
        if (is_col_zero) {
            for (int i = 0; i < m; i++) {
                a[i][0] = 0;
            }
        }
    }
};

int main() {
    vector< vector< int>> matrix = { {1,1,1},{1,0,1},{1,1,1} };
    auto s = Solution();
    s.setZeros(matrix);
    cout << "s = " << endl;
    for (int i = 0; i < matrix.size(); i++) {
        cout << "[ ";
        for (int j = 0; j < matrix[0].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "]\n";
    }
}