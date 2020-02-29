struct CHT { // Finds maximum
private:
	vector<pii> lines;
public:
	CHT() {}
	void addLine(pii line) {
		lines.push_back(line);
	}
	void build() {
		sort(lines.begin(), lines.end());
		vector<pii> _lines = lines;
		lines.clear();
		for (pii line : _lines) insert(line);
	}
	ll query(int x) {
		if (lines.empty()) return LLONG_MIN;

		int L = 0, R = lines.size() - 1;
		while (L != R) {
			int mid1 = L + (R - L) / 3;
			int mid2 = R - (R - L) / 3;
			if (lines[mid1].x * 1LL * x + lines[mid1].y
				>= lines[mid2].x * 1LL * x + lines[mid2].y) R = mid2 - 1;
			else L = mid1 + 1;
		}
		return lines[L].x * 1LL * x + lines[L].y;
	}
private:
	bool bad(pii line1, pii line2, pii line3) {
		return (line3.y - line1.y) * 1LL * (line1.x - line2.x)
			   <= (line2.y - line1.y) * 1LL * (line1.x - line3.x);
	}
	void insert(pii line) {
		while (lines.size() > 0 && lines.back().x == line.x) lines.pop_back();
		lines.push_back(line);
		int sz = lines.size();
		while (sz >= 3 && bad(lines[sz - 3], lines[sz - 2], lines[sz - 1])) {
			lines.erase(lines.end() - 2);
			sz--;
		}
	}
};