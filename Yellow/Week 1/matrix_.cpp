#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix {
public:
	Matrix() {
		num_cols = num_rows = 0;
	}

	Matrix(const int& new_num_rows, const int& new_num_cols) {
		Reset(new_num_rows, new_num_cols);
	}

	void Reset(const int& new_num_rows, const int& new_num_cols) {
		if (new_num_rows < 0) {
			throw out_of_range("num_rows must be >= 0");
		}
		if (new_num_cols < 0) {
			throw out_of_range("num_columns must be >= 0");
		}
		if (new_num_rows == 0 || new_num_cols == 0) {
			num_rows = num_cols = 0;
		}
		else {
			num_rows = new_num_rows;
			num_cols = new_num_cols;
			data.resize(num_rows);
			for (auto& c : data) {
				c.assign(num_cols, 0);
			}
		}
	}

	int At(const int& row, const int& col) const {
		return data.at(row).at(col);
	}

	int& At(const int& row, const int& col){
		return data.at(row).at(col);
	}

	int GetNumRows() const {
		return num_rows;
	}

	int GetNumColumns() const {
		return num_cols;
	}


private:
	vector<vector<int>>data;
	int num_rows;
	int num_cols;
};


istream& operator>>(istream& input, Matrix& m) {
	int rows(0), cols(0);
	input >> rows >> cols;
	m.Reset(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			input>>m.At(i, j);
		}
	}
	return input;
}

ostream& operator<<(ostream& output, const Matrix& m) {
	output << m.GetNumRows() << " " << m.GetNumColumns() << endl;
	for (int i = 0; i < m.GetNumRows(); i++) {
		for (int j = 0; j < m.GetNumColumns(); j++) {
			output << m.At(i, j) << " ";
		}
		output << endl;
	}
	return output;
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
	if (!(lhs.GetNumColumns() != rhs.GetNumColumns() || lhs.GetNumRows() != rhs.GetNumRows())) {
		for (int i = 0; i < lhs.GetNumRows(); i++) {
			for (int j = 0; j < lhs.GetNumColumns(); j++) {
				if (rhs.At(i, j) != lhs.At(i, j)) return false;
			}
		}
		return true;
	}
	return false;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
	if (lhs.GetNumColumns() != rhs.GetNumColumns() || lhs.GetNumRows() != rhs.GetNumRows()) {
		throw invalid_argument("Invalid arguments");
	}
	Matrix result;
	result.Reset(lhs.GetNumRows(), lhs.GetNumColumns());
	for (int i = 0; i < lhs.GetNumRows(); i++) {
		for (int j = 0; j < lhs.GetNumColumns(); j++) {
			result.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
		}
	}
	return result;
}

/*int main() {
	try {
		std::cout << std::boolalpha << (Matrix(0, 1) == Matrix(2, 0)) << '\n';
	}
	catch (out_of_range& ex) {
		cout << ex.what() << endl;
	}
}*/
