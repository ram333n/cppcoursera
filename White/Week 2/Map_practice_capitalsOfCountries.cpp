#include <iostream>
#include <map>
#include <string>

using namespace std;

void psevdo_main_2() {
	int q;
	string command;
	map<string, string> source;
	cin >> q;
	for (int t = 0; t < q; t++) {
		cin >> command;
		if (command == "CHANGE_CAPITAL") {
			string country, new_capital;
			cin >> country >> new_capital;
			if (source.count(country) == 0) {
				cout << "Introduce new country " << country << " with capital " << new_capital << endl;
				source[country] = new_capital;
			}
			else if (source[country] == new_capital) cout << "Country " << country << " hasn't changed its capital" << endl;
			else {
				cout << "Country " << country << " has changed its capital from " << source[country] << " to " << new_capital << endl;
				source[country] = new_capital;
			}
		}
		if (command == "ABOUT") {
			string country;
			cin >> country;
			if (source.count(country) == 0) cout << "Country " << country << " doesn't exist" << endl;
			else cout << "Country " << country << " has capital " << source[country] << endl;
		}
		if (command == "DUMP") {
			if (source.size() == 0) cout << "There are no countries in the world" << endl;
			else for (const auto& c : source) cout << c.first << "/" << c.second << " ";
		}
		if (command == "RENAME") {
			string old_country_name, new_country_name;
			cin >> old_country_name >> new_country_name;
			if (old_country_name == new_country_name || source.count(old_country_name) == 0 || source.count(new_country_name) != 0) cout << "Incorrect rename, skip" << endl;
			else {
				cout << "Country " << old_country_name << " with capital " << source[old_country_name] << " has been renamed to " << new_country_name << endl;
				source[new_country_name] = source[old_country_name];
				source.erase(old_country_name);
			}
		}
	}
}