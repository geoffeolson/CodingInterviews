
#include <bits/stdc++.h>
using namespace std;

void print_nums(string name, vector<int> nums) {
    int n = nums.size();
    cout << name << " = [";
    for (int i = 0; i < n; i++) {
        string delim = (i == n - 1) ? "" : ",";
        cout << nums[i] << delim;
    }
    cout << "]" << endl;
}

class Solution {
  public:
  void merge(vector<int>& nums1, int m, vector<int>& nums2, int n){
    vector<int> x( nums1.size());
    for (int i=0, j=0; i<m or j<n;){
      bool num1 = false;
      if (i<m){
        if (j<n){
          if ( nums1[i] < nums2[j]) num1 = true;
          else num1 = false;
        } else num1 = true;
      } else num1 = false;

      if (num1){
        x[i+j] = nums1[i];
        i++;
      }else{
        x[i+j] = nums2[j];
        j++;
      }
    }
    print_nums("test", x);
    for ( int i=0; i < nums1.size(); i++)
      nums1[i] = x[i];
  }
};

int main() {
  vector<int> nums1 = {1,2,3,0,0,0};
  vector<int> nums2 = {2,5,6};
  print_nums( "nums1", nums1);
  print_nums( "nums2", nums2);
  auto s = Solution();
  s.merge(nums1, 3, nums2, 3);
  print_nums( "nums1", nums1);
  return 0;
}
