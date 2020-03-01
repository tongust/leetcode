#include <iostream>

#include <vector>
#include <string>

#include <unordered_map>
#include <unordered_set>

#include "BinaryTree.h"
#include "Impl.h"
#include "SpecialBT.h"


/* Usings */

using std::cout;
using std::cin;
using std::endl;

using std::unordered_map;
using std::unordered_set;
using std::string;
using std::vector;

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
       vector<int> res;
       return res;
    }
};

int main() {
    vector<int> nums = {0,1,2,3,4,5,6,7,8,9};
    NumArray na(nums);
    while (1) {
        int l = 0, r = 0;
        l = 5, r = 7;
    //    cin >> l >> r; cout << endl;
        cout << "---------: " << na.sumRange(l,r) << ", " << na.sumArray << endl;
        int c = 0;
        for (int i = l; i <= r; i++) c += nums[i];
        cout << "final " << c << endl;
        break;
    }
    
    return 0;
}
