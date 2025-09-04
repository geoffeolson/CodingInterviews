#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {

        // initialize j pointing to the last element of nums
        int j = nums.size() - 1;

        // move j to point to the first element of nums thats not equal to val
        while (j >= 0) {
            if (nums[j] == val) j--;
            else break;
        }

        // starting at the j position search through nums for elements equal to val
        int i = j;
        while (i > 0) {

            // if the element pointed to by i is equal to val 
            // set the element to the value at j and decriment j
            if (nums[--i] == val)
                nums[i] = nums[j--];
        }

        // return the number of elements of nums not equal to val
        return j + 1;
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
    vector<int> nums = { 0,1,2,2,3,0,4,2 };
    int val = 2;
    auto s = Solution();
    int a = s.removeElement(nums,val);
    cout << "number of elements not equal to val = " << a << endl;
    print_nums("nums", nums);
    return 1;
}