// Warning: replace __int128 with long double if using floating point lines or if unsure about the compiler
// Queries maximum by default, pass false in constructor to query minimum
// Line = pair (m, c) for a line y = mx + c
// Make sure lines are inserted in non-decreasing order for maximum queries, and non-increasing order for minimum queries
template<typename T, class Line = pair<T, T>> // Make sure multiplications fit in T
class CHT {
private:
  vector<Line> lines;
  bool maximum;
public:
  CHT(bool maximum = true) { this->maximum = maximum; }
  void addLine(Line line) {
    if (!maximum) line.first = -line.first, line.second = -line.second;
    insert(line);
  }
  T query(const T &x) {
    assert(!lines.empty());

    int L = 0, R = lines.size() - 1;
    while (L != R) {
      int mid1 = L + (R - L) / 3;
      int mid2 = R - (R - L) / 3;
      if (lines[mid1].x * x + lines[mid1].y
          >= lines[mid2].x * x + lines[mid2].y
          ) R = mid2 - 1;
      else L = mid1 + 1;
    }

    T res = lines[L].x * x + lines[L].y;
    return maximum ? res : -res;
  }
private:
  bool bad(const Line &line1, const Line &line2, const Line &line3) {
    return __int128(line3.y - line1.y) * __int128(line1.x - line2.x)
           <= __int128(line2.y - line1.y) * __int128(line1.x - line3.x);
  }
  void insert(const Line &line) {
    while (lines.size() > 0 && lines.back().x == line.x) lines.pop_back();
    lines.push_back(line);
    int sz = lines.size();
    while (sz >= 3 && bad(lines[sz - 3], lines[sz - 2], lines[sz - 1])) {
      lines.erase(lines.end() - 2);
      sz--;
    }
  }
};