// C++ implementation of matrix operations
#include<bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

template<typename T>
class matrix {
private:
	vector< vector<T> > mat; // Matrix is 0 indexed
public:
	const int MOD = int(1e9) + 7;
	void setDimensions(int row, int col);
	int totalRows() const;
	int totalColumns() const;
	void setCell(int row, int col, T val);
	T getCell(int row, int col) const;
	matrix operator * (const matrix &m) const; // Returns a new matrix as the result of this->mat x m
	matrix operator ^ (long long e) const; // Returns a new matrix as the result of this->mat ^ m
	friend ostream& operator<<(ostream& os, const matrix &m) {
		for (int i = 0; i < m.totalRows(); i++) {
			for (int j = 0; j < m.totalColumns(); j++) {
				os << m.mat[(uint)i][(uint)j] << " ";
			}
			os << endl;
		}
		return os;
	}
};
template<typename T>
void matrix<T>::setDimensions(int row, int col) {
	this->mat = vector< vector<T> >((uint)row, vector<T>((uint)col, 0));
}
template<typename T>
int matrix<T>::totalRows() const {
	return (int)this->mat.size();
}
template<typename T>
int matrix<T>::totalColumns() const {
	assert(this->mat.size() > 0);
	return (int)this->mat[0].size();
}
template<typename T>
void matrix<T>::setCell(int row, int col, T val) {
	assert(row < this->totalRows());
	assert(col < this->totalColumns());
	this->mat[(uint)row][(uint)col] = val % MOD;
}
template<typename T>
T matrix<T>::getCell(int row, int col) const {
	assert(row < this->totalRows());
	assert(col < this->totalColumns());
	return this->mat[row][col];
}
template<typename T>
matrix<T> matrix<T>::operator * (const matrix &m) const {
	int rows = this->totalRows();
	int cols = m.totalColumns();
	int comm = this->totalColumns();
	assert(this->totalColumns() == m.totalRows());

	vector< vector<T> > ret(rows, vector<T>(cols, 0));

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
template<typename T>
matrix<T> matrix<T>::operator ^ (long long e) const {
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
	matrix<long long> m;
	m.setDimensions(2, 2);
	m.setCell(0, 0, 1);
	m.setCell(1, 1, 2);
	cerr << m;
}