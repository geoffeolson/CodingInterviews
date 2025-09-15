#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        const int n = nums.size();
        for (int i = 0, j = 0; i < n; i++) {
            const int jump = nums[i] + i;
            if (jump >= n - 1) {
                return true;
            }
            else if (jump > j) {
                j = jump;
            }
            else if (j == i) {
                return false;
            }
        }
        return false;
    }
};

int main() {
    vector<int> nums = { 2, 3, 1, 1, 4 };
    auto s = Solution();
    bool can_jump = s.canJump(nums);
    cout << "can_jump = " << can_jump << endl;
    return 0;
}