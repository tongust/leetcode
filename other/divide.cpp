#include <iostream>
#include <limits>
#include <vector>
using std::cout;
using std::vector;
using std::endl;
int divide(int a2, int b2)/*a / b*/
{
    if (b2 == 0) return (a2>0?std::numeric_limits<int>::max():std::numeric_limits<int>::min());
    if (b2 == 1 ) return a2;
    if (b2 == -1) 
    {
        if (a2 == std::numeric_limits<int>::min())
            return std::numeric_limits<int>::max();
        else
            return -a2;
    }
    bool flg = true;
    if ((a2>=0 && b2<=0) || (a2<=0 && b2>=0)) flg = false;
    
    /* assure that a and b both are positive int */
    unsigned long long a = 0, b = 0;
    if (a2 < 0)
    {
        a2++;
        a = -a2;
        a++;
    }
    else a = a2;
    if (b2 < 0)
    {
        b2++;
        b = -b2;
        b++;
    }
    else b = b2;
    int c = 0;
    cout << a << ","  << b << endl;
    unsigned long long a1 = a, b1 = b, t1 = 0;
    c = 0;
    int res = 0;
    for(;;)
    {
        if (a1 < b) break;
        b1 = b;
        c = 0;
        for(;;)
        {
            c++;
            t1 = b1;
            b1 = b1<<1;
            if (a1 < b1)
            {
                b1 = t1;
                c--;
                break;
            }
        }
        res += 1<<c;
        a1 -= b1;
    }
    res = flg?res:-res;
    return res;
}
int main()
{
    int a = -2147483648, b = 3;
    long unsigned int c = -a;
    a++;
    c = -a;
    c++;
    cout << c << endl;
    cout << divide(a,b) << "," << (a/b) << endl;
}
