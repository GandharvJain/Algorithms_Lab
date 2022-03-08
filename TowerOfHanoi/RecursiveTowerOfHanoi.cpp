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

void ToH_Move(int discs, char src, char dst, char tmp) {
	if (discs == 0)
		return;

	ToH_Move(discs - 1, src, tmp, dst);
	
	// printf("Moved disk %d from %c to %c\n", discs, src, dst);
	moveDisc(src, dst);
	printTowers();
	
	ToH_Move(discs - 1, tmp, dst, src);

}

int main() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	int discs;
	cin >> discs;	//Number of discs
	cout << "Recursive version:" << "\n";

	initTowers(discs, 'A');
	printTowers();

	ToH_Move(discs, 'A', 'C', 'B');
	return 0;
}