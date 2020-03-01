/*
Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?
*/

#include <iostream>
#include <list>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <algorithm>
#include <random>
#include <functional>
#include <string>
#include <memory>
#include <stdexcept>      // std::out_of_range
#include <stack>

using namespace std;


  struct TreeNode {

      int val;

      TreeNode *left;

      TreeNode *right;

      TreeNode(int x) : val(x), left(NULL), right(NULL) {}

  };

 
typedef TreeNode* tptr;

vector<tptr> vs;



void maxTree(tptr root, tptr &res) {
    if (!root)return;
    if (root->val > res->val) {
        res = root;
    } 
    maxTree(root->left, res);
    maxTree(root->right, res);
    return;
}
void minTree(tptr root, tptr &res) {
    if (!root)return;
    if (root->val < res->val) {
        res = root;
    } 
    minTree(root->left, res);
    minTree(root->right, res);
    return;
}

tptr minTreeR(tptr root) {
    if (!root)return root;
    auto p = root->right;
    if (!p)return root;
    else {
        minTree(root->right, p);
    }
    return p;
}


tptr maxTreeL(tptr root) {
    
    if (!root)return root;
    auto p = root->left;
    if (!p)return root;
    else {
        maxTree(root->left, p);
    }
    return p;
}

class Solution {

public:

    void exchangeNode(tptr p1, tptr p2) {

        auto tmp = p1->val;

        p1->val = p2->val;

        p2->val = tmp;

        //cout << tmp << endl;
        return;

    }

    void recoverTree(TreeNode* root) {

        if(!root)return;

        auto med = root;

        auto left = maxTreeL(med), right = minTreeR(med);

        // case 1

        if (left == right)return;

        if (left == med) {

           // cout << "l" << endl;
           // cout << (long)left << " " << (long)med << " " << (long)right << endl;

            if (med->val < right->val) return recoverTree(med->right);

            else {

                exchangeNode(med, right);

                return;

            }

        } else if(right == med) {

            if (med->val > left->val) {

                recoverTree(med->left);

            }

            else {

                exchangeNode(med, left);

            }

        } else {

            // 1

            if (left->val < med->val && med->val < right->val) {

                recoverTree(med->left);

                recoverTree(med->right);

               

            } 

            else if (left->val>med->val && med->val > right->val)  {

                exchangeNode(left, right);

            }

            else if (left->val > med->val) {

                exchangeNode(left, med);

            }

            else {

                exchangeNode(right, med);

            }

        }

        return;

    }

};

int main(){
    vector<shared_ptr<TreeNode>> desTree;
    auto p = make_shared<TreeNode>(3);
    desTree.push_back(p);
    auto p1  = make_shared<TreeNode>(2);
    p->right = p1.get();
    desTree.push_back(p1);
    auto p2  = make_shared<TreeNode>(1);
    p1->right = p2.get();
    desTree.push_back(p2);
    Solution so;
    so.recoverTree(p.get());
    cout << p->val << " "<<  p->right->val << " "<<p->right->right->val << endl;
    return 0;
}

