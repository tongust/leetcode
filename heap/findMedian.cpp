#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class MedianFinder {

private:

    double med;

public:

    vector<int> bignums;

    vector<int> litnums;

    size_t len;



    /** initialize your data structure here. */

    MedianFinder() {

        len = 0;

        med = 0;

    }

    

    void addNum(int num) {

        len++;
        if (len==1) {
            litnums.push_back(num);
            return;
        }
        if ((len-1)%2 == 0) { // add to litnum

            if (num < bignums.front()) {

                litnums.push_back(num);

                push_heap(litnums.begin(), litnums.end()/*<*/);

            } else {

                bignums.push_back(num);

                push_heap(bignums.begin(), bignums.end(), [](const int&lhs,const int&rhs)->bool{return lhs>rhs;});

                

                litnums.push_back(bignums.front());

                push_heap(litnums.begin(), litnums.end());

                

                pop_heap(bignums.begin(), bignums.end(), [](const int&lhs,const int&rhs)->bool{return lhs>rhs;});

                bignums.pop_back();

                

            }

            med = litnums.front();

        } else { // add to bignum

            if (num > litnums.front()) {

                bignums.push_back(num);

                push_heap(bignums.begin(), bignums.end(), [](const int&lhs,const int&rhs)->bool{return lhs>rhs;});

            } else {

                litnums.push_back(num);

                push_heap(litnums.begin(), litnums.end());

                

                bignums.push_back(litnums.front());

                push_heap(bignums.begin(), bignums.end(), [](const int&lhs,const int&rhs)->bool{return lhs>rhs;});

                

                pop_heap(litnums.begin(), litnums.end());

                litnums.pop_back();

            }

            med = litnums.front() + bignums.front();

            med /= 2.0;

        }

        return;

    }

    

    double findMedian() {

        return med;

    }

};


int main() {
    MedianFinder d;
    d.addNum(1);
    d.addNum(2);    
    d.addNum(3);    
    d.addNum(4);    
    d.addNum(5);    
    d.addNum(6);    
    for (auto i : d.litnums) cout << i << ",";cout << endl;
    for (auto i : d.bignums) cout << i << ",";cout << endl;
    cout << d.findMedian();
    return 0;
}
