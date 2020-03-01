#include <iostream>
#include <math.h>
#include <map>
#include <climits>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
/* the default hash function exists in <functional> for "comman" types, all floating-point types, pointers, strings, and some special
 * type (error_code, thread:id, bitset<>, and vector<bool>) 
 * */
#include <functional>
using std::hash;
using std::pair;
using std::cout;
using std::vector;
using std::endl;
using std::unordered_map;
using std::unordered_set;
using std::string;
using std::ostream;
typedef vector<int> vint;
typedef unsigned long long ull64;
struct Point
{
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(const int &a, const int &b) : x(a), y(b) {}
};

typedef pair<double, double> pairdd;
/*
 * Combine hash function 
 * From boost: http://www.boost.org/doc/libs/1_35_0/doc/html/hash/combine.html 
 * */
template<typename T>
inline void hash_combine (std::size_t& seed, const T& val) 
{
    seed ^= std::hash<T>{} (val) + 0x9e3779b9 + (seed<<6) + (seed>>2);return;
}
/*
 * First:
 *  Providing Hash Function
 * */
class pairHash2D
{
public:
    std::size_t operator() (const pairdd& c) const 
    {
        std::size_t seed = 10;
        hash_combine(seed, c.first);
        hash_combine(seed, c.second);
        return seed;
    }

};
/*
 * Second:
 * Providing Equivalence Criterion (default)
 *
 * */
