/*
 *  Given two words (beginWord and endWord), and a dictionary's word list,
 *  find all shortest transformation sequence(s) from beginWord to endWord, such that:
 *  Only one letter can be changed at a time
 *  Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
 * */
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <random>
using std::unordered_set;
using std::unordered_map;
using std::unordered_multimap;
using std::string;
using std::cout;
using std::vector;
using std::endl;
inline 
void copy2(const string &scr, string &dest, const int& b, const int & len)
{
    dest.resize(len);
    auto it_s = scr.begin()+b;
    auto it_d = dest.begin();
    for (;it_d != dest.end(); ++it_d)
    {
        *it_d = *it_s;
        it_s += 2;
    }
    return;
}
vector<vector<string>> 
findLadders(string beginWord, string endWord, vector<string>& wordList) 
{
    vector<vector<string>> res; 
    unordered_multimap<string, string> oddDic, evenDic;
    string odd_s, even_s;
    
    for (auto &its : wordList)
    {
        /*even*/
        copy2(its, even_s, 0, int((its.size()+1)/2));
        /*odd*/
        copy2(its, odd_s, 1, int((its.size())/2));
        evenDic.insert(std::pair<string, string>(even_s, odd_s));
        oddDic.insert(std::pair<string, string>(odd_s, even_s));
    }
    
    for (auto &it_pair : oddDic)
    {
       cout << it_pair.first << "--->" << it_pair.second << endl;
    }
    for (auto &it_pair : evenDic)
    {
       cout << it_pair.first << "--->" << it_pair.second << endl;
    }
    

    //auto res_range = oddDic.equal_range(string("o"));
    /*std::for_each(res_range.first, res_range.second, [](decltype(oddDic)::value_type &ts)->void {cout << ts.first << "--->" << ts.second <<"\n";return;});*/

    return res;
}
int main()
{
    vector<string> wd = {"hot","dot","dog","lot","log","cog"};
    std::for_each(wd.begin(), wd.end(), [](decltype(wd)::value_type &it)->void{cout << it << ",";});cout << endl;
    string beginWord = "hit", endWord = "cog";
    findLadders(beginWord, endWord, wd);
    return 0;
}
