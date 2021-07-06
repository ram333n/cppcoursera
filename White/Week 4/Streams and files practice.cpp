#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

struct Student {
    string name;
    string surname;
    int day;
    int month;
    int year;
};

int main()
{
    int SizeOfVector, t;
    cin >> SizeOfVector;
    vector<Student> students(SizeOfVector);
    for (Student& s : students) {
        cin >> s.name >> s.surname >> s.day >> s.month >> s.year;
    }
    cin >> t;
    for (int i = 0; i < t; i++) {
        string command;
        int n;
        cin >> command >> n;
        if (n<1 || n>SizeOfVector){
            cout << "bad request" << endl;
            continue;
        }
        else {
            if (command == "name") cout << students[n - 1].name << " " << students[n - 1].surname << endl;
            else if (command == "date") cout << students[n - 1].day << "." << students[n - 1].month << "." << students[n - 1].year << endl;
            else cout << "bad request" << endl;
        }
    }   
}
