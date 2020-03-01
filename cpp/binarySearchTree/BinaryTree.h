#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>

#include <vector>
#include <string>

#include <unordered_map>
#include <unordered_set>


/* Usings */

using std::cout;
using std::cin;
using std::endl;

using std::unordered_map;
using std::unordered_set;
using std::string;
using std::vector;


vector<int> countLess(vector<int> &num); 
class Satellite {
public:
    Satellite(int nl = -1, int nr = -1, int p = -1); 

    /* strickly less left, 
     * if this node's value is equal to its left child,
     * the numOfLC will not increment by 1, same is below 
     */
    int numOfLC;
    int numOfRC;/* stricklt bigger right */
    int pos;
    int data;
    int sumOfLeftSubtree;
    int sumOfRightSubtree;
    int sumOfSubtree;
    int SetSumOfSubtree() {
        sumOfSubtree = sumOfLeftSubtree + sumOfRightSubtree;
        return sumOfSubtree;
    }
    int GetSumOfSubtree() {return SetSumOfSubtree();}
    /* TODO the pointer to other data */
};


struct node
{
		node(int k = -1, int nl = -1, int nr = -1, int p = -1);
    int key_value;
		Satellite sate;
    node *left;
    node *right;
    node *parent;
};

class btree
{
public:
    btree();
    ~btree() {destroy_tree();}

    int insert(int key);
    node* insert_return_node(int key, int data);
    node *search(int key);
    void destroy_tree();
    node *predecessor(node *leaf);
    node *GetLastUpLeftAncestor(node *leaf);
    node *GetLastUpRightAncestor(node*);
    int GetSumOfMoreThan(node *);
    int GetSumOfLessThan(node *);
    void updateSateData(node*, int);
private:
    void destroy_tree(node *leaf);
    int insert(int key, node *leaf, int preNumLeft);
    node* insert_return_node(int key, int data, node *leaf);
    node *search(int key, node *leaf);
    void updateSateData(node*, int, bool);
        
    node *root;
};

#endif /*BINARYTREE_H*/
