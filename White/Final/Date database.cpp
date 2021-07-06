//
//
//See better impl in Yellow belt
//
//
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <set>
#include <exception>
#include <sstream>

using namespace std;


class Date {
public:
    Date() {
        year = 0;
        day = 0;
        month = 0;
    }
    Date(const int& new_year, const int& new_month, const int& new_day) {
        year = new_year;
        if (new_month < 1 || new_month>12) { 
            throw runtime_error("Month value is invalid: " + to_string(new_month));
        }
        month = new_month;
        if (new_day < 1 || new_day>31) {
            throw runtime_error("Day value is invalid: " + to_string(new_day));
        }
        day = new_day;
    }
    int GetYear() const {
        return year;
    }

    int GetMonth() const {
        return month;
    }

    int GetDay() const {
        return day;
    }
private:
    int year;
    int month;
    int day;
};

void PrintDate(const Date& d) {
    cout << setw(4) << setfill('0') << d.GetYear() << "-" << setw(2) << setfill('0')
        << d.GetMonth() << "-" << setw(2) << setfill('0') << d.GetDay() << " ";
}

bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() < rhs.GetDay();
        }
        return lhs.GetMonth() < rhs.GetMonth();
    }
    return lhs.GetYear() < rhs.GetYear();
}

bool operator==(const Date& lhs, const Date& rhs) {
    return lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth() && lhs.GetDay() == rhs.GetDay();
}

//ÍÎÐÌÀËÜÍÀ ÐÅÀË²ÇÀÖ²ß ÎÏÅÐÀÒÎÐÀ(ÀÁÎ ßÊ ÏÅÐÅÂ²ÐÈÒÈ ÔÎÐÌÀÒ ÄÀÒÈ) ???
/*istream& operator>>(istream& input, Date& d) {
    int day(0), month(0), year(0);
    char div1;
    char div2;
    if (input && input >> year && (input >> div1 && div1 == '-') && input >> month && (input >> div2 && div2 == '-') 
        && input >> year &&(input.peek()==input.eof()|| input.peek() == ' ')) {
        try {
            d = { year,month,day };
        }
        catch (runtime_error& ex) {
            cout << ex.what() << endl;
        }
    }
    else {
        stringstream ss;
        ss << "Wrong date format: " << endl;
        throw runtime_error(ss.str());
    }
    return input;
}*/

istream& operator>>(istream& stream, Date& date)
{
    string line;
    istringstream date_stream;

    stream >> line;

    date_stream.str(line);

    int year, month, day;

    date_stream >> year;
    if (date_stream.peek() != '-')
    {
        throw runtime_error("Wrong date format: " + line);
    }
    else
    {
        date_stream.ignore(1);
    }
    date_stream >> month;
    if (date_stream.peek() != '-')
    {
        throw runtime_error("Wrong date format: " + line);
    }
    else
    {
        date_stream.ignore(1);
    }

    set<char> ch_vec = { '-', '+', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

    if (ch_vec.count(char(date_stream.peek())) == 0){  
        throw runtime_error("Wrong date format: " + line);
    }
    else{    
        date_stream >> day;
    }

    if (date_stream.peek() != EOF)
    {
        throw runtime_error("Wrong date format: " + line);
    }
    else
    {
        date = Date(year, month, day);
    }
    return stream;
}


class Database {
public:
    void AddEvent(const Date& date, const string& event) {
        data[date].insert(event);
    }
    bool DeleteEvent(const Date& date, const string& event) {
        if ((data.count(date) == 0)||(data.at(date).count(event)==0)) return false;
        data[date].erase(event);
        return true;
    }
    int DeleteDate(const Date& date) {
        //
        int q = data[date].size();
        data.erase(date);
        return q;
    }
    void Find(const Date& date) const {
        if (data.count(date) == 0) return;
        for (const auto& event : data.at(date)) {
            cout << event << endl;
        }
    }

    void Print() const {
        for (const auto& d : data) {
            Date temp = d.first;
            for (const auto& event : d.second) {
                PrintDate(temp);
                cout << event << endl;
            }
        }
    }
private:
    map<Date, set<string>> data;
};

// ÍÎÐÌÀËÜÍÀ ÐÅÀË²ÇÀÖ²ß input ???
/*int main()
{
    Database db;

    string line;

    while (getline(cin, line))
    {
        if (line == "") continue;
        string command;
        stringstream input(line);
        Date temp_date;
        input >> command;
        if (command == "Add") {
            try { input >> temp_date; }
            catch (exception& ex) { 
                cout << ex.what() << endl;
                break;
            }
            string temp_string;
            input >> temp_string;
            db.AddEvent(temp_date, temp_string);
        }
        else if (command == "Print") {
            db.Print();
        }
        else if (command == "Find") {
            try { input >> temp_date; }
            catch (exception& ex) {
                cout << ex.what() << endl;
                break;
            }
            db.Find(temp_date);
        }
        else if (command == "Del") {
            try { input >> temp_date; }
            catch (exception& ex) {
                cout << ex.what() << endl;
                break;
            }
            if (input.eof()) { 
                int n = db.DeleteDate(temp_date);
                cout << "Deleted " << n << " events" << endl;
            }
            else {
                string temp_event;
                input >> temp_event;
                if (db.DeleteEvent(temp_date, temp_event)) cout << "Deleted successfully" << endl;
                else cout << "Event not found" << endl;
            }
        }
        else {
            cout << "Unknown command : " << command << endl;
            break;
        }
    }
}*/