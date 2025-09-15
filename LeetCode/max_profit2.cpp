#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int> prices) {
        int profit = 0, inc;
        for (int i = 1; i < prices.size(); i++) {
            inc = prices[i] - prices[i - 1];
            if (inc > 0)
                profit += inc;
        }
        return profit;
    }
};

int main() {
    vector<int> prices = { 1,2,3,4,5 };
    auto s = Solution();
    int profit = s.maxProfit(prices);
    cout << "profit = " << profit << endl;
    return 0;
}