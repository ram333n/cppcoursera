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
//int gcd(int a, int b) {
//    while (a > 0 && b > 0)
//    {
//        if (a > b) a %= b;
//        else b %= a;
//    }
//    return a + b;
//}
//
//class Rational {
//public:
//    Rational() {
//        numerator = 0;
//        denominator = 1;
//    }
//
//    Rational(const int& new_numerator, const int& new_denominator) {
//        if (new_denominator == 0) {
//            throw invalid_argument("Invalid argument");
//        }
//        if (new_numerator == 0) {
//            numerator = 0;
//            denominator = 1;
//        }
//        else {
//            int t = gcd(abs(new_numerator), abs(new_denominator));
//            numerator = (new_numerator * (((new_numerator > 0 || new_numerator < 0) && new_denominator > 0) ? 1 : -1) / t);
//            denominator = abs(new_denominator) / t;
//        }
//    }
//
//    int Numerator() const {
//        return numerator;
//    }
//
//    int Denominator() const {
//        return denominator;
//    }
//
//private:
//    int numerator;
//    int denominator;
//};
//
//void TestConstructor_1() {
//    Rational r;
//    bool check = r.Numerator() == 0 && r.Denominator() == 1;
//    Assert(check, "Default constructor");
//}
//
//void TestConstructor_2() {
//
//
//    {
//        Rational r(3, 4);
//        Assert(r.Numerator() == 3 && r.Denominator() == 4, "Checking second part");
//    }
//
//    {
//        Rational r(9, 12);
//        Assert(r.Numerator() == 3 && r.Denominator() == 4, "a Checking second part");
//    }
//
//    {
//        Rational r(33, 44);
//        Assert(r.Numerator() == 3 && r.Denominator() == 4, "b Checking second part");
//    }
//
//    {
//        Rational r(9, -12);
//        Assert(r.Numerator() == -3 && r.Denominator() == 4, "c Checking second part");
//    }
//
//    {
//        Rational r(-9, 12);
//        Assert(r.Numerator() == -3 && r.Denominator() == 4, "d Checking second part");
//    }
//
//    {
//        Rational r(333, 111);
//        Assert(r.Numerator() == 3 && r.Denominator() == 1, "e Checking second part");
//    }
//
//    {
//        Rational r(-333, 111);
//        Assert(r.Numerator() == -3 && r.Denominator() == 1, "f Checking second part");
//    }
//
//    {
//        Rational r(-56, -112);
//        Assert(r.Numerator() == 1 && r.Denominator() == 2, "g Checking second part");
//    }
//
//    {
//        Rational r(56, 4324);
//        Assert(r.Numerator() == 14 && r.Denominator() == 1081, "q Checking second part");
//    }
//
//    {
//        Rational r(numeric_limits<int>::max(), 1);
//        Assert(r.Numerator() == numeric_limits<int>::max() && r.Denominator() == 1, " vChecking second part");
//    }
//
//    {
//        Rational r(numeric_limits<int>::min(), 1);
//        Assert(r.Numerator() == numeric_limits<int>::min() && r.Denominator() == 1, " u Checking second part");
//    }
//
//    /*{
//        Rational r(1, numeric_limits<int>::min());
//        Assert(r.Numerator() == 1 && r.Denominator() == abs(numeric_limits<int>::min()), " x Checking second part");
//    }*/
//
//
//
//}
//
//void TestConstructor_3() {
//    {
//        Rational r(-3, 4);
//        Assert(r.Numerator() < 0 && r.Denominator() > 0, "Checking third part");
//    }
//
//    {
//        Rational r(3, -4);
//        Assert(r.Numerator() < 0 && r.Denominator() > 0, "Checking third part");
//    }
//}
//
//void TestConstructor_4() {
//
//    {
//        Rational r(-12, -11);
//        Assert(r.Numerator() > 0 && r.Denominator() > 0, "Checking third part");
//    }
//
//    {
//        Rational r(-42, -87678);
//        Assert(r.Numerator() > 0 && r.Denominator() > 0, "Checking third part");
//    }
//
//}
//
//void TestConstructor_5() {
//    {
//        Rational r(0, -3);
//        Assert(r.Numerator() == 0 && r.Denominator() == 1, "Checking, when Numerator == 0");
//    }
//
//    {
//        Rational r(0, 12);
//        Assert(r.Numerator() == 0 && r.Denominator() == 1, "Checking, when Numerator == 0");
//    }
//
//    {
//        Rational r(0, -1);
//        Assert(r.Numerator() == 0 && r.Denominator() == 1, "Checking, when Numerator == 0");
//    }
//
//    {
//        Rational r(0, 3233);
//        Assert(r.Numerator() == 0 && r.Denominator() == 1, "Checking, when Numerator == 0");
//    }
//}
//
//
//
//void TestAll() {
//    TestRunner tr;
//    tr.RunTest(TestConstructor_1, "");
//    tr.RunTest(TestConstructor_2, "");
//    tr.RunTest(TestConstructor_3, "");
//    tr.RunTest(TestConstructor_4, "");
//    tr.RunTest(TestConstructor_5, "");
//}
//
//
///*int main() {
//    TestAll();
//    return 0;
//}*/
