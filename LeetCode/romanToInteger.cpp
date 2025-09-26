#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> tokenLevels = { "IVX", "XLC", "CDM", "MMM" };

    unordered_map<char, int> levels =
    { {'I', 0}, {'V', 0}, {'X', 1}, {'L', 1}, {'C', 2}, {'D', 2}, {'M', 3} };

    int romanToInt(string s) {
        int n = s.size();
        int num = 0;
        for (int i = 0; i < n;) {
            int level = levels[s[i]];
            string c = tokenLevels[level];
            int decimal = pow(10, level);
            if (s[i] == c[0]) num += 1 * decimal;// I=1
            else if (s[i] == c[1]) num += 5 * decimal;// V=5

            if (i < n) i++; else break;

            if (s[i] == c[0]) num += 1 * decimal;// II=2 OR VI=6
            else if (s[i] == c[1]) num += 3 * decimal;// IV=4
            else if (s[i] == c[2])num += 8 * decimal;// IX=9
            else continue;

            if (i < n)i++; else break;

            if (s[i] == c[0]) num += 1 * decimal;// III=3 OR VII=7
            else continue;

            if (i < n) i++; else break;

            if (s[i] == c[0]) num += 1 * decimal;// VIII=8
            else continue;

            if (i < n) i++; else break;
        }
        return num;
    }
};

int main() {
    string x = "MCMXCIV";
    auto s = Solution();
    int num = s.romanToInt(x);
    cout << "num = " << num << endl;
    return 0;
}