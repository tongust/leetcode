/*
 * Set is implemented as balanced binary search tree.
 * */
#include <iostream>
#include <random>
#include <set> // binary search tree
#include <vector>
#include <algorithm> // heap algorithm
#include <string>
#include <random>
#include <map>

using std::cout;
using std::map;
using std::set;
using std::multiset;
using std::vector;
using std::endl;
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
typedef multiset<int> msetint;
typedef vector<int > vint;

vector<double> solve(
        vint &nums,
        int k
        )
{
    vector <double> res;
    int len_res = nums.size()+1-k;
    res.resize(len_res,0);
    if (k%2 == 1) // odd case
    {

    }
    else // even case
    {
        // initial stage.
        int len_win = k/2;
        vint tmp(nums.begin(), nums.begin()+k);
        std::sort(tmp.begin(),tmp.end());
        // min_win : the begin() element is maximum
        multiset<int, bool(*)(int,int)> min_win(tmp.begin(), tmp.begin()+len_win, [](int lhs, int rhs)->bool{return lhs>rhs;});
        // max_win : the begin() element is minimum.
        multiset<int> max_win(tmp.begin()+len_win, tmp.begin()+k);
        print_1d(min_win, "min left win");
        print_1d(max_win, "max right win");
        res[0] = (*min_win.begin())+(*max_win.begin());
        res[0] /= 2.0;
        auto next_res = res.begin()+1;
        bool exist_in_min_win = true; // whether the previous element exists in the left minimum window set.
        // true: means it exist in min_win, otherwise it exists in the other window.
        auto pre_ele = min_win.find(nums[k-1]);// previous element 
        if (pre_ele != min_win.end())
            exist_in_min_win = true;
        else
        {
            exist_in_min_win = false; 
            pre_ele = max_win.find(nums[k-1]);
        }
        auto it_nums = nums.begin() + k - 1;
        auto stop_it = nums.end() - k + 1;
        auto b_it = nums.begin()+1;
        for (;b_it != stop_it; ++b_it)
        {// second 
            it_nums++;
            vint ttt(b_it-1, b_it+5);
            std::sort(ttt.begin(), ttt.end());
            print_1d(ttt, "ttt");////////////////
            print_1d(min_win, "min_win");
            cout << *stop_it << "," << *it_nums << "," << *pre_ele << endl;
            print_1d(max_win, "max_win");
            auto min_b = min_win.begin();
            auto max_b = max_win.begin();
            *next_res = *(max_b) + *(min_b);
            *next_res /= 2.0;
            next_res++;
            if (*it_nums > *max_b) // case 0:  put new item into the max window
            {
                if (exist_in_min_win) // previous element exists in the left window.
                {
                    min_b = min_win.end();
                    pre_ele = min_win.erase(pre_ele);
                    pre_ele = max_win.insert(*it_nums); // insert new element into the max window.
                    exist_in_min_win = false;
                    // move the begin of max window into min window
                    min_win.insert(*max_b);
                    max_b = max_win.erase(max_b);
                }
                else
                {
                    max_b = min_win.end();
                    pre_ele = max_win.erase(pre_ele);
                    pre_ele = max_win.insert(*it_nums);
                    exist_in_min_win = false;
                }
                continue;
            }
            if (*it_nums == *max_b)// equal 
            {
                if (exist_in_min_win)
                {
                    min_b = min_win.end();
                    pre_ele = min_win.erase(pre_ele);
                    pre_ele = min_win.erase(pre_ele);
                    pre_ele = min_win.insert(*it_nums);
                    exist_in_min_win = true;
                }
                else 
                {
                    max_b = max_win.end();
                    pre_ele = max_win.erase(pre_ele);
                    pre_ele = max_win.insert(*it_nums);
                    exist_in_min_win = false;
                }
                continue;
            }
            if (*it_nums < *min_b) // case 1: put new item into the min window
            {
                if (exist_in_min_win)  // previous element exists in the left window.
                {
                    min_b = min_win.end();
                    pre_ele = min_win.erase(pre_ele);
                    pre_ele = min_win.insert(*it_nums);
                }
                else // move the first element of min window into the max window and delete the previous element.
                {
                    max_b = max_win.end();
                    pre_ele = max_win.erase(pre_ele);
                    max_win.insert(*min_b);
                    min_b = min_win.erase(min_b);
                    pre_ele = min_win.insert(*it_nums);
                    exist_in_min_win = true;
                }
                continue;
            }
            if (*it_nums == *min_b)
            {
                if (exist_in_min_win)
                {
                    min_b = min_win.end();
                    pre_ele = min_win.erase(pre_ele);
                    pre_ele = min_win.insert(*it_nums);
                    exist_in_min_win = true;
                }
                else
                {
                    max_b = max_win.end();
                    pre_ele = max_win.erase(pre_ele);
                    pre_ele = max_win.insert(*it_nums);
                    exist_in_min_win = false;
                }
                continue;
            }
            
        }// end of block


    }
    print_1d(res, "res:");
    return res;
}

int main()
{
    std::default_random_engine generator_random;
    //srand((unsigned)time(NULL));
    vector<int> vs(13, 1);
    std::generate(vs.begin(), vs.end(), []()->int {return (rand()%10);});
    print_1d(vs);
    solve(vs, 6); 


    return 0;
}
