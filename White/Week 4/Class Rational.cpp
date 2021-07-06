#include <iostream>
#include <string>
#include <sstream>
#include <exception>

using namespace std;

int gcd(int a, int b) {
    while (a > 0 && b > 0)
    {
        if (a > b) a %= b;
        else b %= a;      
    }
    return a + b;
}

class Rational {
public:
    Rational() {
        numerator = 0;
        denominator = 1;
    }

    Rational(const int& new_numerator, const int& new_denominator) {
        if (new_denominator == 0) {
            throw invalid_argument("Invalid argument");
        }
        if (new_numerator == 0) {
            numerator = 0;
            denominator = 1;
        }
        else {
            int t = gcd(abs(new_numerator), abs(new_denominator));
            numerator = (new_numerator* (((new_numerator > 0 || new_numerator < 0) && new_denominator > 0) ? 1 : -1) / t);
            denominator = abs(new_denominator) / t;
        }
    }

    int Numerator() const {
        return numerator;
    }

    int Denominator() const {
        return denominator;
    }

private:
    int numerator;
    int denominator;
};

bool operator ==(const Rational& lhs, const Rational& rhs) {
    return (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator());
}

Rational operator +(const Rational& lhs, const Rational& rhs) {
    return { lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),rhs.Denominator() * lhs.Denominator() };
}

Rational operator -(const Rational& lhs, const Rational& rhs) {
    return { lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),rhs.Denominator() * lhs.Denominator() };
}

Rational operator *(const Rational& lhs, const Rational& rhs) {
    return { lhs.Numerator() * rhs.Numerator(),lhs.Denominator() * rhs.Denominator() };
}

Rational operator /(const Rational& lhs, const Rational& rhs) {
    if (rhs.Numerator() == 0) throw domain_error("Division by zero");
    return { lhs.Numerator() * rhs.Denominator() ,lhs.Denominator() * rhs.Numerator() };
}

ostream& operator<<(ostream& stream, const Rational& r) {
    stream << r.Numerator() << "/" << r.Denominator();
    return stream;
}

istream& operator>>(istream& input, Rational& r) {
    int num(NULL), den(NULL); 
    char op;
    if (input && input >> num && (input >> op && op == '/') && input >> den) {
        r = { num,den };
    }
    return input;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return (lhs - rhs).Numerator() < 0;
}

Rational ApplyOperation(const Rational& r1, const Rational& r2, const char& op) {
    switch (op) {
        case '+': return r1 + r2; break;
        case '-': return r1 - r2; break;
        case '*': return r1 * r2; break;
        case '/': return r1 / r2; break;
    }
}


int main() {
    while (true) {
        Rational r1, r2;
        char oper;
        try {
            cin >> r1 >> oper >> r2;
            cout << ApplyOperation(r1, r2, oper);
        }
        catch (exception& ex) {
            cout << ex.what() << endl;
        }
    }

}