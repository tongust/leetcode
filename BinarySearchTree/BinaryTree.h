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
    int numOfLC;/* strickly less left */
    int numOfRC;/* stricklt bigger right */
    int pos;
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
    node *search(int key);
    void destroy_tree();
    node *predecessor(node *leaf);
private:
    void destroy_tree(node *leaf);
    int insert(int key, node *leaf, int preNumLeft);
    node *search(int key, node *leaf);
        
    node *root;
};

#endif /*BINARYTREE_H*/
