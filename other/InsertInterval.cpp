#include <iostream>
#include <vector>
using std::cout;
using std::vector;
using std::endl;

struct Interval
{
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
    int start, end;
};

int findV(vector<int>& ms, const int &v)
{
    int left = 0, right = ms.size() - 1, res = 0;
    int med = (left+right)/2;
    while (left <= right)
    {
        if (ms[left]>= v) {res = left;break;}
        if (ms[right] == v) {res = right; break;}
        if (ms[med] == v) {res = med;break;}
        if (v < ms[med])
        {
            right = med;
        }
        else
        {
            left = med;
        }
        med = (left+right)/2;
        if (right - left == 1)
        {
            if (ms[left] == v){res = left; break;}
            else {res = right; break;}
        }
    }
    return res;
}
vector<Interval> insert(vector<Interval>& intervals, Interval newInterval)
{
    vector<Interval> res;
    vector<int> mlist(intervals.size()*2);
    if (intervals.empty()){res.push_back(newInterval);return res;}
    if (newInterval.start > (intervals.end()-1)->end )
    {
        res = intervals;
        res.push_back(newInterval);
        return res;
    }
    for (int i = 0; i < intervals.size(); ++i)
    {
        mlist[i<<1] = intervals[i].start;
        mlist[(i<<1)+1] = intervals[i].end;
    }
    int left = findV(mlist, newInterval.start);
    int right = findV(mlist, newInterval.end);
    int tmp = 0, tmp1 = 0, tmp2 = 0;
    Interval v1;
    if (left%2 == 0)
        v1.start = newInterval.start;
    else
        v1.start = mlist[left-1];
    res.resize((left/2));
    std::copy(intervals.begin(), intervals.begin()+res.size(), res.begin());
    if (right%2 == 0)
    {
        if (mlist[right] == newInterval.end)
        {
            v1.end = mlist[right+1];
            tmp = (right+2)/2;
        }
        else
        {
            v1.end = newInterval.end;
            tmp = right/2;
        }
    }
    else
    {
        v1.end = mlist[right];
        tmp = (right+2)/2;
    }
    res.push_back(v1);
    tmp2 = intervals.size() - tmp;
    tmp1 = res.size();
    res.resize(tmp1+tmp2);
    std::copy(intervals.begin()+tmp, intervals.end(), res.begin()+tmp1);
    if (newInterval.end > (*(res.end()-1)).end)
    {
        (*(res.end()-1)).end = newInterval.end;
    }
    return res;
}
 int main()
{
    vector<int> ms{1,3,5,6,9,12, 13, 15};
    vector<Interval> intervals(ms.size()/2);
    int mcc = -1;
    for (int i = 0; i < intervals.size(); ++i)
    {
        intervals[i] = Interval(ms[i<<1], ms[(i<<1)+1]);
    }
    for (auto &i : intervals) cout << i.start << "," << i.end << endl;
    Interval vl(-1,1);
    auto res = insert(intervals, vl);
    cout << "------------" << endl;
    for (auto &i : res) cout << i.start << "," << i.end << endl;
    return 0;
}
