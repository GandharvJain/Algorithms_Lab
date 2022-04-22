#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef vector<ll> vl;
typedef vector<vl> vvl;

#define BLANK 0

class GameState {
public:
	vvl board;
	ll n;
	ll misplaced;
	ll level;
	ll blank_row, blank_col;
	GameState *parent;

	GameState(const vvl &b, ll old_r, ll old_c, ll new_r, ll new_c, ll lvl, GameState *p, const vvl &goal) {
		n = b.size();
		board = b;
		blank_row = new_r, blank_col = new_c;
		level = lvl;
		parent = p;
		swap(board[old_r][old_c], board[new_r][new_c]);
		countMisplaced(goal);
	}

	void countMisplaced(const vvl &goal) {
		misplaced = 0;
		for (ll i = 0; i < n; ++i)
			for (ll j = 0; j < n; ++j)
				if (board[i][j] != goal[i][j])
					misplaced++;
	}
	void printBoard() {
		for (auto row : board) {
			for (auto tile : row)
				cout << setw(floor(log10(n*n - 1) + 1)) << tile << " ";
			cout << "\n";
		}
		cout << "\n";
	}
	ll getCost() {return misplaced + level;}
	bool isWithinBounds(ll row, ll col) {return row >= 0 && row < n && col >= 0 && col < n;}
	void printMoveSequence() {
		if (parent != NULL)
			parent->printMoveSequence();
		printBoard();
	}
};

class PriorityQueue {
private:
	vector<GameState*> heap;

	ll left(ll i) {return 2 * i + 1;}
	ll right(ll i) {return 2 * i + 2;}
	ll parent(ll i) {return (i - 1) / 2;}
	void exchange(ll a, ll b) {
		GameState* temp = heap[a];
		heap[a] = heap[b];
		heap[b] = temp;
	}

	void minHeapifyDown(ll i) {
		ll l = left(i), r = right(i), smallest = i;
		if (l < size() && heap[l]->getCost() < heap[i]->getCost()) smallest = l;
		if (r < size() && heap[r]->getCost() < heap[smallest]->getCost()) smallest = r;
		if (smallest != i) {
			exchange(smallest, i);
			minHeapifyDown(smallest);
		}
	}

	void minHeapifyUp(ll i) {
		ll p = parent(i);
		while (i > 0 && heap[p]->getCost() > heap[i]->getCost()) {
			exchange(p, i);
			i = p;
			p = parent(p);
		}
	}
public:
	PriorityQueue(ll n = 0) {heap.reserve(n);}

	ll size() {return heap.size();}
	bool isEmpty() {return heap.size() == 0;}
	GameState* getMin() {return heap[0];}

	void insert(GameState *state) {
		heap.push_back(state);
		minHeapifyUp(size() - 1);
	}
	GameState* extractMin() {
		GameState *min_elem = heap[0];
		exchange(0, size() - 1);
		heap.pop_back();
		minHeapifyDown(0);
		return min_elem;
	}
};

void solvePuzzle(const vvl &initial, const vvl &goal) {
	ll n = initial.size();
	ll r = n - 1, c = n - 1;
	int row[] = {0, +1, 0, -1};
	int col[] = {+1, 0, -1, 0};

	for (ll i = 0; i < n; ++i)				//Find blank tile
		for (ll j = 0; j < n; ++j)
			if (initial[i][j] == BLANK)
				r = i, c = j;

	PriorityQueue live_nodes;
	GameState *root = new GameState(initial, r, c, r, c, 0, NULL, goal);
	live_nodes.insert(root);

	while (!live_nodes.isEmpty()) {
		GameState *e_node = live_nodes.extractMin();

		if (e_node->misplaced == 0) {
			e_node->printMoveSequence();
			break;
		}

		ll oldR = e_node->blank_row, oldC = e_node->blank_col;
		ll new_lvl = e_node->level + 1;
		for (ll i = 0; i < 4; ++i) {
			ll newR = oldR + row[i], newC = oldC + col[i];
			if (e_node->isWithinBounds(newR, newC)) {
				GameState *child_node = new GameState(e_node->board, oldR, oldC, newR, newC, new_lvl, e_node, goal);
				live_nodes.insert(child_node);
			}
		}
	}
}

int main() {
	freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);
	vvl init = {
		{0, 2, 3, 4},
		{1, 6, 7, 8},
		{5, 10, 11, 12},
		{9, 13, 14, 15}
	};
	vvl goal = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 0}
	};

	solvePuzzle(init, goal);
	
	return 0;
}