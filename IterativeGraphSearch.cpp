#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#define IS_DIRECTED false

class Graph {
	ll vertices;
	vector<vector<ll>> adj_list;
public:
	Graph(ll V) {
		vertices = V;
		adj_list.resize(V);
	}
	void addEdge(ll u, ll v) {
		adj_list[u].push_back(v);
		if (!IS_DIRECTED)
			adj_list[v].push_back(u);
	}
	void iterativeDFS(ll);
	void iterativeBFS(ll);
};

void Graph::iterativeDFS(ll root = 0) {
	cout << "DFS: ";
	vector<bool> visited(vertices, false);
	stack<ll> s;
	s.push(root);

	while (!s.empty()) {
		ll u = s.top();
		s.pop();

		if (visited[u]) continue;

		visited[u] = true;
		cout << u << " ";

		for (auto v : adj_list[u])
			if (!visited[v])
				s.push(v);
	}
	cout << "\n";
}

void Graph::iterativeBFS(ll root = 0) {
	cout << "BFS: ";
	vector<bool> visited(vertices, false);
	queue<ll> q;

	q.push(root);
	visited[root] = true;

	while (!q.empty()) {
		ll u = q.front();
		q.pop();

		cout << u << " ";

		for (auto v : adj_list[u])
			if (!visited[v]) {
				visited[v] = true;
				q.push(v);
			}
	}
	cout << "\n";
}

void generate_random_graph(ll v = -1, ll e = -1) {
	srand(time(0));
	if (v <= 0)
		v = rand() % 3 + 5;
	ll max = v*(v - 1)/2, min = v - 1;
	if (e < min || e > max) {
		ll range = max - min + 1;
		e = rand() % range + min;
	}
	string cmd = "python3 MinSpanTree/MinSpanTree_in.py ";
	cmd += to_string(v) + " -e " + to_string(e);
	system(cmd.c_str());
}
void draw_graphs() {
	cout << flush;
	system("python3 MinSpanTree/MinSpanTree_out.py 0");
}

int main() {
	freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);
	generate_random_graph(7, 7);

	ll n, m; cin >> n >> m;
	Graph in(n);

	for (ll i = 0; i < m; ++i) {
		ll x, y, w; cin >> x >> y >> w;
		in.addEdge(x, y);
	}

	ll root = rand() % n;
	in.iterativeDFS(root);
	in.iterativeBFS(root);

	draw_graphs();	
	return 0;
}