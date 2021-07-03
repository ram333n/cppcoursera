#include "date.h"


Date::Date(const int& new_year, const int& new_month, const int& new_day) {
    year = new_year;
    if (new_month > 12 || new_month < 1) {
        throw std::logic_error("Month value is invalid: " + std::to_string(new_month));
    }
    month = new_month;
    if (new_day > 31 || new_day < 1) {
        throw std::logic_error("Day value is invalid: " + std::to_string(new_day));
    }
    day = new_day;
}

int Date::GetDay() const {
    return Date::day;
}

int Date::GetMonth() const {
    return Date::month;
}

int Date::GetYear() const {
    return Date::year;
}

Date ParseDate(std::istream& is) {
    bool is_ok = true;

    int t_year;
    is_ok = is_ok && (is >> t_year);
    is_ok = is_ok && (is.peek() == '-');
    is.ignore(1);

    int t_month;
    is_ok = is_ok && (is >> t_month);
    is_ok = is_ok && (is.peek() == '-');
    is.ignore(1);

    int t_day;
    is_ok = is_ok && (is >> t_day);

    if (!is_ok) {
        throw std::logic_error("Wrong date format");
    }

    return Date(t_year, t_month, t_day);
}

std::ostream& operator<<(std::ostream& os, const Date& d) {
    os << std::setw(4) << std::setfill('0') << d.GetYear() << "-"
        << std::setw(2) << std::setfill('0') << d.GetMonth() << "-"
        << std::setw(2) << std::setfill('0') << d.GetDay();

    return os;
}

bool operator<(const Date& lhs, const Date& rhs) {
    return std::vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
        std::vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator>(const Date& lhs, const Date& rhs) {
    return std::vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} >
        std::vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator>=(const Date& lhs, const Date& rhs) {
    return !(lhs < rhs);
}

bool operator<=(const Date& lhs, const Date& rhs) {
    return !(lhs > rhs);
}

bool operator==(const Date& lhs, const Date& rhs) {
    return std::vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} ==
        std::vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator!=(const Date& lhs, const Date& rhs) {
    return !(lhs == rhs);
}