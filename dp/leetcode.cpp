#include <iostream>

#include <vector>
#include <string>

#include <unordered_map>
#include <unordered_set>


#include "minCut.h"


/* Usings */

using std::cout;
using std::cin;
using std::endl;

using std::unordered_map;
using std::unordered_set;
using std::string;
using std::vector;

int main() {
    string s = "aab";
    cout << minCut1(s) << endl;

    return 0;
}
