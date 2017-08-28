#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <math.h>       /* log2 */

#ifndef MMIN
#define MMIN(x,y) ((x) > (y) ? (y) : (x))
#endif
#ifndef MMAX
#define MMAX(x,y) ((x) < (y) ? (y) : (x))
#endif

#ifndef PRINT1D
#define PRINT1D(v,d) do {for (auto it_print : v) cout << it_print << d; cout << endl;}while(0)
#endif

#ifdef PRINT1D
#ifndef PRINT2D
#define PRINT2D(v,d)                          \
do {                                          \
    cout << endl;                             \
    for (auto &it_print2d : v) {              \
        for (auto &it_print1d : it_print2d) { \
            cout << it_print1d << d;          \
            } cout << endl;                   \
    }                                         \
} while(0)
#endif
#endif

#ifndef MDebugLog
#define MDebugLog(msg)  std::cout << __FILE__ << ":" << __LINE__ << ": " << msg
#endif

/* Usings */

using std::cout;
using std::cin;
using std::endl;

using std::unordered_map;
using std::unordered_set;
using std::string;
using std::vector;
using std::pair;

/* Typedef */

typedef vector<int> vint;
typedef vector<vector<int>> vvint;

typedef pair<int, int> range_node;


struct seg_node {
    seg_node() = default;
    seg_node(int i, int j, int k = 0) 
        :rang(i, j), right(nullptr), left(nullptr), high(k){}
    range_node rang;
    int high;
    seg_node *left,
             *right;
    bool isIn(int i) {
        return (rang.first <= i) && (i <= rang.second);
    }
    bool isLeaf() {
        return (left == nullptr) && (right == nullptr);
    }
};

void print_pair(seg_node* r);

class segment_tree {
public:
    segment_tree():root(nullptr) {  }
    ~segment_tree(){dispose_segment_tree(root);}
    seg_node* root;
    seg_node* make_seg_node(seg_node* left, seg_node* right); 
    seg_node* build_segment_tree_recur(vector<seg_node*>);
    seg_node* build_segment_tree(vector<pair<int,int>>&);
    seg_node* build_segment_tree(vector<pair<int,int>>&, vector<int>&);
    void dispose_segment_tree(seg_node*);
    vector<seg_node*> search_range(int);
    vector<seg_node*> search_range_recur(int, seg_node*);
};


seg_node* segment_tree::make_seg_node(seg_node* left, seg_node* right) {
    if (left == nullptr)return right;
    if (right == nullptr)return left;
    seg_node* snewnode = new seg_node;
    if (left->rang.first > right->rang.first) {
        auto tmp = left;
        left = right;
        right = tmp;
    }
    snewnode->rang.first = left->rang.first;
    snewnode->rang.second = MMAX(left->rang.second, right->rang.second);
    snewnode->left = left;
    snewnode->right = right;
    return snewnode;
}

seg_node* segment_tree::build_segment_tree_recur(vector<seg_node*> snodes) {
    int N = snodes.size();
    if (N == 0) return nullptr;
    for (auto it : snodes) {cout <<"---";print_pair(it);}
    if (N == 1) return snodes[0];
    vector<seg_node*> snew((N+1)/2, nullptr);
    int M = snew.size();
    if (N % 2 == 1) snew[M-1] = snodes[N-1];
    auto it_sn = snew.begin();
    for (int i = 0; i < N-1; i+=2) {
        *it_sn = make_seg_node(snodes[i], snodes[i+1]);
        it_sn++;
    }
    for (auto it : snew) {cout <<"++";print_pair(it);}
    return build_segment_tree_recur(snew);
}
void segment_tree::dispose_segment_tree(seg_node* root) {
    if (root == nullptr) return;
    dispose_segment_tree(root->left);
    dispose_segment_tree(root->right);
    delete root;
    return;
}

seg_node* segment_tree::build_segment_tree(vector<pair<int, int>> &nums) {
    int N = nums.size();
    vector<seg_node*> snodes(N, nullptr);
    for (int i = 0; i < N; ++i) {
        snodes[i] = new seg_node(nums[i].first, nums[i].second);
    }
    root = build_segment_tree_recur(snodes);
    return root;
}
seg_node* segment_tree::build_segment_tree(vector<pair<int, int>> &nums, vint &hs) {
    int N = nums.size();
    vector<seg_node*> snodes(N, nullptr);
    for (int i = 0; i < N; ++i) {
        snodes[i] = new seg_node(nums[i].first, nums[i].second, hs[i]);
    }
    root = build_segment_tree_recur(snodes);
    return root;
}

vector<seg_node*> segment_tree::search_range_recur(int val, seg_node* snodep) {
    vector<seg_node*> res;
    if (snodep == nullptr || !(snodep->isIn(val)))return res;
    if (snodep->isLeaf())
    {
        res.push_back(snodep);
        return res;
    }
    auto res_l = res,
         res_r = res;
    if (snodep->left != nullptr && snodep->left->isIn(val)) {
        res_l = search_range_recur(val, snodep->left);
    }
    if (snodep->right != nullptr && snodep->right->isIn(val)) {
        res_r = search_range_recur(val, snodep->right);
    }
    res.resize(res_l.size()+res_r.size(), nullptr);
    std::copy(res_l.begin(), res_l.end(), res.begin());
    std::copy(res_r.begin(), res_r.end(), res.begin()+res_l.size());
    return res;
}

vector<seg_node*> segment_tree::search_range(int val) {
    return search_range_recur(val, root);
}
void print_pair(seg_node* r)  {
    if(r!=nullptr)cout << r->rang.first << " " << r->rang.second << endl;
    else cout << "nil" << endl;
    return;
}
int main() {
    segment_tree stree;
    vint f = {1, 2, 3, 8};
    vint s = {3, 5, 7, 9};
    vector<pair<int, int>> vp;
    for (int i = 0; i < s.size(); ++i ) {
        vp.push_back(pair<int, int>(f[i], s[i]));
    }
    stree.build_segment_tree(vp);
    auto res = stree.search_range(3);
    for (auto r : res) {
        cout << "<<";print_pair(r);
    }
    return 0;
}
