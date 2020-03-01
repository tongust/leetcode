#include <iostream>
#include <vector>
#include <algorithm>
using std::cout;
using std::vector;
using std::endl;
#define IF132PATTERN(x, y, z) ( ( (x) < (z)  ) & ( (z) < (y) )  )
/*
 * The binary heap data structure is an array object that 
 * we can view as a nearly complete binary tree.
 * */
typedef vector<int> vint;
class myHeap
{
public:
    myHeap() = default;
    int parent(const int &i)
    {
        return int(i/2.0);
    }
    int left(const int &i)
    {
        return (2*i);
    }
    int right(const int &i)
    {
        return (2*i + 1);
    }
    void max_heapify(vint &A, const int &i)
    {
        if (A.empty())return;
        int l = left(i);
        int r = right(i), largest = i;
        if ((l < A.size() ) && (A[l] > A[i]))// index begin ar 0.
        {
            largest = l;
        }
        else
            largest = i;
        if ((r < A.size()) && (A[r] > A[largest]))
            largest = r;
        if (largest != i)
        {
            int temp = A[i];
            A[i] = A[largest];
            A[largest] = temp;
            max_heapify(A, largest);
        }
        return;
    }
    void max_heapify(const int &i)
    {
        max_heapify(H, i);
    }

    void buildMaxHeap(vint &A)
    {
        auto heap_size = A.size();
        for (int i = int(heap_size/2); i >= 1; --i)
        {
            max_heapify(A, i-1);
        }
        return;
    }

    void heap_sort(vint & A, vint &res)
    {
        res = A;
        buildMaxHeap(A);
        size_t mc = 0;
        for (int i = A.size(); i >= 1; --i)
        {
            int i1 = i - 1;
            // exchange A[0] with A[i1]
            int temp = A[0];
            A[0] = A[i1];
            res[mc] = temp;
            A.pop_back();
            mc++;
            max_heapify(A, 0);
        }
    }
public:
        vint H;

};

bool find2(vint & nums);
int main()
{
    myHeap hp;
    vint A{0,12,123,12331,3123,123123,113,123,123,123,123,3,8,5,2}, B;
    hp.heap_sort(A, B);
    for (auto i : B)
        cout << i << ",";
    cout << endl;
    return 0;
}


bool find2(vint & nums)
{
    if (nums.size() < 3) return false;
    myHeap hp;
    vint nums1(nums.size()-2);
    std::copy(nums.begin()+2, nums.end(), nums1.begin());
    hp.buildMaxHeap(nums1);
    auto N = nums.size() - 1;
    int L = nums[0], M = 0, R = 0, tmp = 0;
    for (int i = 1; i < N; i++)
    {
        M = nums[i];
        R = nums1[0];
        if (IF132PATTERN(L, M, R))
            return true;
        // exchange num1[0] with num1[end]
        
        if (L > M)
            L = M;
    }
    return false;
}
