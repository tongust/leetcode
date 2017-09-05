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
#include <limits>
#include <algorithm>
#include <queue>
using std::queue;
using std::unordered_set;
using std::unordered_map;
using std::unordered_multimap;
using std::string;
using std::cout;
using std::vector;
using std::endl;
#define WHITE 0
#define GRAY 1 
#define BLACK 2

template<typename T/*weight type*/, typename Tv /*value type*/>
struct vertex
{
    /* default construct */
    vertex() : color(0), d(), pi(nullptr), value(){}
    vertex(const char& c, const T &d1, vertex *p, const Tv &val): color(c), d(d1), pi(p), value(val) {}
    /* copy construct */
    vertex(const vertex &v): color(v.color), d(v.d), pi(v.pi), value(v.value) {}
    /*assignment construct*/
    vertex& operator=(const vertex & v)
    {
        color = v.color;
        d = v.d;
        pi = v.pi;
        value = v.value;
        return *this;
    }
    /* member */
    /* color 0: white 1: gray, 2: black, otherwise white*/
    char color;
    T d;
    Tv value;
    vertex *pi;
};
typedef vertex<int/*1: connected, 0: disconnected*/, string /*value*/> vertex_str;
inline
bool isConnected(const string &lhs, const string &rhs)
{
    if (lhs.size() != rhs.size())return false;
    char mcc = 0;
    for (auto lit = lhs.begin(), rit = rhs.begin(); lit != lhs.end(); ++lit,++rit)
    {
        if (*lit != *rit) mcc++;
        if (mcc>1)return false;
    }
    if (mcc == 1)return true;
    else return false;
}
void BSF(unordered_map<vertex_str*, vector<vertex_str*>> &G, vertex_str *s);
vector<vector <string> >
mcombine(unordered_map<vertex_str*, vector<vertex_str*>> &G, vertex_str *s)
{
    vector<vector<string>> res;
    vector<string> res_ele(1);
    vector<vector<string>> res_next;
    int t1 = 0;
    auto d_now = s->d - 1;
    if (s->d == 0)
    {
        res.push_back(vector<string>(1,s->value));
        return res;
    }
    for (auto &it_p : G[s])
    {
        res_ele.resize(1);
        res_ele[0] = s->value;
        if ( it_p->d == d_now )
        {
            res_next = mcombine(G, it_p);
            t1 = res.size();
            res.resize(t1+res_next.size());
            for (auto &res_it : res_next)
            {
                res_ele.resize(res_it.size()+1);
                std::copy(res_it.begin(), res_it.end(), res_ele.begin()+1);
                res[t1] = res_ele;
                t1++;
            }
        }
    }
    return res;
}
vector<vector<string>> 
findLadders(string beginWord, string endWord, vector<string>& wordList) 
{
    vector<vector<string>> res; 
    unordered_map<vertex_str*, vector<vertex_str*>> G_adjacency_list;
    vector<vertex_str> Vs(wordList.size()+1);/*0: source 1: target*/
    Vs[0] = vertex_str(0,0,nullptr,beginWord);
    Vs[1] = vertex_str(0,0,nullptr,endWord);
    unordered_set<string> Vsets(wordList.begin(), wordList.end());
    auto resf1 = Vsets.find(endWord);
    if (resf1 == Vsets.end())return res;
    Vsets.erase(endWord);/*exclude the end word*/
    size_t mcc = 2;
    for (auto &it_str : Vsets) {Vs[mcc].value = it_str;mcc++;}
    /*build the graph*/
    if (isConnected(Vs[0].value, Vs[1].value))
    {
        G_adjacency_list[&Vs[0]].push_back(&Vs[1]);
    }
    for (int i = 0; i < Vs.size(); ++i)
    {
        for (int j = 0; j < Vs.size(); ++j)
        {
            if (isConnected(Vs[i].value, Vs[j].value))
                G_adjacency_list[&Vs[i]].push_back(&Vs[j]);
        }
    }
    /* Breadth first search*/
    BSF(G_adjacency_list, &Vs[0]);
    if (Vs[1].d == std::numeric_limits<decltype(vertex_str::d)>::max())
        return res;
    auto tmp_res = mcombine(G_adjacency_list, &Vs[1]);
    /*reverse*/
    res.resize(tmp_res.size(), vector<string>(Vs[1].d+1));
    auto res_b = res.begin();
    for (auto & it_res : tmp_res)
    {
        std::copy(it_res.begin(), it_res.end(), res_b->rbegin());
        res_b++;
    }

    /*
    int len_vstr = Vs[1]->d + 1;
    vertex_str *it_ver = &Vs[1];
    vector<string> tmps;
    for (int i = 3; i >= 0; --i)
    {
        tmps.clear();
        for (auto & p: G_adjacency_list[it_ver])
        {
            if (p->d == i)
            {
                tmps.push_back(p->value);
            }
        }
    }
    */
    /*
    for (auto &ps : G_adjacency_list)
    {
        cout << ps.first->value << ":\td:\t" << ps.first->d << ":\t";
        for (auto &it_p : ps.second) cout << it_p->value << " ";cout << endl;
    }
    for (auto & i : res)
    {
        for (auto &j : i)
            cout << j << ",";cout << endl;
    }
    */
    return res;
}
void BSF(unordered_map<vertex_str*, vector<vertex_str*>> &G, vertex_str *s)
{
    for (auto &it_ps : G)
    {
        it_ps.first->color = 0;
        it_ps.first->d = std::numeric_limits<decltype(vertex_str::d)>::max();
        it_ps.first->pi = nullptr;
    }
    s->color = GRAY;/*Gray*/
    s->d = 0;
    s->pi = nullptr;
    queue<vertex_str*> Q;
    Q.push(s);
    vertex_str *u;
    while (!Q.empty())
    {
        u = Q.front();
        Q.pop();
        for (auto v : G[u])
        {
            if (v->color == 0)
            {
                v->color = GRAY;
                v->d = u->d + 1;
                v->pi = u;
                Q.push(v);
            }
        }
        u->color = BLACK;/*BLACK*/
    }
    return;
}
int main()
{
    //vector<string> wd = {"hot","dot","dog","lot","log","cog"};
    vector<string> wd = {"hot","dot","dog","lot","log","cog"};
    std::for_each(wd.begin(), wd.end(), [](decltype(wd)::value_type &it)->void{cout << it << ",";});cout << endl;
    string beginWord = "hit", endWord = "cog";
    findLadders(beginWord, endWord, wd);
    vertex_str v1(0,1,nullptr,string("hot"));
    return 0;
}
