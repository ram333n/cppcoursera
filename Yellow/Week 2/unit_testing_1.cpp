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
//            cerr << test_name << "OK" << endl;
//        }
//        catch (exception& e) {
//            ++fail_count;
//            cerr << test_name << " fail: " << e.what() << endl;
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
//int GetDistinctRealRootCount(double a, double b, double c) {
//    if (a) {
//        double D = b * b - 4 * a * c;
//        return (D > 0 ? 2 : (D == 0 ? 1 : 0));
//    }
//    else {
//        //bx+c=0
//        if (b) {
//            return 1;
//        }
//        return 0;
//    }
//}
//void TestResult(){
//    for (int i = 0; i < 20; i++) {
//        int a = rand() % 101 - 50;
//        int b = rand() % 101 - 50;
//        int c = rand() % 101 - 50;
//        int r = GetDistinctRealRootCount(a, b, c);
//        Assert(r<3 && r>-1,"");
//    }
//}
//
//void TestLinear() {
//    AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0);//c=0 => zero
//    AssertEqual(GetDistinctRealRootCount(0, 0, -231), 0);
//    AssertEqual(GetDistinctRealRootCount(0, 0, -13), 0);
//    AssertEqual(GetDistinctRealRootCount(0, 1, 0), 1);//bx=0;
//    AssertEqual(GetDistinctRealRootCount(0, -123, 0), 1);
//    AssertEqual(GetDistinctRealRootCount(0, 1, 1), 1);//bx+c=0;
//    AssertEqual(GetDistinctRealRootCount(0, 31, 12), 1);
//    AssertEqual(GetDistinctRealRootCount(0, -21, -131), 1);
//}
//
//void TestNoRoots() {
//    AssertEqual(GetDistinctRealRootCount(1, 0, 1), 0);//D<0
//    AssertEqual(GetDistinctRealRootCount(3,-6,333), 0);//D<0
//    AssertEqual(GetDistinctRealRootCount(3.232, 8, 6666), 0);//D<0
//    AssertEqual(GetDistinctRealRootCount(5, 25, 13337), 0);
//}
//
//void TestOneRoot(){
//    int p, q;
//    for (int i = 0; i < 100; i++) {
//        q = i * i;
//        p = -2 * i;
//        AssertEqual(GetDistinctRealRootCount(1, p, q), 1);
//    }
//}
//
//void TestTwoRoots() {
//
//}
//
//void TestAll() {
//    TestRunner tr;
//    tr.RunTest(TestResult, "");
//    tr.RunTest(TestLinear, "");
//    tr.RunTest(TestOneRoot, "");
//    tr.RunTest(TestNoRoots, "");
//}
//
///*int main() {
//    TestAll();
//    return 0;
//}*/
