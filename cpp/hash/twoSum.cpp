#include <iostream>
#include <climits>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <functional>
#define PARENT(i) (((i+1)/2)-1)
#define LEFT(i) (2*i+1)
#define RIGHT(i) (2*i+2)
#define mswap_ele(l,t,r) {t = (l);l = (r); r = (t);}
using std::pair;
using std::cout;
using std::vector;
using std::endl;
using std::hash;
using std::unordered_map;
using std::unordered_set;
using std::string;
using std::ostream;
typedef vector<int> vint;
typedef unsigned long long ull64;
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> mst;
    int mcc = 0;
    for (auto &i : nums)
    {
        mst[target - i] = mcc;
        mcc++;
    }
    for (auto &i : mst) cout << i.first << "," << i.second << endl;
    for (int i = 0; i < nums.size();++i)
    {
        auto resf = mst.find(nums[i]);
        cout << nums[i] << "ss" << endl;
        if (resf != mst.end() && resf ->second != i)
            return vector<int>{i,resf->second};
    }
}

int main()
{
    vector<int> nums{3,2,4};
    auto res = twoSum(nums, 6);
    for (auto &i : res) cout << i << endl;
    return 0;
}
