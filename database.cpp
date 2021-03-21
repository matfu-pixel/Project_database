#include "database.h"

Database::Database() = default;

void Database::Add(const Date d, const string e) {
	bool ok = Set[d].count(e);
	if (!ok) {
		S[d].push_back({d, e});
		Set[d].insert(e);
		help.insert(d);
	}
}

void Database::Print(ostream& out) const {
    for (const auto& it : S) {
        for (auto& s : it.second) {
            out << it.first << " " << s.second << endl;
        }
    }
}

int Database::RemoveIf(const function<bool(const Date& date, const string& event)> f) {
    int cnt = 0;
    vector<Date> T;
    for (auto &it : S) {
    	if (it.second.empty()) {
    		T.push_back(it.first);
    		continue;
    	}
        Date d = it.first;
        vector<string> v;
        for (auto el : it.second) {
            v.push_back(el.second);
        }
        auto last = stable_partition(v.begin(), v.end(), [f, d](string s) {return !f(d, s);});
        cnt += (v.end() - last);
        vector<pair<Date, string>> tmp;
        for (int i = (last - v.begin()); i < (int)v.size(); ++i) {
        	Set[d].erase(v[i]);
        }
        for (int i = 0; i < (last - v.begin()); ++i) {
            tmp.push_back({d, v[i]});
        }
        it.second = tmp;
        if (it.second.empty()) {
        	T.push_back(it.first);
        	help.erase(it.first);
        }
    }

    for (auto it : T) {
    	S.erase(it);
    	Set.erase(it);
    }

    return cnt;
}

vector<pair<const Date, const string>> Database::FindIf(const function<bool(const Date& date, const string& event)> f) const {
    vector<pair<const Date, const string>> tmp;
    for (const auto it : S) {
        for (auto el : it.second) {
            if (f(el.first, el.second)) {
                tmp.push_back(el);
            }
        }
    }
    return tmp;
}

string Database::Last(Date d) const {
	if (help.empty()) {
		return "No entries";
	}
	auto it = help.upper_bound(d);
	if (it == help.begin()) {
		return "No entries";
	}
	it--;

	string s = S.at(*it).back().second;
	stringstream ss;
	pair<Date, string> res = {*it, s};
	ss << res.first << " " << res.second;
	return ss.str();
}
