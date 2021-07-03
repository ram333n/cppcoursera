//#include <iostream>
//#include <map>
//#include <set>
//#include <sstream>
//#include <stdexcept>
//#include <string>
//#include <vector>
//
//using namespace std;
//
//template <class T>
//ostream& operator << (ostream& os, const vector<T>& s) {
//    os << "{";
//    bool first = true;
//    for (const auto& x : s) {
//        if (!first) {
//            os << ", ";
//        }
//        first = false;
//        os << x;
//    }
//    return os << "}";
//}
//
//template <class T>
//ostream& operator << (ostream& os, const set<T>& s) {
//    os << "{";
//    bool first = true;
//    for (const auto& x : s) {
//        if (!first) {
//            os << ", ";
//        }
//        first = false;
//        os << x;
//    }
//    return os << "}";
//}
//
//template <class K, class V>
//ostream& operator << (ostream& os, const map<K, V>& m) {
//    os << "{";
//    bool first = true;
//    for (const auto& kv : m) {
//        if (!first) {
//            os << ", ";
//        }
//        first = false;
//        os << kv.first << ": " << kv.second;
//    }
//    return os << "}";
//}
//
//template<class T, class U>
//void AssertEqual(const T& t, const U& u, const string& hint = {}) {
//    if (t != u) {
//        ostringstream os;
//        os << "Assertion failed: " << t << " != " << u;
//        if (!hint.empty()) {
//            os << " hint: " << hint;
//        }
//        throw runtime_error(os.str());
//    }
//}
//
//void Assert(bool b, const string& hint) {
//    AssertEqual(b, true, hint);
//}
//
//class TestRunner {
//public:
//    template <class TestFunc>
//    void RunTest(TestFunc func, const string& test_name) {
//        try {
//            func();
//            cerr << test_name << " OK" << endl;
//        }
//        catch (exception& e) {
//            ++fail_count;
//            cerr << test_name << "fail: " << e.what() << endl;
//        }
//        catch (...) {
//            ++fail_count;
//            cerr << "Unknown exception caught" << endl;
//        }
//    }
//
//    ~TestRunner() {
//        if (fail_count > 0) {
//            cerr << fail_count << " unit tests failed. Terminate" << endl;
//            exit(1);
//        }
//    }
//
//private:
//    int fail_count = 0;
//};
//
//bool IsPalindrom(const string& str) {
//    for (size_t i = 0; i < str.size() / 2; ++i) {
//        if (str[i] != str[str.size() - i - 1]) {
//            return false;
//        }
//    }
//    return true;
//}
//
//void Test() {
//    //madam
//    Assert(IsPalindrom("madam"), "Test 1");
//    Assert(!IsPalindrom("Madam"), "Test 2");
//    Assert(!IsPalindrom("madaM"), "Test 3");
//    Assert(!IsPalindrom("MadAM"), "Test 4");
//    Assert(!IsPalindrom("Ma dam"), "Test 5");
//
//    Assert(IsPalindrom(""), "Test 6");
//    Assert(IsPalindrom(" "), "Test 7");
//    Assert(IsPalindrom("a"), "Test 8");
//    Assert(!IsPalindrom(" a"), "Test 9");
//
//    Assert(IsPalindrom("wasitacaroracatisaw"), "Test 10");
//    Assert(!IsPalindrom("wasitacaro racatisaw"), "Test 11");
//    Assert(!IsPalindrom(" wasitacaroracatisaw"), "Test 12");
//    Assert(IsPalindrom(" wasitacaroracatisaw "), "Test 13");
//
//    Assert(IsPalindrom("abccba"), "Test 14");
//    Assert(IsPalindrom("     "), "Test 15");
//}
//
//int main() {
//    TestRunner runner;
//    runner.RunTest(Test,"");
//    return 0;
//}
