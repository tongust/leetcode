/*Write a function to determine if a given target is in the array.*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include <iterator>
#define MBEG -1
#define MEND -2
using std::cout;
using std::list;
using std::vector;
using std::endl;
using std::string;
typedef vector<int>::iterator vit;
bool search(vit b, vit e,const int &target)
{
    int N = e - b;
    if (N <= 3) 
    {
        bool res = false;
        for (vit it = b; it != e; it++)
        {
            if (*it == target)
            {
                res = true;
                break;
            }
        }
        return res;
    }
    vit med = b + (N/2);
    vit rigit = e - 1;
    if (*b == target || *med == target || *rigit == target) return true;
    /* case 1: the med is not equal to neither b or rigit */
    if (*med != *b && *med != *rigit)
    {
        if (*b < *med)
        {
            if (target > *b && target < *med)
                return search(b+1, med, target);
            else
                return search(med+1, rigit, target);
        }
        else
        {
            if (target > *med && target < *rigit)
                return search(med+1, rigit, target);
            else
                return search(b+1, med, target);
        }
    }
    /* case 2: the med is equal to either b or rigit */
    else
    {
        bool slg = false;
        if (*med == *b)
        {
            slg = false;
            for (vit it = b; it != med; it++)
                if (*it != *med)
                {
                    slg = true;
                    break;
                }
            if (slg) return search(b+1, med, target);
            else return search(med+1, rigit, target);
        }
        else
        {
            slg = true;
            for (vit it = med; it != rigit; it++)
                if (*it != *med)
                {
                    slg = false;
                    break;
                }
            if (slg) return search(b+1, med, target);
            else return search(med+1, rigit, target);
        }
    }
}
bool search(vector<int> &nums, int target)
{
    if (nums.empty()) return false;
    return search(nums.begin(), nums.end(), target);
}
int main()
{
    vector<int> nums = {4,5,6,7,0,1,2};
    for (auto &i : nums)cout << search(nums, i+1) << endl;
    return 0;
}
