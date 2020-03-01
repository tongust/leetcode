/*
 * split the number
 * Such 4: 4 | 3 1 | 2 2 | 1 1 1 1
 */

#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <algorithm>
using namespace std;

typedef pair<int, int> pint;
typedef vector<pint> vpint;
typedef vector<int> vint;
typedef vector<vint> vvint;
void foo(vvint &dp, int k, int m)// 5 2
{
	if (dp[k][m] != -1)return;
	int left = k - m;
	int res = 0;
	for (int i = 1; i <= m && i <= left; ++i) {
		foo(dp, left, i);
		res += dp[left][i];
	}
	dp[k][m] = res;
}

int run(int n) {
	vvint dp(n+1, vint(n+1,-1));
	for (int i = 0; i < n + 1; ++i)
	{
		dp[i][i] = 1;
		dp[i][1] = 1;
		dp[i][0] = dp[0][i] = 0;
	}
	int res = 0;
	for (int i = 1; i <= n; ++i) {
		foo(dp, n, i);
		res += dp[n][i];
	}
	return res;
}


int main()
{
	int n;
	
	while (cin >> n)
	{
		cout << run(n) << endl;
	}
	return 0;

}
