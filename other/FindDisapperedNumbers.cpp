
#include <iostream>
#include <vector>
using std::cout;
using std::vector;
using std::endl;


vector<int>
find(vector<int> &nums)
{
    vector<int > res;
    auto N = nums.size();
    for (int i = 0; i != N; ++i)
    {
        int t2 = nums[i];
        if (t2 > 0)
        {
            t2--;
            int &t1 = nums[t2];
            if (t1 > 0)
                t1 = -t1;
        
        }
        else
        {
            t2 = -t2 - 1;
            int &t1 = nums[t2];
            if (t1 > 0)
                t1 = -t1;
        }

    }

    for (int i = 0; i != N; ++i)
    {
        if (nums[i]>0)
            res.push_back(i+1);
    } 
    
    return res;
}
int main()
{
    vector<int > nums = {4,3,2,7,8,2,3,1};
    auto res = find(nums);
    for (auto &i : res) cout << i << ","; cout << endl;
    return 0;
}
