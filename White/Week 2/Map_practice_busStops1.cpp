#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

int main() {
	int q;
	string command;
	vector<string>buses;
	map<string, vector<string>>source;
	cin >> q;
	for (int t = 0; t < q; t++) {
		cin >> command;
		if (command == "NEW_BUS") {
			string bus;
			int stop_count;
			cin >> bus >> stop_count;
			buses.push_back(bus);
			source[bus].resize(stop_count);
			for (int i = 0; i < stop_count; i++) {
				cin >> source[bus][i];
			}
		}
		if (command == "BUSES_FOR_STOP") {
			string stop;
			bool isStopExist(false);
			cin >> stop;
			for (const auto& bus : buses) {
				for (const auto& s : source[bus]) {
					if (s == stop) {
						isStopExist = true;
						cout << bus << " ";
						break;
					}
				}
			}
			if (!isStopExist) cout << "No stop";
			cout << endl;
		}
		if (command == "STOPS_FOR_BUS") {//8f8f8f8f8fqw89fq8fq89fq98f89q98qff89qfq89
			string search_bus;
			cin >> search_bus;
			if (source.count(search_bus) == 0) cout << "No bus" << endl;
			else {
				for (const auto& search_bus_stops : source[search_bus]) {
					bool isInterchangeExist = false;
					cout << "Stop " << search_bus_stops << ": ";
					//vector
					for (const auto& bus : buses) {
						if (bus == search_bus) continue;
						for (const auto& stop : source[bus]) {
							if (search_bus_stops == stop) {
								isInterchangeExist = true;
								cout << bus << " ";
								break;
							}
						}
					}
					if (!isInterchangeExist) cout << "no interchange";
					cout << endl;
				}
			}
		}
		if (command == "ALL_BUSES") {
			if (source.size() == 0) cout << "No buses" << endl;
			else {
				for (const auto& bus : source) {
					cout << "Bus " << bus.first << ": ";
					for (const auto& stop : bus.second) cout << stop << " ";
					cout << endl;
				}
			}
		}
	}
}