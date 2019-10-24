// C++ implementation of matrix operations
#include<bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

class matrix {
private:
	vector< vector<long long> > mat; // Matrix is 0 indexed
public:
	void setDimensions(int row, int col);
	int totalRows() const;
	int totalColumns() const;
	void setCell(int row, int col, long long val);
	long long getCell(int row, int col) const;
	matrix operator * (const matrix &m) const; // Returns a new matrix as the result of this->mat x m
	matrix operator ^ (long long e) const; // Returns a new matrix as the result of this->mat ^ m
	friend ostream& operator<<(ostream& os, const matrix &m) {
		for (int i = 0; i < m.totalRows(); i++) {
			for (int j = 0; j < m.totalColumns(); j++) {
				os << m.mat[i][j] << " ";
			}
			os << endl;
		}
		return os;
	}
};
void matrix::setDimensions(int row, int col) {
	this->mat = vector< vector<long long> >(row, vector<long long>(col, 0));
}
int matrix::totalRows() const {
	return this->mat.size();
}
int matrix::totalColumns() const {
	assert(this->mat.size() > 0);
	return this->mat[0].size();
}
void matrix::setCell(int row, int col, long long val) {
	assert(row < this->totalRows());
	assert(col < this->totalColumns());
	this->mat[row][col] = val % MOD;
}
long long matrix::getCell(int row, int col) const {
	assert(row < this->totalRows());
	assert(col < this->totalColumns());
	return this->mat[row][col];
}
matrix matrix::operator * (const matrix &m) const {
	int rows = this->totalRows();
	int cols = m.totalColumns();
	int comm = this->totalColumns();
	assert(this->totalColumns() == m.totalRows());

	vector< vector<long long> > ret(rows, vector<long long>(cols, 0));

	for (int r = 0; r < rows; r++)
	for (int c = 0; c < cols; c++) {
		ret[r][c] = 0LL;

		for (int i = 0; i < comm; i++) {
			ret[r][c] += (this->mat[r][i] * m.mat[i][c]);
			ret[r][c] %= MOD;
		}
	}

	matrix retMat;
	retMat.setDimensions(rows, cols);
	for (int r = 0; r < rows; r++)
	for (int c = 0; c < cols; c++) {
		retMat.setCell(r, c, ret[r][c]);
	}

	return retMat;
}
matrix matrix::operator ^ (long long e) const {
	matrix ret;
	assert(this->totalRows() == this->totalColumns());

	if (e == 0) {
		ret.setDimensions(this->totalRows(), this->totalColumns());
		int dim = ret.totalRows();
		for (int i = 0; i < dim; i++) {
			ret.setCell(i, i, 1LL);
		}
	}
	else if (e % 2 == 1) {
		ret = (*this) * ((*this) ^ (e - 1));
	}
	else {
		ret = (*this) ^ (e / 2);
		ret = ret * ret;
	}

	return ret;
}

int main() {
	matrix m;
	m.setDimensions(2, 2);
	m.setCell(0, 0, 1);
	m.setCell(1, 1, 2);
	cerr << m;
}