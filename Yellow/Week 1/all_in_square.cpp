#include <iostream>
#include <vector>
#include <utility>
#include <map>

using namespace std;

template <typename T> 
T Sqr(const T& x);

template <typename T>
vector<T> Sqr(const vector<T>& v);

template <typename First, typename Second>
pair<First,Second> Sqr(const pair<First,Second>& p);

template <typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& m);


template <typename T>
T Sqr(const T& x) {
	return x * x;
}

template <typename T>
vector<T> Sqr(const vector<T>& v) {
	vector<T>result;
	for (const T& elem : v) {
		result.push_back(Sqr(elem));
	}
	return result;
}

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p) {
	return make_pair(Sqr(p.first), Sqr(p.second));
}

template <typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& m) {
	map<Key, Value> result;
	for (const auto& p : m) {
		result[p.first] = Sqr(p.second);
	}
	return result;
}

int main() {
	// Пример вызова функции
	vector<int> v = { 1, 2, 3 };
	cout << "vector:";
	for (int x : Sqr(v)) {
		cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
	  {4, {2, 2}},
	  {7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
		cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}
}