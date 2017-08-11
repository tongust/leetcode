#include <iostream>

#include <vector>
#include <string>

#include <unordered_map>
#include <unordered_set>

#include "BinaryTree.h"


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
    vector<int> nums = {5,2 ,6, 1};
    auto res = countLess(nums);
    for (auto it : res) 
        cout << it << ",";
    cout << endl;
    return 0;
}
