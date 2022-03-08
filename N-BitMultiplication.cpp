#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
#define BIT_LEN 16

class bitForm {
private:
	string bitString;
	string getLeft() {return bitString.substr(0, this->len() / 2);}
	string getRight() {return bitString.substr(this->len() / 2);}
public:
	bitForm(string s = "", int n = BIT_LEN) {	//Constructors
		bitString = lenNorm(s, n);
	}
	bitForm(ull num, int n = BIT_LEN) {
		string s = bitset<BIT_LEN> (num).to_string();
		bitString = lenNorm(s, n);
	}

	string lenNorm(string s, int n) {			//Zero-Padder
		int l = s.size();
		if (l < n) {
			string temp(n - l, '0');
			s = temp + s;
		}
		else if (l > n) {			
			return s.substr(l - n);
		}
		return s;
	}
	int len() {return bitString.size();}
	string getBitString() {return bitString;}
	ull getDecimal() {return strtoull(bitString.c_str(), NULL, 2);}

	bitForm operator+(const bitForm& t) {		//Overloading "+" operator
		string a = this->getBitString(), b = t.bitString;
		int l = max(a.size(), b.size());
		a = lenNorm(a, l);
		b = lenNorm(b, l);

		string temp = "";
		int c = 0;

		for (ll i = l - 1; i >= 0; --i) {
			int x = a[i] - '0', y = b[i] - '0';
			int s = x ^ y ^ c;
			c = x & y | y & c | c & x;
			temp.push_back(s + '0');
		}
		if (c) {temp.push_back('1');}

		reverse(temp.begin(), temp.end());
		bitForm sum(temp, temp.size());
		return sum;
	}
	bitForm operator<<(int n) {					//Overloading "<<" operator
		string shifted(n, '0');
		shifted = bitString + shifted;
		shifted = shifted.substr(max(0, (int)shifted.size() - BIT_LEN));
		return bitForm(shifted, shifted.size());
	}
	bitForm operator*(bitForm& t2){				//Overloading "*" operator
		bitForm t1 = *this;
		int n = max(t1.len(), t2.len());
		bitForm a(t1.bitString, n), b(t2.bitString, n);

		if (n == 1) {
			int x = (char)a.bitString.back() - '0';
			int y = (char)b.bitString.back() - '0';
			return bitForm(x & y, 1);
		}
		bitForm a_l(a.getLeft(), n / 2), a_r(a.getRight(), n / 2);
		bitForm b_l(b.getLeft(), n / 2), b_r(b.getRight(), n / 2);

		bitForm p_ll = a_l * b_l;
		bitForm p_lr = a_l * b_r;
		bitForm p_rl = a_r * b_l;
		bitForm p_rr = a_r * b_r;

		bitForm ans = (p_ll << n) + ((p_lr + p_rl) << (n / 2)) + p_rr;
		return ans;
	}
};

int main() {
	freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);

	bitForm a(9), b(13);
	cout << a.getDecimal() << " " << a.getBitString() << "\n";
	cout << b.getDecimal() << " " << b.getBitString() << "\n";
	bitForm c = a * b;
	cout << c.getDecimal() << " " << c.getBitString() << "\n";
	
	
	return 0;
}