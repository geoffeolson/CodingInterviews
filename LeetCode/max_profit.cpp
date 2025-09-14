#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int min = 10e6, max_profit = 0, profit = 0;
        for (int i = 0; i < prices.size(); i++) {
            if (prices[i] < min) {
                min = prices[i];
            }
            else {
                profit = prices[i] - min;
                if (profit > max_profit) {
                    max_profit = profit;
                }
            }
        }
        return max_profit;
    }
};

int main() {
    vector<int> prices = { 7,1,5,3,6,4 };
    auto s = Solution();
    int max_profit = s.maxProfit(prices);
    cout << "max_profit = " << max_profit << endl;
}