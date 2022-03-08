#include <bits/stdc++.h>
using namespace std;

void merge(vector<int> &A, int p, int q, int r) {

	vector<int> left(A.begin() + p, A.begin() + q + 1);
	vector<int> right(A.begin() + q + 1, A.begin() + r + 1);

	left.push_back(INT_MAX);
	right.push_back(INT_MAX);

	for (int i = 0, j = 0, k = p; k <= r; ++k)
		A[k] = (left[i] <= right[j]) ? left[i++] : right[j++];	// "<=" ensures stable sort
}

void mergesort(vector<int> &v, int n) {
	for (int l = 1; l < n; l *= 2) {	//l represents size of the arrays to be merged
		for (int p = 0; p < n; p += 2*l) {

			int r = min(p + 2*l - 1, n - 1);
			int q = min(p + l - 1, n - 1);
			merge(v, p, q, r);
		}
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
	
	mergesort(array, n);
	
	for (int i = 0; i < n; ++i)
		cout << array[i] << " ";

	return 0;
}