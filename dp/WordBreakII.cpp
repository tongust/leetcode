#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <random>
using std::unordered_set;
using std::string;
using std::cout;
using std::vector;
using std::endl;
vector<string> wordPrint(vector<vector<int>> &A, string &s, int index)
{
    vector<string> res, res_next;
    string tmp;
    for (auto &i : A[index])
    {
        tmp = string(s.begin()+index, s.begin()+1+i);
        if (i+1 < s.size()) 
        {
            tmp += " ";
            res_next = wordPrint(A, s, i+1);
            for (auto &j : res_next)
            {
                res.push_back(tmp+j);
            }
        }
        else
        {
            res.push_back(tmp);
        }
    }
    return res;
}
vector<string> wordBreak(string s, vector<string>& wordDict) 
{
    vector<string> res;
    if (s.empty())return res;
    vector<vector<int>> A(s.size());
    unordered_set<string> wd;
    for (auto &i : wordDict) wd.insert(i);
    int N = s.size(), N1 = s.size()-1;
    string tmps;
    int t1 = 0;
    for (int i = N1; i >= 0; --i)
    {
        tmps.clear();
        for (int j = i; j < N; ++j)
        {
            tmps.push_back(s[j]);
            auto refs = wd.find(tmps);
            cout << tmps << endl;
            if (refs != wd.end())
            {
                if (j+1>=N)
                    A[i].push_back(j);
                else
                {
                    if (!A[j+1].empty())
                        A[i].push_back(j);
                }
            }
        }
    }
    int mcc = 0;
    for (auto &i : A)
    {
        cout << mcc << "\t";
        for (auto &j : i)
            cout << j << ",";cout <<endl;
        mcc++;
    }
    /* print it out */
    if (!A[0].empty())
        res = wordPrint(A, s, 0);
    return res;
}
int main()
{
    vector<string> dic = {"cat", "cats", "and", "sand", "dog"};
    string s = "catsanddog";
    auto res = wordBreak(s,dic);
    for (auto &i : res)
        cout << i << endl;

    return 0;
}
