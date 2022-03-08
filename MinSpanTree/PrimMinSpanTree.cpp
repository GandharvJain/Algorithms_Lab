#include <bits/stdc++.h>
using namespace std;
#define MAX_VERTICES 1000

typedef long long int ll;
typedef struct Node {
	ll v;
	ll key = LLONG_MAX;
} Node;

class PriorityQueue {
private:
	vector<Node> heap;
	vector<ll> vert_pos;

	ll left(ll i) {return 2 * i + 1;}
	ll right(ll i) {return 2 * i + 2;}
	ll parent(ll i) {return (i - 1) / 2;}
	void exchange(ll a, ll b) {
		swapVertPos(heap[a].v, heap[b].v);
		Node temp = heap[a];
		heap[a] = heap[b];
		heap[b] = temp;
	}

	void minHeapifyDown(ll i) {
		ll l = left(i), r = right(i), smallest = i;
		if (l < size() && heap[l].key < heap[i].key) 		smallest = l;
		if (r < size() && heap[r].key < heap[smallest].key) smallest = r;
		if (smallest != i) {
			exchange(smallest, i);
			minHeapifyDown(smallest);
		}
	}

	void minHeapifyUp(ll i) {
		ll p = parent(i);
		while (i > 0 && heap[p].key > heap[i].key) {
			exchange(p, i);
			i = p;
			p = parent(p);
		}
	}

	void buildMinHeap() {
		for (ll i = parent(size() - 1); i >= 0; --i)
			minHeapifyDown(i);
	}

	void initVertPos(vector<Node> nodes) {
		ll n = size();
		for (auto node : nodes) {
			ll v = node.v;
			if (v >= vert_pos.size())
				vert_pos.resize(v + 1, -1);
			vert_pos[v] = n++;
		}
	}
	void swapVertPos(ll v1, ll v2) {
		ll temp = vert_pos[v1];
		vert_pos[v1] = vert_pos[v2];
		vert_pos[v2] = temp;
	}

public:
	ll size() {return heap.size();}
	bool isEmpty() {return size() == 0;}

	PriorityQueue(vector<Node> in = {}, ll n = MAX_VERTICES) {
		initVertPos(in);
		heap = in;
		if (n > in.size())
			heap.reserve(n);
		else
			heap.resize(n);

		vert_pos.resize(n);
		buildMinHeap();
	}

	void insert(ll v, ll k) {
		Node elem = {v, k};
		initVertPos({elem});
		heap.push_back(elem);
		minHeapifyUp(size() - 1);
	}
	ll getMin() {
		if (size() < 1) {
			cout << "Queue is empty!" << "\n";
			return LLONG_MAX;
		}
		return heap[0].v;
	}
	ll extractMin() {
		if (size() < 1) {
			cout << "Queue is empty!" << "\n";
			return LLONG_MAX;
		}
		Node min_elem = heap[0];
		exchange(0, size() - 1);
		heap.pop_back();
		minHeapifyDown(0);
		return min_elem.v;
	}
	void decreaseKey(ll v, ll new_key) {
		ll i = vert_pos[v];
		if (heap[i].key < new_key) {
			printf("Error! New key is greater than current key\n");
			return;
		}
		heap[i].key = new_key;
		minHeapifyUp(i);
	}
	bool contains(ll v) {return vert_pos[v] < size();}
	ll getKey(ll v) {return heap[vert_pos[v]].key;}
};

class Graph {
	vector<vector<pair<ll, ll>>> adj_list;	//vertice 1, (vertice 2, weight)
	ll vertices;
public:
	Graph(ll v) {
		vertices = v;
		adj_list.resize(v);
	}
	void addEdge(ll u, ll v, ll w) {
		adj_list[u].push_back({v, w});
		adj_list[v].push_back({u, w});
	}
	ll numEdges() {
		ll count = 0;
		for (auto src : adj_list)
			for (auto dest : src)
				count++;
		return count / 2;
	}
	ll numVertices() {return vertices;}
	void printGraph() {
		cout << vertices << " " << numEdges() << "\n";
		for (ll i = 0; i < adj_list.size(); ++i) {
			for (auto dest : adj_list[i]) {
				if (i < dest.first)
					cout << i << " " << dest.first << " " << dest.second << "\n";
			}
		}
	}

	Graph primMST(ll);
};

Graph Graph::primMST(ll root = 0) {
	PriorityQueue Q({}, vertices);
	vector<ll> parent(vertices, -1), weight(vertices, -1);

	Q.insert(root, 0);
	for (ll i = 0; i < vertices; ++i) {
		if (i == root) continue;
		Q.insert(i, LLONG_MAX);
	}

	while (!Q.isEmpty()) {
	    ll src = Q.extractMin();
	    for (auto dest : adj_list[src]) {
	    	ll dst = dest.first, w = dest.second;
	    	if (Q.contains(dst) && w < Q.getKey(dst)) {
	    		parent[dst] = src;
	    		weight[dst] = w;
	    		Q.decreaseKey(dst, w);
	    	}
	    }
	}

	Graph ans(vertices);
	for (ll i = 0; i < vertices; ++i) {
		if (i == root) continue;
		ans.addEdge(i, parent[i], weight[i]);
	}
	return ans;
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

	in.primMST(rand() % n).printGraph();

	draw_graphs();
	return 0;
}