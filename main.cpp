#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"

#include <iostream>
#include <stdexcept>
#include <functional>

using namespace std;

string ParseEvent(istream& is) {
    bool leading_space = is.peek() == ' ';
    while (leading_space) {
        is.ignore(1);
        leading_space = is.peek() == ' ';
    }

    string s;
    getline(is, s);
    return s;
}

template <class T1, class T2>
ostream& operator<<(ostream& out, pair<T1, T2> p) {
    out << p.first << " " << p.second;
    return out;
}

int main() {
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
            } catch (invalid_argument&) {
                cout << "No entries" << endl;
            }
        }
        else if (command.empty()) {
            continue;
        }
        else {
            throw logic_error("Unknown command: " + command);
        }
    }

    return 0;
}
