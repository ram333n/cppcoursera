#include "test_runner.h"
#include "profile.h"

#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

//SLOW IMPL OF TASK

//template <typename String>
//using Group = vector<String>;
//
//
//template <typename String>
//using Char = typename String::value_type;
//
//template <typename String>
//vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
//	vector<Group<String>> result;
//	vector<set<Char<String>>> sorted_groups;
//
//	for (auto& str : strings) {
//		set<Char<String>> str_chars;
//
//		for (auto& c : str) {
//			str_chars.insert(c);
//		}
//		
//		bool is_group_found = false;
//
//		for (size_t i = 0; i < sorted_groups.size(); ++i) {
//			if (sorted_groups[i] == str_chars) {
//				is_group_found = true;
//				result[i].push_back(move(str));
//				break;
//			}
//		}
//
//		if (!is_group_found) {
//			Group<String> to_push;
//			to_push.push_back(move(str));
//			result.push_back(move(to_push));
//			sorted_groups.push_back(move(str_chars));
//		}
//	}
//
//	return result;
//}


template <typename String>
using Group = vector<String>;


template <typename String>
using Char = typename String::value_type;

template <typename String>
String GetKey(const String& str) {
	String result = str;
	sort(begin(result), end(result));
	result.erase(unique(begin(result), end(result)), end(result));
	return result;
}

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
	map<String, Group<String>> map_of_groups;
	for (String& str : strings) {
		map_of_groups[GetKey(str)].push_back(move(str));
	}
	vector<Group<String>> result;
	for (auto& p : map_of_groups) {
		result.push_back(move(p.second));
	}
	return result;
}


void TestGroupingABC() {
	vector<string> strings = { "caab", "abc", "cccc", "bacc", "c" };
	auto groups = GroupHeavyStrings(strings);
	ASSERT_EQUAL(groups.size(), 2);
	sort(begin(groups), end(groups));  // Порядок групп не имеет значения
	ASSERT_EQUAL(groups[0], vector<string>({ "caab", "abc", "bacc" }));
	ASSERT_EQUAL(groups[1], vector<string>({ "cccc", "c" }));
}

void TestGroupingReal() {
	vector<string> strings = { "law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl" };
	auto groups = GroupHeavyStrings(strings);
	ASSERT_EQUAL(groups.size(), 4);
	sort(begin(groups), end(groups));  // Порядок групп не имеет значения
	ASSERT_EQUAL(groups[0], vector<string>({ "laptop", "paloalto" }));
	ASSERT_EQUAL(groups[1], vector<string>({ "law", "wall", "awl" }));
	ASSERT_EQUAL(groups[2], vector<string>({ "port" }));
	ASSERT_EQUAL(groups[3], vector<string>({ "top", "pot" }));
}

int main() {
	TestRunner tr;
	{	LOG_DURATION("");
		RUN_TEST(tr, TestGroupingABC);
		RUN_TEST(tr, TestGroupingReal);
		return 0;
	}
}
