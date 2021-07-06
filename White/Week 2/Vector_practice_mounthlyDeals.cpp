#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
	int q, month(0);
	string command;
	vector<vector<string>> source(31);
	const vector<int>days = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	cin >> q;
	for (int t = 0; t < q; t++) {
		cin >> command;
		if (command == "ADD") {
			int i;
			string s;
			cin >> i >> s;
			source[i - 1].push_back(s);
		}
		if (command == "DUMP") {
			int i;
			cin >> i;
			cout << source[i - 1].size();
			for (auto& s : source[i - 1]) cout << " " << s << " ";//
			cout << '\n';
		}
		if (command == "NEXT") {
			int currentDays = days[month];
			month = (month + 1) % 12;

			if (days[month] < days[month - 1]) {
				for (int i = currentDays - 1; i >= days[month]; i--) {
					source[days[month]-1].insert(end(source[days[month] - 1]), begin(source[i]), end(source[i]));
				}
			}
			source.resize(days[month]);
		}
	}
}