#include <iostream>

#include <vector>
#include <string>

#include <unordered_map>
#include <unordered_set>

#include "BinaryTree.h"
/* Usings */

using std::cout;
using std::cin;
using std::endl;

using std::unordered_map;
using std::unordered_set;
using std::string;
using std::vector;

btree::btree()
{
  root=nullptr;
}
void btree::destroy_tree(node *leaf)
{
  if(leaf!=nullptr)
  {
    destroy_tree(leaf->left);
    destroy_tree(leaf->right);
    delete leaf;
  }
}

int btree::insert(int key, node *leaf, int preNumLeft)
{
    if(key < leaf->key_value)
    {
        leaf->sate.numOfLC += 1;
        if(leaf->left != nullptr)
            return insert(key, leaf->left, preNumLeft);
        else
        {
            leaf->left = new node(key, 0, 0, 0);
        }  
    }
    else 
    {
        preNumLeft += (leaf->key_value != key ? 1 : 0) + leaf->sate.numOfLC;
        if (leaf->right != nullptr) {
            if (leaf->key_value != key)
                leaf->sate.numOfRC += 1;
            return insert(key, leaf->right, preNumLeft);
        }
        else {
            leaf->right = new node(key, 0, 0, 0);
        }
    }
    return preNumLeft;
}

node *btree::search(int key, node *leaf)
{
  if(leaf!=nullptr)
  {
    if(key==leaf->key_value)
      return leaf;
    if(key<leaf->key_value)
      return search(key, leaf->left);
    else
      return search(key, leaf->right);
  }
  else return nullptr;
}

int btree::insert(int key)
{
  if(root!=nullptr)
    return insert(key, root, 0);
  else
  {
    root = new node(key, 0, 0, 0);
    return 0;
  }
}

vector<int> countLess(vector<int> &num) {
    btree bt;
    vector<int> res(num.size());
    int c = 0;
    for (auto it = num.rbegin(); it != num.rend(); it++) {
        c++;
        res[num.size() - c] = bt.insert(*it);
    }
    return res;
}

node *btree::search(int key)
{
  return search(key, root);
}
void btree::destroy_tree()
{
  destroy_tree(root);
}

Satellite::Satellite(int nl, int nr, int p) : numOfLC(nl), numOfRC(nr), pos(p) {} 

node::node(int k, int nl, int nr, int p):key_value(k), sate(nl,nr,p) {
    left = right = parent = nullptr;
}

node* btree::predecessor(node *leaf) {
    if (leaf->parent == nullptr) 
        return nullptr;
    if (leaf->parent->right == leaf) {
        return leaf->parent;
    } 
    else {
        return predecessor(leaf->parent);
    }
}

