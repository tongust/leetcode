 /* LeetCode 536. Construct Binary Tree from String
* 
* You need to construct a binary tree from a string consisting of parenthesis and integers.
* 
* The whole input represents a binary tree. It contains an integer followed by zero, one or two pairs of parenthesis. The integer represents the root's value and a pair of parenthesis contains a child binary tree with the same structure.
* 
* You always start to construct the left child node of the parent first if it exists.
* 
* Example:
* 
* Input: "4(2(3)(1))(6(5))"
* Output: return the tree root node representing the following tree:
* 
       * 4
     * /   \
    * 2     6
   * / \   / 
  * 3   1 5   
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
template <typename T>
class binaryNode {
public:
    /* default ctor */
    binaryNode(): key(0), left(nullptr), right(nullptr), p(nullptr) {}
    /* ctor  */
    binaryNode(const binaryNode &n): 
        key(n.key), left(n.left), right(n.right),p(n.p) {}
    binaryNode(const T& t):key(t), left(nullptr), right(nullptr), p(nullptr){}
    /* dtor */
    ~binaryNode() = default;
/* data member */
public:
    binaryNode *left;
    binaryNode *right;
    binaryNode *p;
    T key;
};

vector<shared_ptr<binaryNode<int>>> vshes;
vector<binaryNode<int>*> vptrs;
char ms[100000];
void buildTree(char *b, char *e, binaryNode<int>* root) {
   char *it = b;
   string mk;
   for (;it != e; ++it) {
       if (*it != '(') 
           mk += *it;
       else break;
   }
   int key = stoi(mk);
   if (!root) {
       cerr << "Wriong: root is nil\n";
       return;
   }
   root->key = key;
   if (it != e) {/*one child exist at least*/
       string s1;
       it++;
       int num_l = 1;
       char *b1 = it, *b2, *e2;
       for (;it != e; ++it) {
           if (*it == '(')
               num_l++;
           else if (*it == ')') {
               num_l--;
               if (num_l == 0) {
                   break;
               }
           }
       }
       static int m11 = 0;m11++;
       shared_ptr<binaryNode<int>> c0sh = make_shared<binaryNode<int>>(binaryNode<int>(0));
       vshes.push_back(c0sh);
       shared_ptr<binaryNode<int>> c1sh = nullptr;
       char *e1 = it;
       c0sh->p = root;
       it++;
       if (it != e) {/* two */
           it++;
           b2 = it;
           e2 = e-1;
           c1sh = make_shared<binaryNode<int>> (binaryNode<int>(0));
           vshes.push_back(c1sh);
       }

       buildTree(b1,e1,c0sh.get());
       c0sh->p = root;
       //try { ///////////////
       if (c1sh) {
           c1sh->p = root;
           buildTree(b2,e2,c1sh.get());
           root->right = c1sh.get();
           root->left = c0sh.get();
       }
       else {
           root->left = c0sh.get();
           root->right = nullptr;
       }
   } 
   else { /* none child exists */
       return;
   }
   return;
}
void printTree(binaryNode<int> *t) {
    if (t) {
        cout << t->key << " ";
        printTree(t->left);
        printTree(t->right);
    } else return;
}

int main() {
   string mstr;
   cin >> mstr;
   copy(mstr.begin(), mstr.end(), ms);
   ms[mstr.size()] = '\0';
   auto p1 = make_shared<binaryNode<int>>(binaryNode<int>(0));
   binaryNode<int>* root = p1.get();
   buildTree(ms, ms+mstr.size(),root);
   printTree(root);
   return 0;

}







