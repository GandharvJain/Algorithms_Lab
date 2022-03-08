#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<double, double> Coords;

vector<Coords> hull;

bool coincide(Coords p1, Coords p2, Coords p) {return (p1 == p2 || p == p1 || p == p2);}
double signedDist(Coords p1, Coords p2, Coords p) {
	if (coincide(p1, p2, p))
		return 0;

	double x1 = p1.first, y1 = p1.second;
	double x2 = p2.first, y2 = p2.second;
	double x = p.first, y = p.second;

	double val1 = (y - y1)*(x2 - x1) - (y2 - y1)*(x - x1);
	double val2 = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

	return val1 / val2;
}
int sign(double x) {
	int sgn = (x == 0) ? 0 : ((x > 0) ? 1 : -1);
	return sgn;
}
bool areCollinear(Coords p1, Coords p2, Coords p, double dist) {
	if (dist != 0 || coincide(p1, p2, p))
		return false;
	return true;
}

void findHull(set<Coords> &points, Coords p1, Coords p2, double side) {
	Coords p_max;
	double max_dist = -1;
	auto max_itr = points.begin();

	for (auto p = points.begin(); p != points.end(); ++p) {
		Coords pnt = *p;
		double dist = signedDist(p1, p2, pnt);

		if (sign(dist) == sign(side) || areCollinear(pnt, p1, p2, dist)) {
			if (abs(dist) > max_dist) {
				max_dist = abs(dist);
				max_itr = p;
				p_max = *p;
			}
		}
	}
	if (max_dist == -1)	return;

	hull.push_back(p_max);

	if (coincide(p_max, p1, p2)) return;

	points.erase(max_itr);
	findHull(points, p1, p_max, -1 * signedDist(p1, p_max, p2));
	findHull(points, p2, p_max, -1 * signedDist(p2, p_max, p1));
}

void quickHull(const vector<Coords> &p) {
	set<Coords> points(p.begin(), p.end());
	Coords p_left(*points.begin()), p_right(*points.begin());

	for (auto p: points) {
		if (p.first < p_left.first)
			p_left = p;
		else if (p.first > p_right.first)
			p_right = p;
	}
	hull.push_back(p_left);
	hull.push_back(p_right);

	findHull(points, p_left, p_right, +1);
	findHull(points, p_left, p_right, -1);
}

void plot_input(int argc, char *argv[], int n) {
	string cmd = "python3 ConvexHull_in.py";
	if (n > 0)
		cmd += " " + to_string(n);
	if (argc > 1) {
		string num = argv[1];
		cmd += " " + num;
	}
	system(cmd.c_str());
}
void plot_output() {
	cout << flush;
	string cmd = "python3 ConvexHull_out.py";
	system(cmd.c_str());
}

int main(int argc, char *argv[]) {
	freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);
	plot_input(argc, argv, 30);

	int n; cin >> n;
	vector<Coords> points(n);
	for (int i = 0; i < n; ++i)
		cin >> points[i].first >> points[i].second;
	
	quickHull(points);

	cout << hull.size() << "\n";
	for (int i = 0; i < hull.size(); ++i)
		cout << hull[i].first << " " << hull[i].second << "\n";

	plot_output();

	return 0;
}