inline
pairdd calAC(const Point &p1, const Point &p2)
{
    if (p1.x == p2.x)
    {
        return pairdd(std::numeric_limits<double>::max(), p1.x);
    }
    else
    {
        pairdd res;
        res.first = double(p1.y*1.0-p2.y*1.0)/(p1.x-p2.x);
        res.second = p1.y - res.first*p1.x;
        return res;
    }
}
inline
pairdd calAC(const pairdd &p1, const pairdd &p2)
{
    const int PR = 1000;
    if (p1.first == p2.first)
    {
        //return pairdd(std::numeric_limits<double>::max(), p1.first);
        return pairdd(std::numeric_limits<double>::max(), int(p1.first*PR));
    }
    else
    {
        pairdd res;
        res.first = double(p1.second*1.0-p2.second*1.0)/(p1.first-p2.first);
        res.second = p1.second - res.first*p1.first;
        res.first = int(res.first*PR);
        res.second = int(res.second*PR);
        return res;
    }
}
#if 0
int maxPoints(vector<Point> points)
{
    unordered_map<pairdd, int, pairHash2D> crossHashMap;
    unordered_map<pairdd, int, pairHash2D> uniq_points;
    for (auto &p: points)
    {
        auto resf = uniq_points.find(pairdd(p.x,p.y));
        if (resf != uniq_points.end())
        {
            resf->second++;
        }
        else
        {
            uniq_points[pairdd(p.x, p.y)] = 1;
        }
    }
    if (uniq_points.size() <= 2) return points.size();
    // refill the points
    points.clear();
    points.resize(uniq_points.size());
    int mcc = -1;
    for (auto &it : uniq_points)
    {
        mcc++;
        points[mcc] = Point(it.first.first, it.first.second);
    }
    /*auto factorF = [](const int& m)->int {return (m*(m-1)/2);};*/
    int res = 0;
    auto resf = crossHashMap.end();
    auto resf1 = crossHashMap.end();
    pairdd tmp;
    int m1 = 0, m2 = 0;
    for (auto it0 = points.begin(); it0 != points.end(); ++it0)
    {
//        m2 = uniq_points[pairdd(it0->x, it0->y)];
        for (auto it1 = it0+1; it1 != points.end(); ++it1)
        {
            tmp = calAC(*it0, *it1);
            resf = crossHashMap.find(tmp);
//            m1 = uniq_points[pairdd(it1->x, it1->y)] + m2;/* !!! */
//            m1 = m1*( m1-1 )/2;
            if (resf != crossHashMap.end())
            {/* find */
                resf->second++;
                if (res < resf->second)
                    res = resf->second;
            }
            else
            {
                crossHashMap[tmp] = 1;
                if (res < m1)
                    res = m1;
            }
        }
    }
    /* again */
    auto crossHashMap1 = crossHashMap;
    for (auto it0 = points.begin(); it0 != points.end(); ++it0)
    {
        m2 = uniq_points[pairdd(it0->x, it0->y)];
        for (auto it1 = it0+1; it1 != points.end(); ++it1)
        {
            m1 = uniq_points[pairdd(it1->x, it1->y)] + m2;/* !!! */
            m2 = m2 - 2;
            tmp = calAC(*it0, *it1);
            resf1 = crossHashMap1.find(tmp);
            resf = crossHashMap.find(tmp);
            if (resf1->second == resf->second)
                resf1->second+= m2;
        }
    }

    if (res == 0)res = 1;
    for (auto &i : crossHashMap)
        cout << i.first.first << "," << i.first.second << ", " << i.second << endl;
    return ((1+sqrt(1+8.0*res))/2);
}
#endif 
int maxPoints(vector<Point> &ps)
{
    unordered_set<int> tst1;
    vector<pairdd> points(ps.size());
    if (points.size() == 0) return 0;
    if (points.size() < 3) return points.size();
    int mcc = -1;
    for (auto &it : ps)
    {
        mcc++;
        points[mcc] = pairdd(it.x, it.y);
    }
    unordered_map<pairdd, unordered_set<unsigned int>, pairHash2D> crossHashMap;
    int N = points.size();
    pairdd tmp;
    for (int i = 0; i < N; i++)
    {
        for (int j = i+1; j < N; j++)
        {
            tmp = calAC(points[i], points[j]);
            if ( int(tmp.first*10) == 4 && int(tmp.second*10) == 160 )
            {
                cout << i << ">>>>" << j << "\t" << tmp.first << "," << tmp.second << endl;
                tst1.insert(i);
                tst1.insert(j);
            }
            crossHashMap[tmp].insert(i);
            crossHashMap[tmp].insert(j);
        }
    }
    int res = 0;
    int t1 = 0;
    for (auto &it : crossHashMap)
    {
        t1 = it.second.size();
        if (res < it.second.size())
            res = t1;
        if (res == 21) 
        {
            cout << it.first.first << "===" << it.first.second << endl;
            for (auto &j : it.second)
                cout << j << ",";
            cout << endl;
            break;
        }
    }
    cout << "test\t" << tst1.size() << endl;
    for (auto &i : tst1) cout << i << ","; cout << endl;
    return res;
}
int main()
{
    /*
    unordered_map<pair<double, double>, int, pairHash2D> crossMap;
    crossMap[pairdd(0.0, 12.2)] = 12;
    auto resf = crossMap.find(pairdd(0.0, 12.2));
    if (resf != crossMap.end())
        cout << resf->second << endl;
        */
    vector<Point> points =
{Point(560,248),Point(0,16),Point(30,250),Point(950,187),Point(630,277),Point(950,187),Point(-212,-268),Point(-287,-222),Point(53,37),Point(-280,-100),Point(-1,-14),Point(-5,4),Point(-35,-387),Point(-95,11),Point(-70,-13),Point(-700,-274),Point(-95,11),Point(-2,-33),Point(3,62),Point(-4,-47),Point(106,98),Point(-7,-65),Point(-8,-71),Point(-8,-147),Point(5,5),Point(-5,-90),Point(-420,-158),Point(-420,-158),Point(-350,-129),Point(-475,-53),Point(-4,-47),Point(-380,-37),Point(0,-24),Point(35,299),Point(-8,-71),Point(-2,-6),Point(8,25),Point(6,13),Point(-106,-146),Point(53,37),Point(-7,-128),Point(-5,-1),Point(-318,-390),Point(-15,-191),Point(-665,-85),Point(318,342),Point(7,138),Point(-570,-69),Point(-9,-4),Point(0,-9),Point(1,-7),Point(-51,23),Point(4,1),Point(-7,5),Point(-280,-100),Point(700,306),Point(0,-23),Point(-7,-4),Point(-246,-184),Point(350,161),Point(-424,-512),Point(35,299),Point(0,-24),Point(-140,-42),Point(-760,-101),Point(-9,-9),Point(140,74),Point(-285,-21),Point(-350,-129),Point(-6,9),Point(-630,-245),Point(700,306),Point(1,-17),Point(0,16),Point(-70,-13),Point(1,24),Point(-328,-260),Point(-34,26),Point(7,-5),Point(-371,-451),Point(-570,-69),Point(0,27),Point(-7,-65),Point(-9,-166),Point(-475,-53),Point(-68,20),Point(210,103),Point(700,306),Point(7,-6),Point(-3,-52),Point(-106,-146),Point(560,248),Point(10,6),Point(6,119),Point(0,2),Point(-41,6),Point(7,19),Point(30,250)};
    cout << maxPoints(points) << endl;
    return 0;
}
