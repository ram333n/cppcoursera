#pragma once

#include <stdexcept>
#include <string>
#include <iomanip>
#include <map>
#include <vector>
#include <set>


class Date {
public:
	//maybe 'const int&' can bring the problem
	Date(const int& new_year, const int& new_month, const int& new_day);

	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;

private:
	int year;
	int month;
	int day;
};

Date ParseDate(std::istream& is);

std::ostream& operator<<(std::ostream& os, const Date& d);

bool operator<(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);