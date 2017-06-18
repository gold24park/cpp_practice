/* complex class */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

class Matrix {
	int** values;
	int row, column;
public:
	Matrix(const int row, const int column) {
		this->row = row;
		this->column = column;
		this->values = new int*[row];
		for (int i = 0; i < row; i++)
			values[i] = new int[column];
	}

	Matrix(const Matrix& another) {
		for (int i = 0; i < column; i++)
			delete[] values[i];
		delete[] values;

		row = another.row;
		column = another.column;
		this->values = new int*[row];
		for (int i = 0; i < row; i++) {
			values[i] = new int[column];
			for (int j = 0; j < column; j++) {
				values[i][j] = another.values[i][j];
			}
		}

	}

	~Matrix() {
		for (int i = 0; i < column; i++)
			delete[] values[i];
		delete[] values;
	}

	Matrix& operator = (const Matrix& another) {
		for (int i = 0; i < column; i++)
			delete[] values[i];
		delete[] values;
		row = another.row;
		column = another.column;
		this->values = new int*[row];
		for (int i = 0; i < row; i++) {
			values[i] = new int[column];
			for (int j = 0; j < column; j++) {
				values[i][j] = another.values[i][j];
			}
		}
		return *this;
	}

	friend Matrix operator + (Matrix& m1, const Matrix& m2) {
		Matrix m(m1);
		for (int i = 0; i < m.row; i++) {
			for (int j = 0; j < m.column; j++) {
				m.values[i][j] += m2.values[i][j];
			}
		}
		return m;
	}

	friend Matrix operator * (Matrix& m1, const int value) {
		Matrix m(m1);
		for (int i = 0; i < m.row; i++) {
			for (int j = 0; j < m.column; j++) {
				m.values[i][j] *= value;
			}
		}
		return m;
	}

	friend istream& operator >> (istream &input, Matrix& matrix) {
		for (int i = 0; i < matrix.row; i++) {
			for (int j = 0; j < matrix.column; j++) {
				input >> matrix.values[i][j];
			}
		}
		return input;
	}

	friend ostream& operator << (ostream& os, const Matrix& matrix) {
		for (int i = 0; i < matrix.row; i++) {
			for (int j = 0; j < matrix.column; j++) {
				os << matrix.values[i][j] << "\t";
			}
			os << endl;
		}
		return os;
	}
};



int main() {
	Matrix m1(2, 2), m2(2, 2);
	cin >> m1;
	cin >> m2;

	Matrix m3 = m1 + m2;
	Matrix m4 = m3 * 10;

	cout << m3 << endl;
	cout << m4 << endl;
}