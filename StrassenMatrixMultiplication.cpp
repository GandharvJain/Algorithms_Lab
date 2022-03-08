#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef vector<vector<ll>> vvl;

class strassMatrix {
	vvl matrix;
	ll width() const{return (this->matrix)[0].size();}
	ll height() const{return (this->matrix).size();}
public:
	strassMatrix(const vvl& m, ll x0, ll y0, ll x1, ll y1) {
		ll w = y1 - y0, h = x1 - x0;	//x1, y1 should be 1 out of range
		matrix.resize(h, vector<ll>(w));

		for (ll i = 0; i < h; ++i) {
			for (ll j = 0; j < w; ++j) {
				matrix[i][j] = m[x0 + i][y0 + j];
			}
		}
	}
	strassMatrix(const vvl& m11, const vvl& m12, const vvl& m21, const vvl& m22) {
		ll h11 = m11.size(), h12 = m12.size(), h21 = m21.size(), h22 = m22.size();
		ll w11 = m11[0].size(), w12 = m12[0].size(), w21 = m21[0].size(), w22 = m22[0].size();

		if (h11 + h21 != h12 + h22 || w11 + w12 != w21 + w22 || 
			h11 != h12 || h21 != h22 || w11 != w21 || w12 != w22) {
			cout << "Error! Invalid matrix size" << endl;
			exit(1);
		}

		for (ll i = 0; i < h11; ++i) {
			matrix.push_back(m11[i]);
			matrix[i].insert(matrix[i].end(), m12[i].begin(), m12[i].end());
		}
		for (ll i = 0; i < h21; ++i) {
			matrix.push_back(m21[i]);
			matrix[i + h11].insert(matrix[i + h11].end(), m22[i].begin(), m22[i].end());
		}
	}

	strassMatrix operator+(const strassMatrix& b) {
		if (this->height() != b.height() || this->width() != b.width()) {
			cout << "Error! Invalid matrix addition" << "\n";
		}
		strassMatrix sum(this->matrix, 0, 0, this->height(), this->width());

		for (ll i = 0; i < b.height(); ++i) {
			for (ll j = 0; j < b.width(); ++j) {
				sum.matrix[i][j] += b.matrix[i][j];
			}
		}
		return sum;
	}
	strassMatrix operator-(const strassMatrix& b) {
		if (this->height() != b.height() || this->width() != b.width()) {
			cout << "Error! Invalid matrix subtraction" << "\n";
		}
		strassMatrix diff(this->matrix, 0, 0, this->height(), this->width());

		for (ll i = 0; i < b.height(); ++i) {
			for (ll j = 0; j < b.width(); ++j) {
				diff.matrix[i][j] -= b.matrix[i][j];
			}
		}
		return diff;
	}
	strassMatrix operator*(const strassMatrix& b) {
		strassMatrix a = *this;
		ll a_h = a.height(), a_w = a.width(), b_h = b.height(), b_w = b.width();
		if (a_w != b_h) {
			cout << "Error! Invalid matrix multiplication" << "\n";
		}
		if (a_h == 1) {
			vvl one(1, vector<ll>(1, a.matrix[0][0] * b.matrix[0][0]));
			strassMatrix ans(one, 0, 0, 1, 1);
			return ans;
		}

		strassMatrix a11(a.matrix, 0	, 0		, a_h/2	, a_w/2	);
		strassMatrix a12(a.matrix, 0	, a_w/2	, a_h/2	, a_w	);
		strassMatrix a21(a.matrix, a_h/2, 0		, a_h	, a_w/2	);
		strassMatrix a22(a.matrix, a_h/2, a_w/2	, a_h	, a_w	);

		strassMatrix b11(b.matrix, 0	, 0		, b_h/2	, b_w/2	);
		strassMatrix b12(b.matrix, 0	, b_w/2	, b_h/2	, b_w	);
		strassMatrix b21(b.matrix, b_h/2, 0		, b_h	, b_w/2	);
		strassMatrix b22(b.matrix, b_h/2, b_w/2	, b_h	, b_w	);

		strassMatrix m1 = (a11 + a22) * (b11 + b22);
		strassMatrix m2 = (a21 + a22) * b11;
		strassMatrix m3 = a11 * (b12 - b22);
		strassMatrix m4 = a22 * (b21 - b11);
		strassMatrix m5 = (a11 + a12) * b22;
		strassMatrix m6 = (a21 - a11) * (b11 + b12);
		strassMatrix m7 = (a12 - a22) * (b21 + b22);


		strassMatrix c11 = m1 + m4 - m5 + m7;
		strassMatrix c12 = m3 + m5;
		strassMatrix c21 = m2 + m4;
		strassMatrix c22 = m1 - m2 + m3 + m6;

		strassMatrix ans(c11.matrix, c12.matrix, c21.matrix, c22.matrix);
		return ans;
	}

	void printMatrix() {
		for (ll i = 0; i < height(); ++i) {
			for (ll j = 0; j < width(); ++j) {
				cout << setw(4) << matrix[i][j] << " ";
			}
			cout << "\n";
		}
	}
};

int main() {
	freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);
	int n = 4;
	vvl a_v{
		{	1,	2,	3,	4},
		{	5,	6,	7,	8},
		{	9,	10,	11,	12},
		{	13,	14,	15,	16}
	}, 
	b_v{
		{	1,	0,	0,	0},
		{	0,	1,	0,	0},
		{	0,	0,	1,	0},
		{	0,	0,	0,	1}
	}, 
	c_v(n, vector<ll>(n, 0));
	
	strassMatrix a(a_v, 0, 0, n, n), b(b_v, 0, 0, n, n);
	strassMatrix c = a * b;
	c.printMatrix();

	// for (ll i = 0; i < n; ++i) {
	// 	for (ll j = 0; j < n; ++j) {
	// 		for (ll k = 0; k < n; ++k) {
	// 			c_v[i][j] += a_v[i][k] * b_v[k][j]; 
	// 		}
	// 	}
	// }
	// for (ll i = 0; i < n; ++i) {
	// 	for (ll j = 0; j < n; ++j) {
	// 		cout << setw(4) << c_v[i][j] << " ";
	// 	}
	// 	cout << "\n";
	// }

	return 0;
}