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

node* btree::insert_return_node(int key, int data) {
    if(root != nullptr)
        return insert_return_node(key, data, root);
    else
    {
        root = new node(key, 0, 0, 0);
        root->sate.data = data;
        return root;
    }
}

node* btree::insert_return_node(int key, int data, node* leaf) {
    if(key < leaf->key_value)
    {
        leaf->sate.numOfLC += 1;
        leaf->sate.sumOfLeftSubtree += data;
        if(leaf->left != nullptr)
            return insert_return_node(key, data, leaf->left);
        else
        {
            leaf->left = new node(key, 0, 0, 0);
            leaf->left->sate.data = data;
            leaf->left->parent = leaf;
            return leaf->left;
        }  
    }
    else 
    {
        leaf->sate.sumOfRightSubtree += data;

        if (leaf->right != nullptr) {
            if (leaf->key_value != key)
                leaf->sate.numOfRC += 1;
            return insert_return_node(key, data, leaf->right);
        }
        else {
            leaf->right = new node(key, 0, 0, 0);
            leaf->right->sate.data = data;
            leaf->right->parent = leaf;
            return leaf->right;
        }
    }
}


node *btree::GetLastUpLeftAncestor(node *leaf) {
    node* n = leaf;
    while (n != nullptr) {
        if (n->parent == nullptr || n->parent->left == n)
            break;
        n = n->parent;
    }
    return n;
}

node *btree::GetLastUpRightAncestor(node *leaf) {
    node* n = leaf;
    while (n != nullptr) {
        if (n->parent == nullptr || n->parent->right == n)
            break;
        n = n->parent;
    }
    return n;
}
int btree::GetSumOfLessThan(node* leaf) {
    if (leaf == nullptr) return 0;
    node *lastUpLeftAncestor = GetLastUpLeftAncestor(leaf);
    return lastUpLeftAncestor->sate.GetSumOfSubtree()
        + lastUpLeftAncestor->sate.data
        - leaf->sate.data
        - leaf->sate.sumOfRightSubtree;
}
int btree::GetSumOfMoreThan(node* leaf) {
    if (leaf == nullptr) return 0;
    node *lastUpRightAncestor = GetLastUpRightAncestor(leaf);
    return
          lastUpRightAncestor->sate.GetSumOfSubtree()
        + lastUpRightAncestor->sate.data
        - leaf->sate.data
        - leaf->sate.sumOfLeftSubtree;
}
void btree::updateSateData(node* leaf, int val) {
    if (leaf == nullptr) return;
    bool isLeftChild = true;
    int update = val - leaf->sate.data;
    leaf->sate.data = val;
    if (leaf->parent != nullptr) {
        if (leaf != leaf->parent->left) {
            isLeftChild = false;
        }
        updateSateData(leaf->parent, update, isLeftChild);
    }
    return;
}
void btree::updateSateData(node* leaf, int update, bool isLeftChild) {
    node* n = leaf;
    while (n != nullptr) {
        if (isLeftChild) {
            n->sate.sumOfLeftSubtree += update;
        }
        else {
            n->sate.sumOfRightSubtree += update;
        }
        n = n->parent;
    }
    return;
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

/* ====================================================================== */

Satellite::Satellite(int nl, int nr, int p) : numOfLC(nl), numOfRC(nr), pos(p) {
    sumOfLeftSubtree 
        = sumOfRightSubtree
        = sumOfSubtree 
        = data 
        = 0;
} 

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

