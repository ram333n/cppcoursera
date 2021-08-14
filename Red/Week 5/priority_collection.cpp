#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <list>
#include <utility>
#include <vector>

using namespace std;

//using Id = size_t;

template <typename T>
class PriorityCollection {
public:
    using Id = size_t;

    // �������� ������ � ������� �����������
    // � ������� ����������� � ������� ��� �������������
    Id Add(T object) {
        objects.push_back({ move(object),0 });
        auto new_id = objects.size() - 1;
        priorities.insert({ 0, new_id });
        identifiers.insert(new_id);
        return new_id;
    }

    // �������� ��� �������� ��������� [range_begin, range_end)
    // � ������� �����������, ������� �������� �� ��������������
    // � �������� [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
        IdOutputIt ids_begin) 
    {
        for (; range_begin != range_end; ++range_begin) {
            *(ids_begin++) = Add(move(*range_begin));
        }
    }

    // ����������, ����������� �� ������������� ������-����
    // ����������� � ���������� �������
    bool IsValid(Id id) const {
        return identifiers.count(id) != 0;
    }

    // �������� ������ �� ��������������
    const T& Get(Id id) const {
        return objects[id].first;
    }

    // ��������� ��������� ������� �� 1
    void Promote(Id id) {
        pair<int, Id> to_promote = { objects[id].second , id };
        auto to_update = priorities.find(to_promote);
        priorities.erase(to_update);
        to_promote.first++;
        objects[id].second++;
        priorities.insert(to_promote);
    }

    // �������� ������ � ������������ ����������� � ��� ���������
    pair<const T&, int> GetMax() const {
        auto pos_in_set = prev(priorities.end());
        return { objects[pos_in_set->second].first, pos_in_set->first };
    }

    // ���������� GetMax, �� ������� ������� �� ����������
    pair<T, int> PopMax() {
        pair<int, Id> info_about_max_elem = *prev(priorities.end());
        priorities.erase(prev(priorities.end()));
        identifiers.erase(info_about_max_elem.second);
        return { move(objects[info_about_max_elem.second].first),info_about_max_elem.first };
    }

private:
    vector<pair<T, int>> objects;
    set<pair<int, Id>> priorities;
    set<Id> identifiers;
};


class StringNonCopyable : public string {
public:
    using string::string;  // ��������� ������������ ������������ ������
    StringNonCopyable(const StringNonCopyable&) = delete;
    StringNonCopyable(StringNonCopyable&&) = default;
    StringNonCopyable& operator=(const StringNonCopyable&) = delete;
    StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");

    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i) {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    return 0;
}
