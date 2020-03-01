# 297. Serialize and Deserialize Binary Tree
Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

For example, you may serialize the following tree

    1
   / \
  2   3
     / \
    4   5
as "[1,2,3,null,null,4,5]", just the same as how LeetCode OJ serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.
Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.

```cpp
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <list>
#include <math.h>       /* log2 */
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <deque>
#include <memory>

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

/* using */

using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::multiset;
using std::pair;
using std::set;
using std::sqrt;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

/* typedef */

typedef vector<int> vint;
typedef vector<vector<int>> vvint;
typedef vector<vvint> vvvint;
typedef vector<vvvint> vvvvint;

/* example */
/*
 * vector<int> mvec;
 * mvec.begin(); mvec.end(); pair<int, int>; first; second;
 * iterator
 */

#ifndef SKELETON 
#define _MAX_S_32 0x7fffffff
#define _MIN_S_32 0x80000000
#endif

using std::deque;

class Codec {
public:
	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
                string res;
                if (!root){
                        res = "";
                        res = "[]";
                        return res;
                }
                if (root->left == nullptr && root->right==nullptr) {
                    
                    res = string("[") + (root->val !=_MAX_S_32 ? std::to_string(root->val) : "") + "]";
                    return res;
                }
                vector<int> words;
                deque<TreeNode*> mque;
                words.push_back(root->val);
                mque.push_back(root);
                

                int lmd =pow(2, depth(root)) - 1;

                while(!mque.empty()) {
                        auto it = mque.front();
                        mque.pop_front();
                        if (it->left != nullptr) {
                                mque.push_back(it->left);
                                words.push_back(it->left->val);

                        } else {
                                if(words.size() < lmd)words.push_back(_MAX_S_32);
                        }
                        if (it->right != nullptr) {
                                mque.push_back(it->right);
                                words.push_back(it->right->val);
                        } else {
                                if(words.size() < lmd)words.push_back(_MAX_S_32);
                        }
                }
                
                auto eraseIt = words.end(), lmdit = words.begin();
                while(eraseIt != lmdit && *(eraseIt-1) == _MAX_S_32)
                {
                        eraseIt--;
                }
                
                words.erase(eraseIt, words.end());

                res = "[";
                for (int i = 0; i < words.size(); ++i) {
                        auto w = words[i];
                        if (w == _MAX_S_32) {
                                res += "null";
                        }
                        else {
                                res += std::to_string(w);
                        }
                        if (i+1 != words.size()) {
                                res += ",";
                        }
                        else {
                                res += "]";
                        }
                }
                return res;

	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
                auto nums = data2vec(data);
                //PRINT1D(nums, " ");//////////////////////////
                if (nums.size() == 1) {
                    return new TreeNode(nums[0]);
                }
                if (
                                nums.empty()||
                                nums[0] == _MAX_S_32)
                        return nullptr;
                vector<TreeNode*> tns(nums.size(), nullptr);
                int mc = 0;
                for (auto n : nums) {
                        if (n != _MAX_S_32) {
                                tns[mc] = new TreeNode(n);
                                //del.push_back(std::shared_ptr<TreeNode>(tns[mc]));////////////////del
                        }
                        mc++;
                }
        
                deque<TreeNode*>ps;
                auto root = tns[0];
                ps.push_back(root);
                mc = 1;
                while(!ps.empty()) {
                        auto it = ps.front();
                        ps.pop_front();
                        it->left = tns[mc];
                        if (it->left != nullptr)
                                ps.push_back(it->left);
                        mc++;
                        if (mc >= tns.size())break;
                        it->right = tns[mc];
                        if (it->right != nullptr)
                                ps.push_back(it->right);
                        mc++;
                        if (mc >= tns.size())break;

                }
                return tns[0];
	}
        vint data2vec(const string& data)
        {
                vector<string> words;
                vint sp;
                for (int i = 1; i < data.size()-1;) {
                        char c = data[i];
                        if (c == 'n') {
                                i += 5;
                                sp.push_back(_MAX_S_32);
                                continue;
                        }
                        string word;
                        while (c != ',') {
                                word.push_back(c);
                                i++;
                                if (i >= data.size()-1)break;
                                c = data[i];
                        }
                        sp.push_back(std::stoi(word));
                        i++;
                }
                return sp;
        }
    
        int depth(TreeNode *root) {
                if (root == nullptr)
                        return 0;
                int l = depth(root->left),
                    r = depth(root->right);
                if (l > r) 
                        return l+1;
                else return r+1;
        }
};
```

