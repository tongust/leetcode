/*
Remember the story of Little Match Girl? By now, you know exactly what matchsticks the little match girl has, please find out a way you can make one square by using up all those matchsticks. You should not break any stick, but you can link them up, and each matchstick must be used exactly one time.

Your input will be several matchsticks the girl has, represented with their stick length. Your output will either be true or false, to represent whether you could make one square using all the matchsticks the little match girl has.

Example 1:
Input: [1,1,2,2,2]
Output: true

Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.
Example 2:
Input: [3,3,3,3,4]
Output: false

Explanation: You cannot find a way to form a square with all the matchsticks.
 */

/*
 * Be careful the recrusive function. When you write some tedious code, it maybe shows poor performance.
 * /

#include <iostream>

#include <string>
#include <vector>
#include <algorithm>
#include <algorithm>
#include <random>
using std::string;
using std::cout;
using std::vector;
using std::endl;
typedef vector<int> vint;
bool find2(vint &nums, int i,
        int w1,
        int w2,
        int w3,
        int w4)
{
    if (i == -1)
    {
        if ((w1==w2)&&(w2==w3)&&(w3==w4))
            return true;
        else
            return false;
    }
    else
    { 
        if (w1>=nums[i])
            if (find2(nums,i-1,w1-nums[i],w2,w3,w4))
                return true;
        if (w2>=nums[i])
            if(find2(nums,i-1,w1,w2-nums[i],w3,w4))
                return true;
        if (w3>=nums[i])
            if (find2(nums,i-1,w1,w2,w3-nums[i],w4))
                return true;
        if (w4>=nums[i])
            if(find2(nums,i-1,w1,w2,w3,w4-nums[i]))
                return true;
        return false;
    }
}


class Solution {
public:
    bool makesquare(vector<int>& nums) {
        auto N = nums.size();
        if (N<4) return false;
        int sum = 0;
        for (auto &i : nums) sum+=i;
        int sum_q = sum / 4;
        if (sum_q*4 != sum) return false;
        else return find2(nums, N-1, sum_q, sum_q, sum_q, sum_q);
    }
};
