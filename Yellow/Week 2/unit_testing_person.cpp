#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        }
        catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
        catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

string FindNameByYear(const map<int, string>& names, int year) {
    string name;  // ���������� ��� ����������

    // ���������� ��� ������� �� ����������� ����� �������, �� ���� � ��������������� �������
    for (const auto& item : names) {
        // ���� ��������� ��� �� ������ �������, ��������� ���
        if (item.first <= year) {
            name = item.second;
        }
        else {
            // ����� ���� ������������, ��� ��� ��� ������ � ��� ����������� ��������� � ��������
            break;
        }
    }

    return name;
}

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        first_names[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        last_names[year] = last_name;
    }
    string GetFullName(int year) {
        // �������� ��� � ������� �� ��������� �� ��� year
        const string first_name = FindNameByYear(first_names, year);
        const string last_name = FindNameByYear(last_names, year);

        // ���� � ���, � ������� ����������
        if (first_name.empty() && last_name.empty()) {
            return "Incognito";

            // ���� ���������� ������ ���
        }
        else if (first_name.empty()) {
            return last_name + " with unknown first name";

            // ���� ���������� ������ �������
        }
        else if (last_name.empty()) {
            return first_name + " with unknown last name";

            // ���� �������� � ���, � �������
        }
        else {
            return first_name + " " + last_name;
        }
    }

private:
    map<int, string> first_names;
    map<int, string> last_names;
};


void Test_begining_from_first_name() {
    Person p;
    AssertEqual(p.GetFullName(1500), "Incognito", "Test 1");


    p.ChangeFirstName(1550, "Roman");
    p.ChangeLastName(1600, "Prokopchuk");

    AssertEqual(p.GetFullName(1575), "Roman with unknown last name", "Test 2");
    AssertEqual(p.GetFullName(1610), "Roman Prokopchuk", "Test 3");

    p.ChangeFirstName(1620, "Aboba");
    AssertEqual(p.GetFullName(1625), "Aboba Prokopchuk", "Test 4");

    p.ChangeFirstName(1650, "Romchik");
    p.ChangeLastName(1650, "Popchik");

    AssertEqual(p.GetFullName(1650), "Romchik Popchik", "Test 5");
}

void Test_begining_from_last_name() {
    Person p;
    AssertEqual(p.GetFullName(1500), "Incognito", "Test 1");


    p.ChangeLastName(1550, "Prokopchuk");
    p.ChangeFirstName(1600, "Roman");

    AssertEqual(p.GetFullName(1575), "Prokopchuk with unknown first name", "Test 2");
    AssertEqual(p.GetFullName(1610), "Roman Prokopchuk", "Test 3");

    p.ChangeLastName(1620, "Aboba");
    AssertEqual(p.GetFullName(1625), "Roman Aboba", "Test 4");

    p.ChangeFirstName(1650, "Romchik");
    p.ChangeLastName(1650, "Popchik");

    AssertEqual(p.GetFullName(1650), "Romchik Popchik", "Test 5");
}

//int main() {
//    TestRunner runner;
//    runner.RunTest(Test_begining_from_first_name,"Test_begining_from_first_name");
//    runner.RunTest(Test_begining_from_last_name, "Test_begining_from_last_name");
//    return 0;
//}
