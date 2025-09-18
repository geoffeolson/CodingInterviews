#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        const int n = nums.size();
        vector<int> ans(n);
        int p = 1; //Product
        // Backward
        for (int i = n - 1; i >= 0; i--) {
            ans[i] = p;
            p *= nums[i];
        }
        // Forward
        p = 1;
        for (int i = 0; i < n; i++) {
            ans[i] *= p;
            p *= nums[i];
        }
        return ans;
    }
};

int main() {
    vector<int> nums = { 1, 2, 3, 4 };
    auto s = Solution();
    vector<int> ans = s.productExceptSelf(nums);
    cout << "ans = [";
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    cout << "]" << endl;
    return 1;
}