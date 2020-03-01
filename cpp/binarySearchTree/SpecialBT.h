#include <iostream>

#include <vector>
#include <string>

#include <unordered_map>
#include <unordered_set>

#include <math.h>       /* log2 */

#define PRINT1D(v,d) do {for (auto it_print : v) cout << it_print << d; cout << endl;}while(0)

#define MDebugLog(msg)  std::cout << __FILE__ << ":" << __LINE__ << ": " << msg << endl
/* Usings */

using std::cout;
using std::cin;
using std::endl;

using std::unordered_map;
using std::unordered_set;
using std::string;
using std::vector;

class snode {
public:
    snode() = default;
    snode(int k, int d, int l, int r) 
        : key(k), data(d), sumLeft(l), sumRight(r) {  }
    int key;
    int data;
    int sumLeft;
    int sumRight;
    int pos;
    int GetTotalData() {return data+sumLeft+sumRight;}
    int GetChildrenData() {return sumLeft+sumRight;}
};


class NumArray {
public:
    NumArray(vector<int> nums) {
        len = nums.size();
        int tmp = int(log2(len*1.0+2.0));
        if (len+2 == (1<<tmp)) 
            high = tmp;
        else high = tmp+1;
        N = (1<<high) - 1;
        idx2idxOfTree.resize(N, 0);
        vector<int> bs(N, 0);
        int c = -1;
        for (int i = 0; i < high; ++i) {
            int a0 = (1 << (high-1-i)) - 1;
            for (int i0 = 0; i0 < (1 << i); ++i0) {
                c++;
                int b = a0 + i0 * ( 1 << (high-i) );
                idx2idxOfTree[b] = c;
                bs[c] = b;
            }
        }
        vsnode.resize(N);
        sumArray = 0;
        c = -1;
        for (auto i : bs) {
            c++;
            vsnode[c].key = i;
            vsnode[c].pos = c;
            vsnode[c].data = i >= len ? 0 : nums[i];
            sumArray += vsnode[c].data;
        }
        for (int i = N-1; i > 0; --i) {
            if (i % 2 == 0) {
                vsnode[pre(i)].sumRight += vsnode[i].data + vsnode[i].sumLeft + vsnode[i].sumRight;
            } else {
                vsnode[pre(i)].sumLeft += vsnode[i].data + vsnode[i].sumLeft + vsnode[i].sumRight;
            }
        }
        //for (auto i : vsnode) { cout << i.key << " " << i.data << " " << i.sumLeft+i.sumRight << endl; }
    }
    int pre(int idx) {
        if (idx < 3) {
            return int(idx/2.0+0.5) - 1;
        }
        int h = (int) log2(idx+2.0);
        if (idx == (1<<h) - 2)
            return (1<<(h-1)) - 2;
        int b_0 = (1 << (h-1)) - 2;
        int b_1 = (1 << h) - 2;
        return b_0 + int (((idx - b_1)/2.0)+0.5);
    }
    /* Big-O is ln(n) */
    void update(int i, int val) {
        int idxT = idx2idxOfTree[i];
        snode* sn = &vsnode[idxT];
        int upd = val - sn->data;
        sumArray += upd;
        sn->data = val;
        while (sn->pos != 0) {
            if (sn->pos % 2 == 0) {
                sn = &vsnode[pre(sn->pos)];
                sn->sumRight += upd;
            } else {
                sn = &vsnode[pre(sn->pos)];
                sn->sumLeft += upd;
            }
        }
        //cout << "after:\n";
        //for (auto i : vsnode) { cout << i.key << " " << i.data << " " << i.sumLeft+i.sumRight << endl; }
    }
    
    int LastRightAncestor(int n) {
        if (n == 0 || n % 2 == 1) return n;
        n = pre(n);
        while (n % 2 == 0 && n != 0) {
            n = pre(n);
        }
        return n;
    }
    int LastLeftAncestor(int n) {
        if (n%2 == 0) return n;
        n = pre(n);
        while (n%2 == 1)
        {
            n = pre(n);
        }
        return n;
    }
    /* Big-O is ln(n) */
    int sumRange(int i, int j) {
        i = idx2idxOfTree[i];
        j = idx2idxOfTree[j];
        int less = vsnode[i].sumLeft,
            more = vsnode[j].sumRight,
            comA = commonAncestor(i,j);
        int i_pre = i,
            j_pre = j;
        int total_data = vsnode[comA].GetTotalData();
        //MDebugLog(string("less ") + std::to_string(less));
        //MDebugLog(string("more ") + std::to_string(more));
        //MDebugLog(string("comA ") + std::to_string(comA));
        //MDebugLog(string("total_data ") + std::to_string(vsnode[comA].data));
        while (i_pre != comA) {
            i_pre = pre(i_pre);
            if (vsnode[i_pre].key < vsnode[i].key)
                less += vsnode[i_pre].data + vsnode[i_pre].sumLeft;
        }
        while (j_pre != comA) {
            j_pre = pre(j_pre);
            if (vsnode[j_pre].key > vsnode[j].key)
                more += vsnode[j_pre].data + vsnode[j_pre].sumRight;
        }
        //for (auto it : vsnode) cout << it.data << " " << it.key << endl;
        return total_data - more - less;
        
    }
    int levelInTree(int idxOfTree) { 
        int lev = 0;
        int tmp = int(log2(idxOfTree*1.0+2.0));
        if (idxOfTree+2 == (1<<tmp)) 
            lev = tmp;
        else lev = tmp+1;
        return lev;
        
    }
    int commonAncestor(int i, int j) {
        int lev_i = levelInTree(i),
            lev_j = levelInTree(j);
        if (lev_i < lev_j) {
            int loop = lev_j - lev_i;
            while (loop-- != 0) {
                j = pre(j);
            }
        }
        else if (lev_i > lev_j){
            int loop = lev_i - lev_j;
            while (loop-- != 0) {
                i = pre(i);
            }
        }
        // equal levels
        if (i == j) return i;
        int i_pre = pre(i),
            j_pre = pre(j);
        while (i_pre != j_pre) {
            i_pre = pre(i_pre);
            j_pre = pre(j_pre);
        }
        return i_pre;
    }
//private:
    int len;
    int high;
    int N;
    vector<int> idx2idxOfTree;
    vector<snode> vsnode;
    int sumArray;
};
