#include <iostream>
#include <vector>
#include <list>

const int MAX_N = 100'000;

using namespace std;
using Position = list<int>::iterator;

int main() {
	int n;
	cin >> n;

	list<int> sportsmen;
	vector<Position> positions(MAX_N + 1,sportsmen.end());

	for (int i = 0; i < n; ++i) {
		int to_insert, pos_to_insert;
		cin >> to_insert >> pos_to_insert;
		auto pos_of_current_sportsman = sportsmen.insert(positions[pos_to_insert], to_insert);
		positions[to_insert] = pos_of_current_sportsman;
	}

	for (int s : sportsmen) {
		cout << s << '\n';
	}
}
