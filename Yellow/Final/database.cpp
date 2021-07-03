#include "database.h"

using namespace std;

ostream& operator<<(ostream& os, const pair<Date, string>& p){
	os << p.first << " " << p.second;
	return os;
}


void Database::Add(const Date& data, const string& event) {
	auto is_not_copy = ordered_storage[data].insert(event);
	if (is_not_copy.second) {
		storage[data].push_back(event);
	}

}

void Database::Print(ostream& os) const {
	for (const auto& date : storage) {
		for (const auto& event : date.second) {
			os << make_pair(date.first, event) << endl;
		}
	}
}


int Database::RemoveIf(function<bool(Date, string)> predicate) {
	int erased = 0;
	for (auto it = storage.begin(); it != storage.end(); ) {
		Date current_date = it->first;
		auto to_delete = stable_partition(it->second.begin(), it->second.end(),
			[=](const string& event) {
				return !predicate(current_date, event);
			});
		erased += it->second.end() - to_delete;
		it->second.erase(to_delete, it->second.end());

		if (it->second.empty()) {
			storage.erase(it++);
		}
		else {
			it++;
		}
	}
	ordered_storage.clear();

	for (const auto& date_pair : storage) {
		for (const auto& event : date_pair.second) {
			ordered_storage[date_pair.first].insert(event);
		}
	}

	return erased;
}



vector<pair<Date, string>> Database::FindIf(function<bool(Date, string)> predicate) const {
	vector<pair<Date, string>> result;

	for (auto map_it = storage.begin(); map_it != storage.end(); ++map_it) {
		Date current_date = map_it->first;
		auto vector_it = map_it->second.begin();

		while (vector_it != map_it->second.end()) {
			vector_it = find_if(vector_it, map_it->second.end(),
				[=](const string& event) {
					return predicate(current_date, event);
				});

			if (vector_it == map_it->second.end()) {
				break;
			}

			result.push_back(make_pair(current_date, *vector_it));

			if (vector_it != map_it->second.end()) {
				vector_it++;
			}
		}
	}

	return result;
}



pair<Date, string> Database::Last(const Date& d) const {

	if (storage.empty()) {
		throw invalid_argument("");
	}

	if (d < storage.begin()->first) {
		throw invalid_argument("");
	}

	auto current_it = storage.upper_bound(d);

	
	current_it--;
	return make_pair(current_it->first, current_it->second[current_it->second.size() - 1]);

}
	
