#include <bits/stdc++.h>
using namespace std;

const int Dig = 10;

struct bigint {
	deque<int> num;
	int sign = 1;

	//constructor
	bigint() {
	}
	bigint(long long x) {
		num.clear();
		if (x < 0)
			sign = -1, x = -x;
		if (x == 0)
			num.push_back(x);
		while (x > 0) {
			num.push_back(x % Dig);
			x /= Dig;
		}
	}
	bigint(int x) {
		num.clear();
		if (x < 0)
			sign = -1, x = -x;
		if (x == 0)
			num.push_back(x);
		while (x > 0) {
			num.push_back(x % Dig);
			x /= Dig;
		}
	}
	bigint(const bigint &x) {
		sign = x.sign;
		num = x.num;
	}

	// change to int
	friend int BtoI(const bigint &x) {
		int res = 0, t = 1;
		for (int i = 0; i < x.num.size(); i++)
			res += t * x.num[i];
		return res;
		
	}

	//absolut
	friend bigint abs(const bigint &x) {
		bigint res = x;
		res.sign = 1;
		return res;
	}

	//clear 0
	void clr() {
		while (!num.empty() and !num.back())
			num.pop_back();
	}

	//normalize
	void normalize() {
		(*this).clr();
		int carry = 0;
		for (int i = 0; i < num.size(); i++) {
			int t = num[i] + carry;
			if (t < 0) {
				t += Dig;
				carry = -1;
				num[i] = t;
			}
			else {
				num[i] = t % Dig;
				carry = t / Dig;
			}
		}
		if (carry > 0)
			num.push_back(carry);
		if (carry < 0) {
			sign *= -1;
			num.push_back(-carry);
		}
		(*this).clr();
		if (num.empty())
			sign = 1;
		
	}

	//is 0
	bool isZero() {
		(*this).normalize();
		return num.empty();
	}

	//compare operators
	bool operator<(const bigint &x) const {
		if (sign != x.sign)
			return sign < x.sign;
		bool res = false, flag = false;
		if (num.size() != x.num.size()) {
			res = (num.size() < x.num.size());
			flag = true;
		}
		else {
			for (int i = num.size() - 1; i >= 0; i--)
				if (num[i] != x.num[i]) {
					flag = true;
					res = (num[i] < x.num[i]);
					break;
				}
		}
		if (!flag)
			return false;
		if (sign == -1)
			return !res;
		return res;
	}
	bool operator==(const bigint &x) const {
		if (sign == x.sign and num.size() == x.num.size()) {
			bool res = true;
			for (int i = 0; i < num.size() and res; i++)
				if (num[i] != x.num[i])
					res = false;
			return res;
		}
		else
			return false;
	}
	bool operator<=(const bigint &x) const {
		return (((*this) < x) or ((*this) == x));
	}
	bool operator>(const bigint &x) const {
		return (!((*this) <= x));
	}
	bool operator>=(const bigint &x) const {
		return (!((*this) < x));
	}
	bool operator!=(const bigint &x) const {
		return (!((*this) == x));
	}
	friend bigint max(const bigint &x, const bigint &y) {
		return (x > y? x: y);
	}
	friend bigint min(const bigint &x, const bigint &y) {
		return (x < y? x: y);
	}

