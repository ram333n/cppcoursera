#include "test_runner.h"
#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	const size_t range_size = range_end - range_begin;

	if (range_size < 2) {
		return;
	}

	vector<typename RandomIt::value_type> pool(make_move_iterator(range_begin),
												make_move_iterator(range_end));

	auto first_border = pool.begin() + range_size / 3;
	auto second_border = pool.begin() + (2 * range_size) / 3;

	MergeSort(pool.begin(), first_border);
	MergeSort(first_border, second_border);
	MergeSort(second_border, pool.end());

	vector<typename RandomIt::value_type> temp_v;

	merge(make_move_iterator(pool.begin()), make_move_iterator(first_border),
		make_move_iterator(first_border), make_move_iterator(second_border),
		back_inserter(temp_v));

	merge(make_move_iterator(temp_v.begin()), make_move_iterator(temp_v.end()),
		make_move_iterator(second_border), make_move_iterator(pool.end()),
		range_begin);
}

void TestIntVector() {
	vector<int> numbers = { 6, 1, 3, 9, 1, 9, 8, 12, 1 };
	MergeSort(begin(numbers), end(numbers));
	ASSERT(is_sorted(begin(numbers), end(numbers)));
}

//int main() {
//	TestRunner tr;
//	RUN_TEST(tr, TestIntVector);
//	return 0;
//}
