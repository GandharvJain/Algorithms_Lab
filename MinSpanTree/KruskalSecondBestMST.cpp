#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

class DisjointSetForest {
	vector<ll> parent;
	vector<ll> rank;
public:
	DisjointSetForest(ll n) {
		parent.resize(n);
		rank.resize(n);

		for (ll i = 0; i < n; ++i) {
			parent[i] = i;
			rank[i] = 0;
		}
	}

	ll findSet(ll node) {
		if (node != parent[node])
			parent[node] = findSet(parent[node]);
		return parent[node];
	}

	void setUnion(ll x, ll y) {
		ll x_root = findSet(x);
		ll y_root = findSet(y);

		if (rank[x_root] > rank[y_root])
			parent[y_root] = x_root;
		else {
			parent[x_root] = y_root;
			if (rank[x_root] == rank[y_root])
				rank[y_root]++;
		}
	}
};

typedef vector<ll> Edge;

class Graph {
	vector<Edge> edges;	//weight, vertice 1, vertice 2
	ll vertices;
public:
	Graph(ll v) {
		edges.clear();
		vertices = v;
	}

	void addEdge(ll u, ll v, ll w) {edges.push_back({w, u, v});}
	ll numEdges() {return edges.size();}
	vector<Edge> getEdges(){return edges;}
	ll numVertices() {return vertices;}
	ll totalWeight() {
		ll sum = 0;
		for (auto edge : edges) sum += edge[0];
		return sum;
	}
	void printGraph() {
		cout << vertices << " " << numEdges() << "\n";
		for (auto edge : edges)
			cout << edge[1] << " " << edge[2] << " " << edge[0] << "\n";
	}

	Graph kruskalMST(bool, Edge);
	Graph secondBestMST();
};

Graph Graph::kruskalMST(bool sorted = false, Edge excluded_edge = {}) {
	DisjointSetForest forest(vertices);
	Graph mst(vertices);

	if (!sorted)
		sort(edges.begin(), edges.end());

	for (auto edge : edges) {
		if (mst.numEdges() == vertices - 1)
			break;
		if (edge == excluded_edge)
			continue;

		ll w = edge[0], u = edge[1], v = edge[2];

		if (forest.findSet(u) != forest.findSet(v)) {
			mst.addEdge(u, v, w);
			forest.setUnion(u, v);
		}
	}

	if (mst.numEdges() != vertices - 1)
		return Graph(0);

	return mst;
}

Graph Graph::secondBestMST() {
	Graph best_mst = this->kruskalMST();
	Graph second_best_mst(vertices);
	ll min_weight = LLONG_MAX;

	for (auto edge : best_mst.getEdges()) {
		Graph temp_mst = this->kruskalMST(true, edge);

		ll temp_mst_weight = temp_mst.totalWeight();
		if (temp_mst.numVertices() > 0 && temp_mst_weight < min_weight) {
			second_best_mst = temp_mst;
			min_weight = temp_mst_weight;
		}
	}

	return second_best_mst;
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
	string cmd = "python3 MinSpanTree_in.py ";
	cmd += to_string(v) + " -e " + to_string(e);
	system(cmd.c_str());
}
void draw_graphs() {
	cout << flush;
	system("python3 MinSpanTree_out.py");
}

int main() {
	freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);
	generate_random_graph();

	ll n, m; cin >> n >> m;
	Graph in(n);

	for (ll i = 0; i < m; ++i) {
		ll x, y, w; cin >> x >> y >> w;
		in.addEdge(x, y, w);
	}
	
	in.kruskalMST().printGraph();
	freopen("out1.txt", "w", stdout);
	in.secondBestMST().printGraph();

	draw_graphs();
	return 0;
}