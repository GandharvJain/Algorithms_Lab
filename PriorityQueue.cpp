#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

class PriorityQueue {
private:
	vector<ll> heap;

	ll left(ll i) {return 2 * i + 1;}
	ll right(ll i) {return 2 * i + 2;}
	ll parent(ll i) {return (i - 1) / 2;}
	void exchange(ll a, ll b) {
		ll temp = heap[a];
		heap[a] = heap[b];
		heap[b] = temp;
	}

	void maxHeapifyDown(ll i) {
		ll l = left(i), r = right(i), largest = i;
		if (l < size() && heap[l] > heap[i]) 		largest = l;
		if (r < size() && heap[r] > heap[largest]) 	largest = r;
		if (largest != i) {
			exchange(largest, i);
			maxHeapifyDown(largest);
		}
	}

	void maxHeapifyUp(ll i) {
		ll p = parent(i);
		if (i > 0 && heap[p] < heap[i]) {
			exchange(p, i);
			maxHeapifyUp(p);
		}
	}

	void buildMaxHeap() {
		for (ll i = parent(size() - 1); i >= 0; --i)
			maxHeapifyDown(i);
	}

public:
	ll size() {return heap.size();}

	PriorityQueue(vector<ll> in = {}, ll n = -1) {
		heap = in;
		if (n != -1)
			heap.resize(n);
		buildMaxHeap();
	}
	
	void insert(ll elem) {
		heap.push_back(elem);
		maxHeapifyUp(size() - 1);
	}

	ll getMax() {
		if (size() < 1) {
			cout << "Queue is empty!" << "\n";
			return LLONG_MIN;
		}
		return heap[0];
	}

	ll extractMax() {
		if (size() < 1) {
			cout << "Queue is empty!" << "\n";
			return LLONG_MIN;
		}
		ll max_elem = heap[0];
		heap[0] = heap.back();
		heap.pop_back();
		maxHeapifyDown(0);
		return max_elem;
	}
};

int main() {
	PriorityQueue arr;
	bool running = true;

	while (running) {
	    cout << "\tOptions:-\n\t1: Insert\n\t2: Get maximum\n\t3: Remove Maximum\n\t4: Exit\n\t";
	    ll n; cin >> n;
	    cin.clear();
	    cin.ignore(INT_MAX, '\n');

	    switch (n) {
	    	case 1: {
	    		cout << "Enter value to insert\n";
	    		string line;
	    		getline(cin, line);
	    		istringstream inStr(line);
	    		ll val;
	    		while (inStr >> val)
		    		arr.insert(val);
	    		break;
	    	}
	    	case 2: {
	    		ll max_elem = arr.getMax();
	    		if (max_elem == LLONG_MIN)
	    			break;
	    		cout << max_elem << "\n";
	    		break;
	    	}
	    	case 3: {
	    		ll max_elem = arr.extractMax();
	    		if (max_elem == LLONG_MIN)
	    			break;
	    		cout << max_elem << "\n";
	    		break;
	    	}
	    	default: {
	    		if (n != 4)
	    			cout << "Invalid option" << "\n";
	    		else
		    		running = false;
		    }
	    }
	}
	return 0;
}