#include <bits/stdc++.h>
using namespace std;

vector<int> s[3];
// Insert n discs into first tower
void initTowers(int n, char start) {
	s[0].clear(); s[1].clear();	s[2].clear();
	int i = start - 'A';
	while (n)
		s[i].push_back(n--);
}
// Move discs between towers
void moveDisc(char from, char to) {
	int i = from - 'A';
	int f = to - 'A';
	s[f].push_back(s[i].back());
	s[i].pop_back();
}
// For printing state of towers:
void printTowers() {
	cout << "|";
	for (int i = 0; i < 3; ++i) {
		char rod = 'A' + i;
		string output;
		output += rod;
		output += ": ";
		for (auto itr = s[i].begin(); itr != s[i].end(); ++itr)
			output += to_string(*itr) + " ";
		int n = s[0].size() + s[1].size() + s[2].size();
		int width = 0;
		for (int i = 0; i <= n; i += 10)
			width += n - i + 1;
		cout << setw(width + n + 2) << left << output << right << "|";
	}
	cout << "\n";
}

// Method 1
int rightmostBit(int x) {
	int ans = 1;
	while ((x & 1) == 0) {
		ans++;
		x /= 2; 
	}
	return ans;
}

void iterative_ToH_2(int n, char source, char dest, char temp) {
	initTowers(n, source);
	printTowers();

	char a[] = {source, temp, dest};
	if (n % 2 == 0)
		swap(a[1], a[2]);

	//Stores current position of disc
	vector<int> discPos(n+1, 0);

	for (int i = 1; i < pow(2, n); ++i) {

		int disc = rightmostBit(i);
		int from = discPos[disc];
		int to = (from + (disc % 2 ? -1 : 1) + 3) % 3;	//Calculate next position of disc
		discPos[disc] = to;

		// printf("Moved disk %d from %c to %c\n", disc, a[from], a[to]);
		moveDisc(a[from], a[to]);
		printTowers();
	}
}

// Method 2
struct args {
	int discs;
	char src, dst, tmp;
};
void iterative_ToH_1(int discs, char source, char dest, char temp) {
	initTowers(discs, source);
	printTowers();

	stack<struct args> s;
	struct args curr = {discs, source, dest, temp};

	while (!s.empty() || curr.discs > 0) {
		while (curr.discs > 0) {
			s.push(curr);
			curr = {curr.discs - 1, curr.src, curr.tmp, curr.dst};
		}

		curr = s.top(); s.pop();

		// printf("Moved disk %d from %c to %c\n", curr.discs, curr.src, curr.dst);
		moveDisc(curr.src, curr.dst);
		printTowers();

		curr = {curr.discs - 1, curr.tmp, curr.dst, curr.src};
	}
}

int main() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	int discs;
	cin >> discs;	//Number of discs
	cout << "Non-recursive version:" << "\n";

	// iterative_ToH_1(discs, 'A', 'C', 'B');
	iterative_ToH_2(discs, 'A', 'C', 'B');
	return 0;
}