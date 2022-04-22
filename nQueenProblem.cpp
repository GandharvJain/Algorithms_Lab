#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef vector<ll> vl;
#define PRINT_ALL true

ll num_solutions = 0;
void printBoard(vl Q, ll n) {
	for (ll r = 0; r < n; ++r) {
			ll col = Q[r];
			for (ll c = 0; c < n; ++c)
				cout << (c == col) << " ";
			cout << "\n";
	}
	cout << "\n";
}

bool isLegal(const vl &Q, ll row, ll col) {
	for (ll r = 0; r < row; ++r)
		if (Q[r] == col || abs(r - row) == abs(Q[r] - col))
			return false;
	return true;
}

bool recursiveQueenPlacer(vl &Q, ll row) {
	ll n = Q.size();
	if (row >= n) {
		if (PRINT_ALL) {
			printBoard(Q, n);
			num_solutions++;
		}
		return true;
	}

	for (ll col = 0; col < n; ++col) {
		if (isLegal(Q, row, col)) {
			Q[row] = col;

			if (recursiveQueenPlacer(Q, row + 1) && !PRINT_ALL)
					return true;

			Q[row] = -1;
		}
	}
	return false;
}

void initQueenPlacer(ll n, bool print_board = true) {
	vl Q(n, -1);
	recursiveQueenPlacer(Q, 0);
	if (!PRINT_ALL)
		printBoard(Q, n);
	else
		cout << "Number of solutions: " << num_solutions << "\n";
}

int main() {
	freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);

	ll n; cin >> n;
	initQueenPlacer(n);

	return 0;
}