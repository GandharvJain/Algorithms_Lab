#include <bits/stdc++.h>
using namespace std;

int partition(vector<int> &A, int p, int r) {
	int i = p;
	for (int j = p; j < r; ++j)
		if (A[j] <= A[r])			// last element is pivot
			swap(A[i++], A[j]);
	swap(A[i], A[r]);
	return i;
}

void quicksort(vector<int> &A, int n) {
	stack<int> s;
	s.push(0);
	s.push(n - 1);

	while (!s.empty()) {
		int r = s.top(); s.pop();
		int l = s.top(); s.pop();
		if (l > r)
			continue;

		int q = partition(A, l, r);
		s.push(l);
		s.push(q - 1);

		s.push(q + 1);
		s.push(r);
	}
}

int main() { 
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	
	int n;
	cin >> n;						//Take array size
	vector<int> array(n);

	for (int i = 0; i < n; ++i)
		cin >> array[i];			//Take array elements
	
	quicksort(array, n);
	
	for (int i = 0; i < n; ++i)
		cout << array[i] << " ";

	return 0;
}