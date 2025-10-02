#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool canConstruct(string ran, string mag) {
        int n = ran.size(), m = mag.size();
        unordered_map<char, int> set;
        //CREATE HASH MAP FROM MAGAZINE
        for (int i = 0; i < m; i++) {
            auto c = mag[i];
            auto it = set.find(c);
            if (it == set.end()) set[c] = 1;
            else it->second += 1;
        }
        //CHECK HASH MAP FOR RANSOM
        for (int i = 0; i < n; i++) {
            char c = ran[i];
            auto it = set.find(c);
            if (it == set.end()) return false;
            else if (it == set.end()) return false;
            else it->second -= 1;
        }
    }
};

int main() {
    string mag = "aab", ran = "aa";
    auto s = Solution();
    bool ans = s.canConstruct(ran, mag);
    cout << "Can Canstructuct Ransome: ";
    cout << string((ans) ? "true" : "false") << endl;
    return 0;
}