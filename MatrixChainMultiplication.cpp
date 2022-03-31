#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef vector<vector<ll>> vvl;
#define MAX_SIZE 10
#define MIN_SIZE 1

void printChainOrder(const vvl &split, int i, int j) {
	if (i == j)
		cout << "A_" << i;
	else {
		cout << "(";
		int k = split[i][j];
		printChainOrder(split, i, k);
		cout << " * ";
		printChainOrder(split, k + 1, j);
		cout << ")";
	}
}

ll matrixChainOrderDP(const vector<ll> &p, bool print_order) {
	int n = p.size() - 1;
	vvl cost(n, vector<ll>(n)), split(n, vector<ll>(n));

	for (int i = 0; i < n; ++i)
		cost[i][i] = 0;

	for (int l = 2; l < n + 1; ++l) {
		for (int i = 0; i < n - l + 1; ++i) {
			int j = i + l - 1;
			cost[i][j] = INT_MAX;
			for (int k = i; k < j; ++k) {
				ll q = cost[i][k] + cost[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
				if (q < cost[i][j]) {
					cost[i][j] = q;
					split[i][j] = k;
				}
			}
		}
	}

	if (print_order) {
		printChainOrder(split, 0, n - 1);
		cout << "\n";
	}
	return cost[0][n - 1];
}

ll matrixChainOrderDnC(const vector<ll> &p, vvl &split, int i, int j) {
	if (i == j)
		return 0;

	int min_cost = INT_MAX;

	for (int k = i; k < j; ++k) {
		int cost_a = matrixChainOrderDnC(p, split, i, k);
		int cost_b = matrixChainOrderDnC(p, split, k + 1, j);
		ll q = cost_a + cost_b + p[i] * p[k + 1] * p[j + 1];

		if (q < min_cost) {
			min_cost = q;
			split[i][j] = k;
		}
	}
	return min_cost;
}

ll MatrixChainOrderDnC_Init(const vector<ll> &p, bool print_order) {
	int n = p.size() - 1;
	vvl split(n, vector<ll>(n));
	ll min_cost = matrixChainOrderDnC(p, split, 0, n - 1);

	if (print_order) {
		printChainOrder(split, 0, n - 1);
		cout << "\n";
	}
	return min_cost;
}

vector<ll> generate_random_chain(int n) {
	srand(time(0));
	vector<ll> p(n + 1);
	for (int i = 0; i < n + 1; ++i)
		p[i] = rand() % (MAX_SIZE - MIN_SIZE + 1) + MIN_SIZE;
	return p;
}

int main() {
	freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);

	vector<ll> p = generate_random_chain(3);
	// p = {2, 3, 4, 5, 6};
	for (auto i : p)
		cout << i << " ";
	cout << "\n";

	ll min_cost_dp = matrixChainOrderDP(p, true);
	cout << "DP Minimum cost: " << min_cost_dp << "\n";

	ll min_cost_dnc = MatrixChainOrderDnC_Init(p, true);
	cout << "DnC Minimum cost: " << min_cost_dnc << "\n";

	return 0;
}