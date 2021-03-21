#pragma once

#include <set>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <map>
#include "date.h"
using namespace std;

class Database {
public:
    Database();
    void Add(const Date d, const string e);
    void Print(ostream& out) const;
    int RemoveIf(const function<bool(const Date& date, const string& event)> f);
    vector<pair<const Date, const string>> FindIf(const function<bool(const Date& date, const string& event)> f) const;
    string Last(Date d) const;
private:
    map<Date, vector<pair<Date, string>>> S;
    map<Date, set<string>> Set;
    set<Date> help;
};
