#include <iostream>
#include <vector>
#include <algorithm>
#include <algorithm>
#include <random>
#define IF132PATTERN(x, y, z) ( ( (x) < (z)   ) & ( (z) < (y)  )   )
using std::cout;
using std::vector;
using std::endl;
#define IF132PATTERN(x, y, z) ( ( (x) < (z)   ) & ( (z) < (y)  )   )
typedef vector<int> vint;
class node
{
public:
    node(const int &i): key(i), left(nullptr), right(nullptr), p(nullptr) {}
    node():key(0), left(nullptr), right(nullptr),p(nullptr){}
	~node(){}
public:
    int key;
    node* left;
    node* right;
    node* p;
};
node * tree_search(node *x, const int &k)
{
	if (x == nullptr || k == x->key)
		return x;
	if (k < x->key)
		return tree_search(x->left, k);
	else
		return tree_search(x->right, k);
}

// minimum

node * tree_minimum(node *x)
{	
	node* tmp;
	tmp = x;
	while (tmp->left)
	{
		tmp = tmp->left;
	}
	return tmp;
}

// maximum
node * tree_maximum(node *x)
{
	node * tmp;
	tmp = x;
	while(tmp -> right)
	{
		tmp = tmp -> right;
	}
	return tmp;
}
// maximun under med
node * tree_maximum_under_med(node *x, const int & med)
{
	node * tmp;
    node *res = nullptr; 
	tmp = x;
    if (tmp -> key < med)
        res = tmp;
    while (tmp)
    {
        if (tmp->key < med)
        {
            res = tmp;
            tmp = tmp->right;
            continue;
        }
        if (tmp->key >= med)
        {
            tmp = tmp->left;
            continue;
        }
        //if (tmp -> key == med)

    }
	return res;
}
// insertion

void tree_insert(node * &T, const int & key)
{
    
	node * z = new node(key);
	node *y = nullptr;
	node *x = T;// root
	while (x)
	{
		y = x;
		if (z->key < x -> key)
			x = x->left;
		else x = x->right;
	}
	z->p = y;
	if (!y)
	{
		T = z;// tree is empty; 
	}
	else 
	{
		if(z->key < y->key)
			y-> left = z;
		else
			y -> right = z;
	}
	return;
}

// deletion

void transplant(node * &T, node *u, node* v)
{
    // case one
	if (!u -> p)
	{
		T = v;
	}
	else 
	{
		if (u == u->p->left)
		{
			u->p->left = v;
		}
		else
		{
			u->p->right = v;
		}
	}
	if (v)
		v->p = u->p;
	return;
}
void tree_delete(node *&T, node *z)
{
	node *y;
	if (!z->left)
	{
		transplant(T, z, z->right);
	}
	else 
	{
		if (!z->right)
		{
			transplant(T, z, z->left);
		}
		else
		{
			y = tree_minimum(z->right);
			if (y->p != z)
			{
				transplant(T, y, y->right);
				y->right = z->right;
				y->right->p = y;
			}
			transplant(T, z, y);
			y->left = z->left;
			y ->left->p = y;

		}
	}
    delete z; ////////////////// important!!
	return;
}
void tree_free(node *x)
{
	if (x)
	{
		tree_free(x->left);
		tree_free(x->right);
		delete x;
	}
	return;
}
node* build_tree_by_vector(vint nums)
{
	auto engine = std::default_random_engine{};
	std::shuffle(nums.begin(), nums.end(), engine);/////////////////////////// avoid  the extrim situation.
	node *T = nullptr;
	for (auto i : nums)
	{
        //cout << i << "," << endl;
		tree_insert(T, i);
	}
    return T;
}
void inorder_tree_walk(node *x)
{
	if (x)
	{
		inorder_tree_walk(x->left);
		std::cout << x->key << ",";
		inorder_tree_walk(x->right);
	}
	return;
}
void delete_by_key(node * &T, const int &key)
{
    auto n = tree_search(T, key);
    tree_delete(T, n); 
    return;
}
bool find2(vint &nums)
{
    if (nums.size() < 3)return false;
    if (nums.size() == 3)
    {
        if (IF132PATTERN(nums[0], nums[1], nums[2]))
            return true;
        else
            return false;
    }
    auto T = build_tree_by_vector(nums);
    int L = nums[0];
    delete_by_key(T, L);
    int R = 0, M = 0;
    node* R_node = nullptr;
    //inorder_tree_walk(T);
    auto b = nums.begin()+1,e = nums.end()-1;
    for (auto iter = b; iter != e; ++iter)
    {
        M = *iter;
        delete_by_key(T, M);
        R_node = tree_maximum_under_med(T, M);
        if (R_node)
            R = (tree_maximum_under_med(T, M))->key;
        else 
        {
            if (L > M)
                L = M;
            continue;
        }
//        cout << L << "," << M << "," << R << endl;
        if (IF132PATTERN(L, M, R))
            return true;
        if (L > M)
            L = M;
    }
    tree_free(T);
    return false;
}
void print_node(node *t)
{
    if (t)
        cout << "key:" << t->key << endl;
    else
        cout << "nil" << endl;
    return;
}

int main()
{
	//vint A{15,6,3,7,2,4,13,9,18,17,20};
    vint A{3,1,4,2};
//    vint A{6,6,6,7};

    for (auto i : A)cout << i << ",";cout << endl;
    cout <<find2(A) << endl;
    
    //vint A{15, 17};
//	auto T = build_tree_by_vector(A);
	//inorder_tree_walk(T);
  //  print_node(tree_maximum_under_med(T, 15));
    //auto n = tree_search(T,15);
    //n = tree_minimum(T);
    //tree_delete(T, n);
	// inorder_tree_walk(T);
    /*
    cout << (tree_maximum(T)->key) << endl;
    for (auto i : A)
    {
        delete_by_key(T, i);
    }
    inorder_tree_walk(T);
    */
//	tree_free(T);
    return 0;
}
