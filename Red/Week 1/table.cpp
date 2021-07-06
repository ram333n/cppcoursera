#include "test_runner.h"

#include<vector>
using namespace std;

template<typename T>
class Table {
public:
	Table(const size_t& rows, const size_t& columns) {
		Resize(rows, columns);
	}

	vector<T>& operator[](const size_t& idx) {
		return data[idx];
	}

	const vector<T>& operator[](const size_t& idx) const {
		return data[idx];
	}

	void Resize(const size_t& rows, const size_t& columns) {
		if (!rows || !columns) {
			this->rows = this->columns = 0;
		}
		else {
			this->rows = rows;
			this->columns = columns;
		}

		data.resize(rows);
		for (auto& c : data) {
			c.resize(columns);
		}
	}

	pair<size_t, size_t> Size() const {
		return { this->rows,this->columns };
	}

private:
	vector<vector<T>> data;
	size_t rows, columns;
};

void TestTable() {
	Table<int> t(1, 1);
	ASSERT_EQUAL(t.Size().first, 1u);
	ASSERT_EQUAL(t.Size().second, 1u);
	t[0][0] = 42;
	ASSERT_EQUAL(t[0][0], 42);
	t.Resize(3, 4);
	ASSERT_EQUAL(t.Size().first, 3u);
	ASSERT_EQUAL(t.Size().second, 4u);
}

//int main() {
//	cout << "RUN TEST\n";
//	TestRunner tr;
//	RUN_TEST(tr, TestTable);
//	return 0;
//}