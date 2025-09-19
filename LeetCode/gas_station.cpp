#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int> gas, vector<int> cost) {
        int n = gas.size(), idx = 0;
        int min = gas[0] - cost[0], sum = 0;
        for (int i = 0; i < n; i++) {
            int next = gas[i] - cost[i];
            sum += next;
            if (sum <= min) {
                min = sum;
                idx = i;
            }
        }
        if (sum < 0) return -1;
        idx++;
        return idx % n;
    }
};

int main() {
    vector<int> gas = { 1,2,3,4,5 };
    vector<int> cost = { 3,4,5,1,2 };
    auto s = Solution();
    int k = s.canCompleteCircuit(gas, cost);
    cout << "k = " << k << endl;
}
