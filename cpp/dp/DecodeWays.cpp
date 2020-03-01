/*
 * Given an encoded message containing digits, determine the total number of ways to decode it.
 * For example,
 * Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).
 *
 *
 * *******************************************************
 * The state equation is:
 * a[i] = max(a[i+1]+1, a[i+2]+2)
 * */
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <random>
#define mMax(a,b) ((a)>(b)?(a):(b))
using std::unordered_set;
using std::string;
using std::cout;
using std::vector;
using std::endl;
inline 
bool below26(unsigned char &a,
        unsigned char &b)
{
    return (a!=0?a*10+b < 27:false);
}
inline 
bool none0(unsigned char &c)
{
    return c!=0;
}
bool ifDecoded(vector<unsigned char> &A)
{
    int N = A.size();
    if (N == 0)return false;
    if (N == 1) return A[0] != 0;
    int N1 = N-1, N2 = N-2;
    vector<bool> b(N, false);
    for (int i = N1; i >= 0; i--)
    {
        if (i == N1)
        {
            if (A[i] != 0)
                b[i] = true;
        }
        else
        {
            if (i == N2)
            {
                if (A[i] != 0 && A[i+1] != 0)
                    b[i] = true;
                else
                {
                    if (A[i] == 0 && A[i+1] == 0)return false;
                    if (A[i] != 0 && A[i+1] == 0 && A[i] < 3)
                        b[i] = true;
                }
            }
            else
            {
                /*single*/
                b[i] = ((A[i]!=0) && b[i+1]) || (below26(A[i], A[i+1]) && b[i+2]);
            }
        }
    }
    return b[0];
}
bool ifDecoded(string &s)
{
    vector<unsigned char> A(s.size());
    std::transform(s.begin(), s.end(), A.begin(), [](char &c)->unsigned char{return c-48;});
    return ifDecoded(A);
}
int numDecodings(string s) 
{
    if (s.size() < 1)return int(s.size());
    /*az to 09*/
    vector<unsigned char> si(s.size());
    /*std::transform(s.begin(), s.end(), si.begin(), [](char &c)->unsigned char{return c-64;});*/
    std::transform(s.begin(), s.end(), si.begin(), [](char &c)->unsigned char{return c-48;});
    for (auto &i : si)cout << int(i) <<",";cout << endl;
    vector<int> a(si.size());
    int N1 = a.size()-1, t1, t2;
    int N2 = N1-1;
    for (int i = N1; i >= 0; --i)
    {
        if (i == N1)
        {
            a[i] = 1;
        }
        else
        {
            if (i == N2)
            {
               if (none0(si[i]) && none0(si[i+1]))
               {
                   a[i] = 1 + below26(si[i], si[i+1]);
               }
               else
               {
                   a[i] = 1;
               }
            }
            else
            {
                if (si[i] == 0)
                {
                    a[i] = a[i+1];
                }
                else
                {
                    if (si[i+1]==0 || si[i+2] == 0)
                    {
                        a[i] = a[i+2];
                    }
                    else
                    {
                        a[i] = a[i+1] + (below26(si[i],si[i+1])?a[i+2]:0);
                    }
                }
            }
        }
    }
    return a[0];
}

int main()
{
    /*          1234112   */
    string s = "1070";
//    cout << numDecodings(s)  << endl;
    cout << ifDecoded(s)  << endl;
    return 0;
}
