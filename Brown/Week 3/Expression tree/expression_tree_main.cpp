#include "Common.h"
#include "test_runner.h"

#include <sstream>

using namespace std;

namespace Nodes {
	class Value : public Expression {
	public:
		Value(int val) : value_(val) {}

		int Evaluate() const override {
			return value_;
		}
		std::string ToString() const override {
			return std::to_string(value_);
		}
	private:
		int value_;
	};

	class Sum : public Expression {
	public:
		Sum(ExpressionPtr l, ExpressionPtr r) : lhs(std::move(l)), rhs(std::move(r)) {}

		int Evaluate() const override {
			return lhs->Evaluate() + rhs->Evaluate();
		}

		std::string ToString() const override {
			return  "(" + lhs->ToString() + ")" + "+"
		          + "(" + rhs->ToString() + ")";
		}

	private:
		ExpressionPtr lhs;
		ExpressionPtr rhs;
	};

	class Product : public Expression {
	public:
		Product(ExpressionPtr l, ExpressionPtr r) : lhs(std::move(l)), rhs(std::move(r)) {}

		int Evaluate() const override {
			return lhs->Evaluate() * rhs->Evaluate();
		}

		std::string ToString() const override {
			return  "(" + lhs->ToString() + ")" + "*"
				  + "(" + rhs->ToString() + ")";
		}

	private:
		ExpressionPtr lhs;
		ExpressionPtr rhs;
	};

}

ExpressionPtr Value(int value) {
	return make_unique<Nodes::Value>(value);
}

ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right) {
	return make_unique<Nodes::Sum>(std::move(left), std::move(right));
}

ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right) {
	return make_unique<Nodes::Product>(std::move(left), std::move(right));
}

string Print(const Expression* e) {
    if (!e) {
        return "Null expression provided";
    }
    stringstream output;
    output << e->ToString() << " = " << e->Evaluate();
    return output.str();
}

void Test() {
    ExpressionPtr e1 = Product(Value(2), Sum(Value(3), Value(4)));
    ASSERT_EQUAL(Print(e1.get()), "(2)*((3)+(4)) = 14");

    ExpressionPtr e2 = Sum(move(e1), Value(5));
    ASSERT_EQUAL(Print(e2.get()), "((2)*((3)+(4)))+(5) = 19");

    ASSERT_EQUAL(Print(e1.get()), "Null expression provided");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, Test);
    return 0;
}