#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int m = 1;
        int i = 1;
        int half = n / 2;
        if (n == 1)
            return nums[0];
        while (i < n) {
            if (nums[i] == nums[i - 1]) {
                m++;
                if (m > half)
                    return nums[i];
            }
            else m = 1;
            i++;
        }
        return 0;
    }
};

int main() {
    vector<int> nums = { 2,2,1,1,1,2,2 };
    auto s = Solution();
    int a = s.majorityElement(nums);
    cout << "majority element = " << a << endl;
    //print_nums("nums", nums);
    return 1;
}