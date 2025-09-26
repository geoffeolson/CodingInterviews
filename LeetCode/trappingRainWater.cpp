#include <bits/stdc++.h>
#include <ratio>
using namespace std;

class Solution {
public:
    int trap(vector<int>& h) {
        int n = h.size();
        int water = 0;
        int j = 0;
        int k = n - 1;

        // LEFT CASCADE
        for (int i = 0; i < n; i++) {
            if (h[i] >= h[j]) {
                water += h[j] * (i - j);
                j = i;
            }
            water -= h[i];
        }
        water += h[j];

        // RIGHT CASCADE
        for (int i = n - 1; i >= j; i--) {
            if (h[i] >= h[k]) {
                water += h[k] * (k - i);
                k = i;
            }
        }
        return water;
    }
};

int main() {
    vector<int> hight = { 0,1,0,2,1,0,1,3,2,1,2,1 };
    auto s = Solution();
    int e = s.trap(hight);
    cout << "elevation = " << e << endl;
}