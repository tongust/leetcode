#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include <iterator>
#define MBEG -1
#define MEND -2
using std::cout;
using std::list;
using std::vector;
using std::endl;
using std::string;
class zuma
{
public:
    int id;
    int fr;
    // default construct
    zuma():id(0),fr(0){}
    zuma(const int&i):id(i),fr(0){}
    zuma(const int&i, const int &f):id(i),fr(f){}
    // copy construct
    zuma(const zuma& z): id(z.id), fr(z.fr){}
    // copy assignment operator
    zuma& operator=(const zuma &z)
    {
        id = z.id;
        fr = z.fr;
        return *this;
    }
    bool operator==(const zuma &rhs)
    {
        return id == rhs.id;
    }
    bool operator==(const int &rhs_id)
    {
        return id == rhs_id;
    }
    bool operator!=(const zuma &rhs)
    {
        return id != rhs.id;
    }
    bool operator!=(const int &rhs_id)
    {
        return id != rhs_id;
    }
    // delete function
    ~zuma(){}

};
bool operator==(const zuma &lhs, const zuma &rhs)
{
    return lhs.id == rhs.id;
}
bool operator!=(const zuma &lhs, const zuma &rhs)
{
    return lhs.id != rhs.id;
}

std::ostream &operator<<(std::ostream &os, const zuma &z)
{

    char mmm[7] = {'R','Y','B','G','W'};
    if (z.id < 0)
        os << "[ " << z.id << "|" << z.fr << " ]";
    else
        os << "[ " << mmm[z.id] << "|" << z.fr << " ]";

    return os;
}
char mapf1(int i)
{
    switch(i)
    {
        case 0:
            return 'R';
        case 1:
            return 'A';
    }
}
template <class T>
inline 
void print_1d(const T& vs)
{
    for (auto &i : vs)
    {
        std::cout << i << "\t";
    }
    std::cout << std::endl;
    return;
}
template <class T>
inline 
void print_2d(const T& vss)
{
    for (auto &i : vss)
        print_1d(i);
    return;
}
// R Y B G M    
int f1(list<zuma> &zl, 
        char *h, 
        int sum) 
{
    return 0;
}
int f2(list<zuma> &zl, // ball on board
        char *h,
        int sum) // left ball at hand
{
    //cout << sum << "-\n";
    // the condition under which the recursive function terminates
    auto N = zl.size()-2; // size of on board.
    if (N == 0 && sum >= 0)
        return sum;
//        {cout <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<sum<<"\n\n\n\n\n\n";print_1d(zl);return sum;}
    if (sum <= 0)// not enough ball at hands to cost
    {
        if (sum == 0 && N == 0) // sum < 0
        {cout <<"300\n\n\n\n\n\n";return 0;}
        else
            return -1;
    }
    if (N < 3) // the size of on board is <= 2
    {
        if (N == 0)// already finish.
            return sum;
          //  {cout <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n\n\n\n\n";return sum;}
        if (N == 1)// one left
        {
            auto it = zl.end();it--;it--;
            if (h[it->id]+it->fr > 2)
                return (sum - 3 + it->fr);
                //{cout <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n\n\n\n\n";return sum-3+it->fr;}
            else
                return -1;
        }
        if (N == 2)
        {
            auto t1 = zl.begin();t1++;
            auto t2 = zl.end();t2--;t2--;
            if (h[t1->id]+t1->fr > 2 && h[t2->id]+t2->fr > 2)
                return (sum + t1->fr + t2-> fr - 6);
            else
                return -1;
        }
    }
    int res = -1;
    list<zuma> zl_bk = zl;;
    int mc = -1;
    auto iter = zl.begin();iter++;
    auto iter_e = zl.end();iter_e--;
    auto m0 = zl_bk.begin();
    auto m1 = zl.end();
    auto mt = m0;
    auto mt_pre = mt;
    char h_bk[5];
    int sum_bk = sum;
    int cost_now = 0;
    int cost_next = 0;
//    cout << "----" << sum << endl;
//    return res;////////////////////////////////////////////////////////
    vector<int> ress(N,-1);
    for (int i11 = 0; i11 != N; i11++)
    {
        res = -1;
        mc++;
        zl_bk = zl;
        std::copy(h, h+5, h_bk);
        sum_bk = sum;
        m0 = zl_bk.begin();
        m0++; // jump up the head
        mt = std::next(m0, mc);// keeps same with iter.
        int t1 = h[iter->id] + iter->fr;
        if (t1 > 2)// enough to allot the ball.
        {
            cost_now = 3 - iter->fr;
            h_bk[iter->id] -= cost_now;
            sum_bk -= cost_now;

            const char mmm[7] = {'R','Y','B','G','W'};
           // cout << ">\t";print_1d(zl_bk); for (int i = 0; i!=5; ++i){cout << mmm[i] << "|"<< int(h_bk[i]) << ",";}cout << endl;
            mt = zl_bk.erase(mt); // delete this element
            while(mt->id >= 0)
            {
                mt_pre = mt;
                mt_pre--;
                if (mt_pre->id == mt->id)
                {
                    mt_pre->fr += mt->fr;
                    zl_bk.erase(mt);
                    if (mt_pre->fr > 2)
                        mt = zl_bk.erase(mt_pre);
                }
                else break;
            }
//            cout <<sum_bk << "\t\t";/////////////////////////////////////////
           // cout << ">\t";print_1d(zl_bk);
           // cout << sum << "," << cost_now << endl;
            cost_next = f2(zl_bk, h_bk, sum_bk);
//            cout << cost_next << "sda" << endl;
            if (cost_next == -1)
            {
                res = -1;
            }
            else
            {
                if (res < cost_next)
                    res = cost_next;
            }
        }
        else 
        {
            cost_now = 0;
            if (h_bk[iter->id]>0)
            {
                cost_now = -1;
            }
            cost_next = cost_now + res;
            if (res < cost_next)
                res = cost_next;
        }
        iter++;
        ress[i11] = res;
    }
    res = *std::max_element(ress.begin(), ress.end());
    return res;

}
int find(string board, string hand)
{
    char h[5] = {0,0,0,0,0};
    auto mapf = [](const char &c)->int 
    {
        switch (c)
        {
            case 'R':
                return 0;
            case 'Y':
                return 1;
            case 'B':
                return 2;
            case 'G':
                return 3;
            case 'W':
                return 4;
            default:
                return 127;
        }
    };// lambda function
    for (auto &i : hand)
    {
        h[mapf(i)]++;
    }
    list<zuma> bl;
    auto N_b = board.size();
    bl.push_back(zuma(-1, 0));// marked -1 as head of list
    bl.push_back(zuma(mapf(board[0]), 1));
    for (int i = 1; i < N_b; ++i)
    {
        int newid = mapf(board[i]);
        if (newid != bl.back())
        {
            bl.insert(bl.end(), zuma(newid, 1));
        } 
        else
        {
            bl.back().fr++;
        }

    }
    bl.insert(bl.end(), zuma(-2,0));// mark as tail of list
    print_1d(bl);
    cout << f2(bl, h, hand.size()) << "\t>>>>" << endl;
    return 0;
}

void callf(int a, void(*f)(int))
{
    return f(a);
}


int main()
{
    string board = "WRRBBW";
    //string board = "BB";
    string hand = "RW";
    cout << "RYBGW"<< endl;
    cout << "board\t" << board << endl;
    cout << "hand\t" << hand << endl;
    list<zuma> zl;
    zl.push_back(zuma(1,1));
    zl.push_back(zuma(3,2));
    zl.push_back(zuma(2,0));
    //auto i1 = zl.begin();i1++;
    //i1 = zl.erase(i1);
    //print_1d(zl);
    find(board, hand);
    int h[3] = { 2,3,4 };
    int p[3];
    std::copy(h, h+3, p);
    //std::copy(p, p+3, std::ostream_iterator<int>(std::cout, ",\n"));
    return 0;
}
