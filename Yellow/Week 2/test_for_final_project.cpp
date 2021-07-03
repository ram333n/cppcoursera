#include "test"
//#include "database.h"
//#include "date.h"
//#include "condition_parser.h"
//#include "node.h"

#include <iostream>
#include <vector>

using namespace std;

/*
    database.h/cpp Ч эти файлы должны содержать объ€вление и определение класса Database;
    node.h/cpp Ч эти файлы должны содержать объ€влени€ и определени€ класса Node, а также всех его потомков (см. выше), которые представл€ют собой узлы абстрактного синтаксического дерева, формируемого функцией ParseCondition;
    condition_parser.h/cpp;
    token.h/cpp;
    main.cpp;
    другие .h- и .cpp-файлы, которые вы посчитаете нужным создать в своЄм решении.*/

string ParseEvent(istream& is) {
    is >> ws;
    string result;
    getline(is, result);
    return result;
}

void TestAll();
void TestParseEvent();

int main() {
    TestParseEvent();
    /*TestAll();

    Database db;

    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "Add") {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        }
        else if (command == "Print") {
            db.Print(cout);
        }
        else if (command == "Del") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };
            int count = db.RemoveIf(predicate);
            cout << "Removed " << count << " entries" << endl;
        }
        else if (command == "Find") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(predicate);
            for (const auto& entry : entries) {
                cout << entry << endl;
            }
            cout << "Found " << entries.size() << " entries" << endl;
        }
        else if (command == "Last") {
            try {
                cout << db.Last(ParseDate(is)) << endl;
            }
            catch (invalid_argument&) {
                cout << "No entries" << endl;
            }
        }
        else if (command.empty()) {
            continue;
        }
        else {
            throw logic_error("Unknown command: " + command);
        }
    }*/

    return 0;
}

void TestParseEvent() {
    {
        istringstream is("event");
        AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
    }
    {
        istringstream is("   sport event ");
        AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
    }
    {
        istringstream is("  first event  \n  second event");
        vector<string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));
        AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
    }
}
//
//void TestAll() {
//    TestRunner tr;
//    tr.RunTest(TestParseEvent, "TestParseEvent");
//    tr.RunTest(TestParseCondition, "TestParseCondition");
//}
