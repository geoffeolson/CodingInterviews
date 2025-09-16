#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int size = nums.size();
        int jump_count = 0;
        int max_jump = 0;
        int count_boundary = 0;
        if (size == 1) return 0;
        for (int i = 0; i < size; i++) {
            int current_jump = nums[i] + 1;
            if (current_jump >= size - 1) return jump_count + 1;
            if (current_jump > max_jump) max_jump = current_jump;
            if (i >= count_boundary) {
                count_boundary = max_jump;
                jump_count++;
            }
        }
        return 0;
    }
};

int main() {
    vector<int> nums = { 2,3,1,1,4 };
    auto s = Solution();
    int jumps = s.jump(nums);
    cout << "jumps = " << jumps << endl;


}