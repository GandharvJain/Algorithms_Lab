#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef vector<ll> vl;
typedef vector<vl> vvl;

#define NORTH 'H'		//H for Horizontally left
#define WEST 'V'		//V for Vertically up
#define NORTH_WEST 'D'	//D for Diagonally up left

typedef struct Node {
	ll len;
	char dir;
} Node;

string lcsString(const vector<vector<Node>> &lcs, const string &x, ll i, ll j) {
	if (i == 0 || j == 0)
		return "";
	if (lcs[i][j].dir == NORTH_WEST)
		return lcsString(lcs, x, i - 1, j - 1) + x[i - 1];
	else if (lcs[i][j].dir == NORTH)
		return lcsString(lcs, x, i - 1, j);
	else
		return lcsString(lcs, x, i, j - 1);
}

string longestCommonSubsequenceDP(string x, string y, bool print_order = true) {
	ll m = x.size(), n = y.size();
	vector<vector<Node>> lcs(m + 1, vector<Node>(n + 1));

	for (ll i = 0; i <= m; ++i)
		lcs[i][0].len = 0;
	for (ll j = 0; j <= n; ++j)
		lcs[0][j].len = 0;

	for (ll i = 1; i <= m; ++i) {
		for (ll j = 1; j <= n; ++j) {
			if (x[i - 1] == y[j - 1]) {
				lcs[i][j].len = lcs[i - 1][j - 1].len + 1;
				lcs[i][j].dir = NORTH_WEST;
			}
			else if (lcs[i - 1][j].len >= lcs[i][j - 1].len) {
				lcs[i][j].len = lcs[i - 1][j].len;
				lcs[i][j].dir = NORTH;
			}
			else {
				lcs[i][j].len = lcs[i][j - 1].len;
				lcs[i][j].dir = WEST;
			}
		}
	}

	string str = to_string(lcs[m][n].len);
	if (print_order)
		str = lcsString(lcs, x, m, n);
	return str;
}

int main() {
	freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);

	string x; cin >> x;
	string y; cin >> y;
	cout << longestCommonSubsequenceDP(x, y) << "\n";
	return 0;
}