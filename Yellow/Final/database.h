#pragma once
#include "date.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

ostream& operator<<(ostream& os, const pair<Date, string>& p);

class Database {
public:
	void Add(const Date& data, const string& event);
	void Print(ostream& os) const;

	int RemoveIf(function<bool(Date, string)> predicate);
	vector<pair<Date, string>> FindIf(function<bool(Date, string)> predicate) const;

	pair<Date, string> Last(const Date& d) const ;

private:
	map<Date, set<string>> ordered_storage;
	map<Date, vector<string>> storage;
};
