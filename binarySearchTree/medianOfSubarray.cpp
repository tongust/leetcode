#include <iostream>
#include <iostream>
#include <random>
#include <set> // binary search tree
#include <vector>
#include <algorithm> // heap algorithm
#include <string>
#include <random>
#include <vector>
#include <algorithm>
#include <list>
#include <random>
#include <map>
using std::cout;
using std::vector;
using std::endl;
using std::list;

typedef vector<int > vint;
template <class T> inline void print_1d(const T& vs, 
        const std::string &msg = "showing 1d...")
{
    cout << msg << endl;
    for (auto &i : vs)
    {
        std::cout << i << "\t";
    }
    std::cout << std::endl;
    return;
}
template <class T> inline  void print_2d(const T& vss, const std::string &msg = "Showing 2d...")
{
    cout << msg << endl;
    for (auto &i : vss)
        print_1d(i, " ");
    return;
}
vector<double> solve(vector<int> &nums, int k)
{
    int len_res = nums.size() - k + 1;
    vector<double> res(len_res, 0);
    std::multimap<int, int> mtp;
    for (int i = 0; i != k; ++i)
    {
       mtp.insert(std::make_pair(nums[i], i));
    }
    list<std::multimap<int, int>::iterator> vits;
    for (int i = 0; i != k; ++i)
    {
        auto ret = mtp.equal_range(nums[i]);
        for (auto it = ret.first; it != ret.second; ++it)
        {
            if (it->second == i)
            {
                vits.push_back(it);
                break;
            }
        }
    }
    for (auto &it : vits)
        cout << it->first << "," << it->second << endl;
    if (k%2 == 0)
    {
        auto mtp_it1 = mtp.begin();
        std::advance(mtp_it1, (k/2)-1);
        cout << mtp_it1->first << "     jljkl" << endl;
        res[0] = (double)mtp_it1->first + (double)(++mtp_it1)->first;
        res[0] /= 2.0;
        cout << ">>>>>>>>>>" << res[0] << endl;
        for (int i = 1; i<len_res; ++i)
        {
            auto it11 = *vits.begin();
            vits.pop_front();
            // push back 
            it11 = mtp.erase(it11);
            int tmp1 = i - 1 + k;
            mtp.insert(std::make_pair(nums[tmp1], tmp1));
            auto ret = mtp.equal_range(nums[i+k-1]);
            for (auto it = ret.first; it != ret.second; ++it)
            {
                if (it->second == tmp1)
                {
                    vits.push_back(it);
                    break;
                }
            }
            auto mtp_it1 = mtp.begin();
            std::advance(mtp_it1, (k/2)-1);
            res[i] = mtp_it1->first + (++mtp_it1)->first;
            res[i] /= 2.0;
        }
    }
    else
    {
        auto mtp_it1 = mtp.begin();
        std::advance(mtp_it1, (k/2));
        res[0] = mtp_it1->first;
        for (int i = 1; i<len_res; ++i)
        {
            auto it11 = *vits.begin();
            vits.pop_front();
            // push back 
            it11 = mtp.erase(it11);
            int tmp1 = i - 1 + k;
            mtp.insert(std::make_pair(nums[tmp1], tmp1));
            auto ret = mtp.equal_range(nums[i+k-1]);
            for (auto it = ret.first; it != ret.second; ++it)
            {
                if (it->second == tmp1)
                {
                    vits.push_back(it);
                    break;
                }
            }
            auto mtp_it1 = mtp.begin();
            std::advance(mtp_it1, (k/2));
            res[i] = mtp_it1->first;
        }
    }
    print_1d(res, "res");
    return res;

}

int main()
{
    vector<int> vs(2, 1);
    std::generate(vs.begin(), vs.end(), []()->int {return (rand()%10);});
    vs[0] = 2147483647;
    vs[1] = 2147483647;
    vs.push_back(2147483647);
    print_1d(vs);
    std::multimap<int, int> mtp = {{2,3},{3,4},{2,5}};

    solve(vs, 2);
//    mtp.insert(4,5);
//    solve(vs, 6);
    
    return 0;
}
