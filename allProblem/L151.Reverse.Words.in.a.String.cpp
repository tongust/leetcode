#include <iostream>
#include <string>
#define TT ','


using namespace std;
class Solution {
public:
    void Rev(string &s, int b, int e) {
        int med = (b+e)/2;
        for (int o = b; o < med; o++) {
            s[o] = s[o]^s[e-1-(o-b)];
            s[e-1-(o-b)] =  s[o]^s[e-1-(o-b)];
            s[o] =  s[o]^s[e-1-(o-b)];
        }
        return;
    }
    void rev0s(string &s, int b, int e) {
        if (b>=e || e >= s.size())return;
        Rev(s, b, s.size());
        for (int i = e-b; i > 0;--i) {
            s.pop_back();
        }
        Rev(s,b,s.size());
        return;
    }
    void reverseWords(string &s) {
        // clean
        // clean head and tail
        // head
        {
            int a = s.size()-1;
            while(s[a]==TT&& a>0) {
                a--;
                s.pop_back();
            }
        }
        auto lmd = s.size()/2;
        for (size_t i = 0; i < lmd; ++i) {
            char t0 = s[i];
            s[i] = s[s.size()-1-i];
            s[s.size()-1-i] = t0;

        }
        // tail
        {
            int a = s.size()-1;
            while(s[a]==TT&& a>0) {
                a--;
                s.pop_back();
            }
        }
        // reverse
        for (int i = 0; i < s.size();) {
            int a = i;
            while (s[a]!=TT && a < s.size()) {
                a++;
            }
            Rev(s,i,a);
            while (s[a]==TT && a < s.size()) {
                a++;
            }
            i=a;
        }
        // remove the 0s
        for (int i = 0; i < s.size(); ++i){
            int a = i;
            while (s[a] == TT && a<s.size()) {
                a++;
            }
            if (a-i>1) {
                int b = i+1, e = a;
                rev0s(s,b,e);
            }
        }
        if (s[0]==TT) s.clear();
        
    }// end of function
};
int main() {
    string s = ",,,,,,,,";
    cout << s << endl;
    Solution s1;
    s1.reverseWords(s);
    cout << s << endl;


    return 0;

}
