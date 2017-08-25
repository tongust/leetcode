Given a complete binary tree, count the number of nodes.

> Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.

```{cpp}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> get_path(int level, int n){
        n++;
        vector<int> res(level, 0);
        int tmp = n;
        for (int i = 0; i < level; ++i) {
            int &ref = res[level - 1 - i];
            if (tmp % 2 == 0) {
                ref = 0;
            } else {
                ref = 1;
            }
            tmp = (tmp + 1) / 2;
        }
        return res;
    }
    int isLeaf(const vector<int> &path, TreeNode* root) {
        auto it = root;
        int mc = 0;
        int N = path.size();
        for (auto p : path) {
            if (p == 0) 
                it = it->right;
            else
                it = it->left;
            if (mc == N - 1) {
                return (it->left != nullptr) + (it->right!=nullptr);
            }
            mc++;
        }
        return 0;
    }
    int run(TreeNode * root) {
        // coner case
        int N = 0;
        if (root == nullptr) return 0;
        auto it = root;
        it = it->left;
        while (it != nullptr) {
            N++;
            it = it->left;
        } 
        if (N == 0) return 1;
        if (N == 1) return 1 + (root->right != nullptr ? 2 : 1);
        int parent_res_idx = 0;
        int secondlastnum = 1 <<  (N - 1);
        int lastindex = 0;
        int beg_idx = 0,
            mid_idx = secondlastnum / 2,
            end_idx = secondlastnum -  1;
        auto beg_path = get_path(N-1, beg_idx);
        auto mid_path = get_path(N-1, mid_idx);
        auto end_path = get_path(N-1, end_idx);

        int mid_is = isLeaf(mid_path, root),
                beg_is = isLeaf(beg_path, root),
                end_is = isLeaf(end_path, root);
        auto cal = [](int n0)->int {if (n0 < 0)n0 = 0;return (1 << (n0+1)) - 1;};
        //cout << mid_is << " " << beg_is <<  " " << end_is << " e " << N << endl;
        
        //for (auto it : end_path) cout << it << endl;
        //cout << mid_is << " " << beg_is <<  " " << end_is << " e " << N << endl;
        if (end_is == 2) {
           // cout << "a" << endl;
            return cal(N);
        }
        
        if (N == 2) {
            
            return cal(1) + beg_is + end_is;
        }
        
        if (N == 1) return 1 + beg_is + end_is;
        int mid1_is = 0;
        while (true ) {
            
            beg_path = get_path(N-1, beg_idx);
            mid_path = get_path(N-1, mid_idx);
            auto mid1_path = get_path(N-1, mid_idx-1);
            end_path = get_path(N-1, end_idx);
            mid_is = isLeaf(mid_path, root);
            mid1_is = isLeaf(mid1_path, root);
            beg_is = isLeaf(beg_path, root);
            end_is = isLeaf(end_path, root);
            if (end_idx - beg_idx == 2) {
               // cout << cal(N-1) << " " << ((parent_res_idx)*2) << " " << mid1_is <<  " " << mid_is << " ===== " << end_is << endl;
                parent_res_idx = mid_idx <= 1 ? 0 : mid_idx - 1;
                return cal(N-1) + (parent_res_idx)*2 + mid1_is + mid_is + end_is;
            }
            //cout << mid_is + mid1_is  << " ;;;;;"  << endl;
            
            if ((mid_is + mid1_is > 0) && (mid_is + mid1_is < 4)) {
                parent_res_idx = mid_idx;
                break;
            }
            if (mid_is + mid1_is == 4) {
                beg_idx = mid_idx;
                mid_idx = beg_idx + end_idx + 1;
                mid_idx /= 2;
            } else {
                end_idx = mid_idx;
                mid_idx = beg_idx + end_idx + 1;
                mid_idx /= 2;
                //cout << end_idx << " sgfsgdsgds " <<mid_idx  << endl;
            }
            
        }
        parent_res_idx = mid_idx < 1 ? 0 : mid_idx - 1;
         //cout << cal(N-1) << " " << mid1_is <<  " " << mid_idx << " e " << parent_res_idx << endl;
        return cal(N-1) + parent_res_idx*2 + mid1_is + mid_is;
    }
    int countNodes(TreeNode* root) {
        return run(root);
    }
};
```