	//math operators
	bigint operator+(const bigint &x) const {
		if (sign == x.sign) {
			bigint res;
			res.sign = sign;
			for (int i = 0; i < max(x.num.size(), num.size()); i++) {
				int t = (i >= num.size()? 0: num[i]) + (i >= x.num.size()? 0: x.num[i]);
				res.num.push_back(t);
			}
			res.normalize();
			return res;
		}
		if (sign == -1)
			return x - abs(*this);
		else
			return (*this) - abs(x);
	}
	bigint operator-(const bigint &x) const {
		if (sign == x.sign) {
			bigint res, a = abs(*this), b = abs(x);
			a.clr();
			b.clr();
			if (a == b) {
				res = 0;
				return res;
			}
			if (b < a) {
				for (int i = 0; i < a.num.size(); i++) {
					int t = a.num[i] - (i >= b.num.size()? 0: b.num[i]);
					res.num.push_back(t);
				}
				res.normalize();
			}
			else {
				for (int i = 0; i < b.num.size(); i++) {
					int t = b.num[i] - (i >= a.num.size()? 0: a.num[i]);
					res.num.push_back(t);
				}
				res.normalize();
				res.sign *= -1;
			}
			if (sign == -1)
				res.sign *= -1;
			return res;
		}
		if (sign == -1) {
			bigint res = abs(*this) + x;
			res.sign *= -1;
			return res;
		}
		else
			return (*this) + abs(x);
	}
	void operator+=(const bigint &x) {
		(*this) = (*this) + x;
	}
	void operator-=(const bigint &x) {
		(*this) = (*this) - x;
	}
	void operator++() {
		(*this) += 1;
	}
	bigint operator++(int) {
		bigint res;
		++(*this);
		return res;
	}
	void operator--() {
		(*this) -= 1;
	}
	bigint operator--(int) {
		bigint res;
		--(*this);
		return res;
	}
	bigint operator*(const bigint &x) const {
		bigint res;
		bigint a = (*this), b = x;
		if (a.isZero() or b.isZero())
			return 0;
		a.clr();
		b.clr();
		for (int i = 0; i < b.num.size(); i++) {
			bigint t;
			for (int j = 1; j <= i; j++)
				t.num.push_back(0);
			for (int j = 0; j < a.num.size(); j++)
				t.num.push_back(a.num[j] * b.num[i]);
			t.normalize();
			res += t;
		}
		res.normalize();
		res.sign = a.sign * b.sign;
		return res;
	}
	void operator*=(const bigint &x) {
		(*this) = (*this) * x;
	}
	friend pair<bigint, bigint> dmod(const bigint &x, const bigint &y) {
		bigint res, a = abs(x), b = abs(y), carry;
		res.sign = y.sign * x.sign;
		a.clr();
		b.clr();
		if (b.isZero())
			return {-1, -1};
		if (a < b) {
			return {0, x};
		}
		int cnt = a.num.size() - 1;
		for (int i = a.num.size() - 1; carry < b; i--) {
			carry.num.push_front(a.num[i]);
			cnt = i - 1;
		}
		for (int i = 1; i <= 10; i++) {
			bigint t = b * i;
			if (t > carry) {
				res.num.push_front(i - 1);
				t -= b;
				carry -= t;
				break;
			}
		}
		for (int i = cnt; i >= 0; i--) {
			carry.num.push_front(a.num[i]);
			carry.normalize();
			if (carry >= b) {
				for (int j = 1; j <= 10; j++) {
					bigint t = b * j;
					if (t > carry) {
						res.num.push_front(j - 1);
						t -= b;
						carry -= t;
						break;
					}
				}
			}
			else {
				res.num.push_front(0);
			}
		}
		res.normalize();
		if (res.sign == -1)
			carry = y - x;
		return {res, carry};

	}
	bigint operator/(const bigint &x) const {
		pair<bigint, bigint> res = dmod((*this), x);
		return res.first;
	}
	void operator/=(const bigint &x) {
		(*this) = (*this) / x;
	}
	bigint operator%(const bigint &x) const {
		pair<bigint, bigint> res = dmod((*this), x);
		return res.second;
	}
	void operator%=(const bigint &x) {
		(*this) = (*this) % x;
	}
	friend bigint pow(const bigint &x, const bigint &y) {
		bigint tmp = y;
		if (tmp.isZero())
			return 1;
		bigint res = 1, t = y, a = x;
	       	pair<bigint, bigint> dm;
		while (t > 0) {
			if ((t % 2) == 1)
				res = res * a;
			a *= a;
			t /= 2;
		}
		return res;
	}
	friend bigint gcd(bigint x, bigint y) {
		return (y.isZero()? x: gcd(y, x % y));
	}
	friend bigint lcm(const bigint &x, const bigint &y) {
		return (x * y) / gcd(x, y);
	}
	friend bigint sqrt(const bigint &x) {
		if (x.sign == -1)
			return -1;
		bigint carry, res, lef;
		deque<pair<int, int>> t;
		for (int i = 0; i < x.num.size(); i += 2) {
			if (i + 1 == x.num.size())
				t.push_front({x.num[i], 1});
			else
				t.push_front({x.num[i] + x.num[i + 1] * 10, 2});
		}
		for (int i = 0; i < t.size(); i++) {
			if (t[i].second == 1)
				carry.num.push_front(t[i].first);
			else
				carry.num.push_front(t[i].first / 10), carry.num.push_front(t[i].first % 10);
			carry.normalize();
			lef.num.push_front(0);
			for (int i = 1; i <= 10; i++) {
				lef.num[0] = i;
				bigint tmp = (lef) * i;
				if (tmp > carry) {
					lef.num[0] = i - 1;
					tmp = lef * (i - 1);
					carry -= tmp;
					lef += (i - 1);
					res.num.push_front(i - 1);
					break;
				}
			}
		}
		res.normalize();
		return res;
	}

