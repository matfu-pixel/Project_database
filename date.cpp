#include "date.h"

Date::Date(int y_, int m_, int d_) : y(y_), m(m_), d(d_) {
}

ostream& operator<<(ostream& out, const Date x) {
    out << setw(4) << setfill('0') << x.y;
    out << '-';
    out << setw(2) << setfill('0') << x.m;
    out << '-';
    out << setw(2) << setfill('0') << x.d;
    return out;
}

bool operator<(const Date a, const Date b) {
    if (a.y < b.y) {
        return true;
    }
    else if (a.y == b.y) {
        if (a.m < b.m) {
            return true;
        }
        else if (a.m == b.m) {
            if (a.d < b.d) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool operator==(const Date a, const Date b) {
    if (a.y == b.y && a.m == b.m && a.d == b.d) {
        return true;
    }
    else {
        return false;
    }
}
bool operator!=(const Date a, const Date b) {
    if (a.y == b.y && a.m == b.m && a.d == b.d) {
        return false;
    } else {
        return true;
    }
}

Date ParseDate(istream& is) {
    string year, month, day;
    getline(is, year, '-');
    getline(is, month, '-');
    getline(is, day, ' ');
    int y = stoi(year), m = stoi(month), d = stoi(day);
    return Date(y, m, d);
}
