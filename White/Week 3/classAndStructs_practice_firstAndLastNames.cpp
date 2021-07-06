#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

string GetHistoryOfNames(map<int, string> year_to_name, int year) {
    vector<string> result;
    vector<int> years;
    string preValue, history("");
    for (const auto& name : year_to_name) {
        if (name.first > year) break;  
        years.insert(years.begin(), name.first);
    }
    int c(0);
    for (const auto& y :years) {
        if ( preValue.compare(year_to_name[y])!=0) {
            switch (c) {
            case 0: history += year_to_name[y]; break;
            case 1: history += " (" + year_to_name[y]; break;
            default: history += ", " + year_to_name[y]; break;
            }
            //result.push_back(rit->second);
            preValue = year_to_name[y];
            c++;
        }
    }
    if (c > 1) history += ")";
    return history;
}

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        if (year < year_of_birth) return;
        year_to_first_name[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        if (year < year_of_birth) return;
        year_to_last_name[year] = last_name;
    }
    Person(const string& first_name, const string& last_name, const int& year) {
        year_of_birth = year;
        year_to_first_name[year] = first_name;
        year_to_last_name[year] = last_name;        
    }
    //trouble 
    string GetFullName(int year) const {
        if (year < year_of_birth) return "No person";
        string temp_first_name("null"), temp_last_name("null");
        for (const auto& f_n : year_to_first_name) {
            if (f_n.first > year) break;
            temp_first_name = f_n.second;
        }
        for (const auto& l_n : year_to_last_name) {
            if (l_n.first > year) break;
            temp_last_name = l_n.second;
        }     
        if (temp_first_name=="null" && temp_last_name == "null") return "Incognito";
        if (temp_last_name == "null" && temp_first_name != "null") return (temp_first_name + " with unknown last name");
        if (temp_first_name == "null" && temp_last_name != "null") return (temp_last_name + " with unknown first name");
        return (temp_first_name + " " + temp_last_name);
    }
    string GetFullNameWithHistory(int year) const {
        if (year < year_of_birth) return "No person";
        string f_n, l_n;
        f_n = GetHistoryOfNames(year_to_first_name, year);
        l_n = GetHistoryOfNames(year_to_last_name, year);
        if (f_n.empty() && l_n.empty()) return "Incognito";
        if (l_n.empty() && !f_n.empty()) return (f_n + " with unknown last name");
        if (f_n.empty() && !l_n.empty()) return (l_n + " with unknown first name");
        return f_n + " " + l_n;
    }
private:
    map<int, string> year_to_first_name;
    map<int, string> year_to_last_name;
    int year_of_birth;
};
int amain() {
    Person person("Polina", "Sergeeva", 1960);
    for (int year : {1959, 1960}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1965, "Appolinaria");
    person.ChangeLastName(1967, "Ivanova");
    for (int year : {1965, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    return 0;
}