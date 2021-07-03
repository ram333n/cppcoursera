#include <iostream>
#include <string>
#include <iomanip>
#include <memory>
#include <sstream>
#include <vector>
using namespace std;

const double PI = 3.14;

class Figure {
public:
	virtual string Name() = 0;
	virtual double Perimeter() = 0;
	virtual double Area() = 0;
};


class Triangle : public Figure {
public:
	Triangle(const double& new_a,
		const double& new_b,
		const double& new_c,
		const string& s) :a(new_a), b(new_b), c(new_c), name(s) {}

	virtual string Name() override { return name; }
	virtual double Perimeter() override  { return a + b + c; }
	virtual double Area() override {
		double p = Perimeter()/2;
		return sqrt(p * (p - a) * (p - b) * (p - c));
	}

private:
	const double a, b, c;
	const string name;
};

class Rect : public Figure {
public:
	Rect(const double& new_a, const double& new_b, const string& n) :a(new_a), b(new_b), name(n) {}

	virtual string Name() override { return name; }
	virtual double Perimeter() override  { return 2 * (a + b); }
	virtual double Area() override  { return a * b; }

private:
	const double a, b;
	const string name;
};

class Circle : public Figure {
public:
	Circle(const double& new_r, const string& n) : r(new_r), name(n) {}

	virtual string Name() override { return name; }
	virtual double Perimeter() override { return 2 * PI * r; }
	virtual double Area() override { return PI * r * r; }

private:
	const double r;
	const string name;
};

shared_ptr<Figure> CreateFigure(istringstream& is) {
	string figure_name;
	is >> figure_name;
	if (figure_name == "RECT") {
		double width, height;
		is >> width >> height;
		return make_shared<Rect>(width, height, figure_name);
	}
	else if (figure_name == "TRIANGLE") {
		double a, b, c;
		is >> a >> b >> c;
		return make_shared<Triangle>(a, b, c, figure_name);
	}
	else {
		double r;
		is >> r;
		return make_shared<Circle>(r, figure_name);
	}
}

//int main() {
//	vector<shared_ptr<Figure>> figures;
//	for (string line; getline(cin, line); ) {
//		istringstream is(line);
//
//		string command;
//		is >> command;
//		if (command == "ADD") {
//			is >> ws;
//			figures.push_back(CreateFigure(is));
//		}
//		else if (command == "PRINT") {
//			for (const auto& current_figure : figures) {
//				cout << fixed << setprecision(3)
//					<< current_figure->Name() << " "
//					<< current_figure->Perimeter() << " "
//					<< current_figure->Area() << endl;
//			}
//		}
//	}
//	return 0;
//}