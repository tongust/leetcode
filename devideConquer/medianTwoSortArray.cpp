#include <iostream>
#include <vector>
#include <algorithm>
#include <algorithm>
#include <random>
using std::cout;
using std::vector;
using std::endl;
typedef vector<int> vint;
/*
 * Find the median of two sorted arrays.
 * */

double find1(vint::iterator b1, 
        vint::iterator e1,
        vint::iterator b2, 
        vint::iterator e2,
        const int & n_half)
{
    auto n1 = n_half / 2;
//    if (n1 <= 0)return 0;/////////////////////
//    cout << "n1\t" << n1 << "\tn_half\t" << n_half << endl;
    int m = e1 - b1, 
           n = e2 - b2;
    if (n_half == 1)
    {
        if (m >= 1 && n >= 1)
        {
            if ((*(b1)) > (*(b2)))
                return *(b2);
            else return *(b1);
        
        }
        if (m >= 1)
        {
            return *(b1);
        }
        else return *(b2);
    }
    if (m == 0)
    {
        return *(b2+n_half-1);
    }
    if (n == 0)
    {
        return *(b1+n_half-1);
    }

    int m_h = 0;
    int n_h = 0;
    if (m < n)
    {
        if (n1 < m)
        {
            m_h = n1;// 
            n_h = n_half - m_h;
        }
        else
        {
            m_h = m;
            n_h = n_half - m_h;
        }
    }
    else
    {
        if (n1 < n)
        {
            n_h = n1;
            m_h = n_half - n_h;
        }
        else
        {
            n_h = n;
            m_h = n_half - n_h;
        }
    }
    m_h--;n_h--;
//    cout << m_h << "," << n_h << endl;
    //if (m_h < 0)return 0;
    auto m_v = *(b1+m_h);
    auto n_v = *(b2+n_h);
    if (m_v < n_v)
    {
        return find1(b1+m_h+1, e1, b2, e2, n_half - m_h-1);
    }
    else
    {
        return find1(b1, e1, b2+n_h+1, e2, n_half - n_h-1);
    }
    return 0;




}
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    double res = 0.0;
    int M = nums1.size(), N = nums2.size();
    int mn_h = (M+N)/2;
    mn_h++;
    if ((M+N) % 2 == 0)
    {
        res = find1(nums1.begin(),nums1.end(), nums2.begin(), nums2.end(), mn_h-1)+
         find1(nums1.begin(),nums1.end(), nums2.begin(), nums2.end(), mn_h);
        res /= 2.0;
    }
    else
        res = find1(nums1.begin(),nums1.end(), nums2.begin(), nums2.end(), mn_h);
    return res*1.0;
}

int main()
{
    vint A{1,4,7,10};
    vint B{-1,0,2};
    int n_half = 4;
//    cout << find1(A.begin(),A.end(), B.begin(), B.end(), n_half) << endl;
    cout << findMedianSortedArrays(A, B) << endl;


    return 0;
}
