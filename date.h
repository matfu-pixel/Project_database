#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <memory>
using namespace std;

class Date {
public:
    Date(int y_, int m_, int d_);
    int y, m, d;
private:
};

ostream& operator<<(ostream& out, const Date x);
bool operator<(const Date a, const Date b);
bool operator==(const Date a, const Date b);
bool operator!=(const Date a, const Date b);

Date ParseDate(istream& is);