	//string to bigint and bigint to string
	void toBig(string &s) {
		if (s[0] == '-') {
			sign = -1;
			s = s.substr(1);
		}
		else
			sign = 1;
		reverse(s.begin(), s.end());
		num.clear();
		for (int i = (s[0] == '-'); i < s.size(); i += Dig / 10) {
			string sp;
			for (int j = i; j < i + (Dig / 10); j++)
				sp += s[j];
			long long t = stol(sp);
			num.push_back(t);
		}
	}
	friend string to_string(const bigint &x) {
		string res;
		if (x.num.empty()) {
			res += '0';
			return res;
		}
		if (x.sign == -1)
			res += '-';
		for (int i = x.num.size() - 1; i >= 0; i--) {
			string t = to_string(x.num[i]);
			reverse(t.begin(), t.end());
			res += t;
		}
		return res;
	}
	//change base
	friend bigint change_base(const bigint &a, const int y, const int x) {
		if (y == x)
			return a;
		bigint res, t = change_base_rev(a, y, 10);
		t.normalize();
		while (t > 0) {
			res.num.push_back(BtoI(t % x));
			t /= x;
		}
		return res;
	}
	friend bigint change_base_rev(const bigint &a, const int y, const int x) {
		if (y == x)
			return a;
		if (x == 10) {
			bigint res, t = 1, b = a;
			b.clr();
			for (int i = 0; i < b.num.size(); i++)
				res += t * b.num[i], t *= y;
			return res;
		}
		bigint t = change_base_rev(a, y, 10);
		return change_base(t, 10, x);

	}
	friend bigint CB(const bigint &a, int y, int x) {
		if (x > y)
			return change_base_rev(a, y, x);
		return change_base(a, y, x);
	}

	//bitwise operator
	bigint operator^(const bigint &x) const {
		bigint res, a = change_base(*this, 10, 2), b = change_base(x, 10, 2);
		for (int i = 0; i < max(a.num.size(), b.num.size()); i++) {
			int d1 = 0, d2 = 0;
			if (i < a.num.size())
				d1 = a.num[i];
			if (i < b.num.size())
				d2 = b.num[i];
			res.num.push_back(d1 ^ d2);
		}
		res.clr();
		res = change_base_rev(res, 2, 10);
		res.normalize();
		return res;
	}
	bigint operator&(const bigint &x) const {
		bigint res, a = change_base(*this, 10, 2), b = change_base(x, 10, 2);
		for (int i = 0; i < max(a.num.size(), b.num.size()); i++) {
			int d1 = 0, d2 = 0;
			if (i < a.num.size())
				d1 = a.num[i];
			if (i < b.num.size())
				d2 = b.num[i];
			res.num.push_back(d1 & d2);
		}
		res.clr();
		res = change_base_rev(res, 2, 10);
		res.normalize();
		return res;
	}
	bigint operator|(const bigint &x) const {
		bigint res, a = change_base(*this, 10, 2), b = change_base(x, 10, 2);
		for (int i = 0; i < max(a.num.size(), b.num.size()); i++) {
			int d1 = 0, d2 = 0;
			if (i < a.num.size())
				d1 = a.num[i];
			if (i < b.num.size())
				d2 = b.num[i];
			res.num.push_back(d1 | d2);
		}
		res.clr();
		res = change_base_rev(res, 2, 10);
		res.normalize();
		return res;
	}
	void operator^=(const bigint &x) {
		(*this) = (*this) ^ x;
	}
	void operator&=(const bigint &x) {
		(*this) = (*this) & x;
	}
	void operator|=(const bigint &x) {
		(*this) = (*this) | x;
	}
	bigint operator<<(const bigint &x) {
		bigint res = change_base((*this), 10, 2);
		for (bigint i = 0; i < x; i++)
			res.num.push_front(0);
		res = change_base_rev(res, 2, 10);
		res.normalize();
		return res;
	}
	bigint operator>>(const bigint &x) {
		bigint res = change_base((*this), 10, 2);
		bigint t = (int)res.num.size();
		for (bigint i = 0; i < min(x, t); i++)
			res.num.pop_front();
		res = change_base_rev(res, 2, 10);
		res.normalize();
		return res;

	}
	void operator>>=(const bigint &x) {
		(*this) = (*this) >> x;
	}
	void operator<<=(const bigint &x) {
		(*this) = (*this) << x;
	}

	//builtin fuctions
	int popcount() {
		int res = 0;
		bigint tmp = *this;
		tmp = CB(tmp, 10, 2);
		for (auto i : tmp.num)
			res += i;
		return res;
	}
	int clz() {
		bigint tmp = *this;
		tmp = CB(tmp, 10, 2);
		for (int i = 0; i < tmp.num.size(); i++)
			if (tmp.num[i])
				return i;
	}

	//cin and cout
	friend istream& operator>>(istream &stream, bigint &x) {
		string s;
		stream >> s;
		x.toBig(s);
		x.normalize();
		return stream;
	}
	friend ostream& operator<<(ostream &stream, bigint &x) {
		if (x.num.empty()) {
			stream << 0;
			return stream;
		}
		if (!x.num.empty() and x.sign == -1)
			stream << '-';
		stream << (x.num.empty() ? 0 : x.num.back());
		for (int i = (int) x.num.size() - 2; i >= 0; i--)
			stream  << x.num[i];
		return stream;
	}
	
};

//tutorial :
//everything is similar to using int exept a few functions
//BtoI(bigint x) : returns x to int (becareful with overflow)
//CB(bigint x, int a, int b) : get a bigint in base a and returns a bigint in base b (a, b <= 10)
//x.popcount() : returns number of 1 in binary form of x
//x.clz() : returns number of 0 before the rightmost 1 in binary form of x