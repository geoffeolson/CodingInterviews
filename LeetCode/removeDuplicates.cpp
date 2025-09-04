#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        int k = 0; // k points to the next element to copy data to
        // i points to the element to copy data from
        // j points to the first element with a value equal to i
        for (int i = 0, j = 0; i < n; i++) {
            // cout << "i = " << i << ", j = " << j << ", k = " << k << endl;
            // if the value of the element at j 
            // is not the same as i move the j pointer to i 
            if (nums[j] != nums[i]) j = i;
            // if the difference between i and j is less than 2
            // then the element at i can be copied to k 
            if (i - j < 2) {
                nums[k] = nums[i];
                k++;
            }
        }
        return k;
    }
};

void print_nums(string name, vector<int> nums) {
    int n = nums.size();
    cout << name << " = [";
    for (int i = 0; i < n; i++) {
        string delim = (i == n - 1) ? "" : ",";
        cout << nums[i] << delim;
    }
    cout << "]" << endl;
}

int main() {
    vector<int> nums = { 1,1,1,2,2,3 };
    auto s = Solution();
    int a = s.removeDuplicates(nums);
    cout << a << endl;
    print_nums("nums", nums);
}