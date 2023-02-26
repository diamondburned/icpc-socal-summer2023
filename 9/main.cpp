#include <bits/stdc++.h>

using namespace std;

struct Record {
    string time;
    double rlat;
    double rlong;
    double ralt;

    double distance(Record prev, double flat, double flong);
};

vector<Record> readAllRecords() {
    Record r;
    vector<Record> records;
    while (cin >> r.time >> r.rlat >> r.rlong >> r.ralt) {
        records.push_back(r);
    }
    return records;
}

double Record::distance(Record prev, double flat, double flong) {
    return sqrt(
            pow((this->rlat- prev.rlat)*flat, 2) +
            pow((this->rlong - prev.rlong)*flong, 2) +
            pow(this->ralt - prev.ralt, 2)
            );
}

int parseTime(string t) {
    int h = 0, m = 0, s = 0;

    string buf;
    int state = 0;
    const auto flush = [&]() {
        switch (state) {
            case 0:
                h = atoi(buf.c_str());
                break;
            case 1:
                m = atoi(buf.c_str());
                break;
            case 2:
                s = atoi(buf.c_str());
                break;
        }
    };

    for (char c : t) {
        if (c != ':') {
            buf += c;
            continue;
        }

        flush();
        state++;
        buf = "";
    }

    flush();

    return s + (m * 60) + (h * 60 * 60);
}

int main() {
	double flat;
	double flong;
	cin >> flat >> flong;

    auto records = readAllRecords();

    auto first = records[0];

    auto prev = first;
    auto prev_t = parseTime(prev.time);
    double cumdist = 0;

    for (size_t i = 1; i < records.size(); i++) {
        auto curr = records[i];
        auto curr_d = curr.distance(prev, flat, flong);
        auto curr_t = parseTime(curr.time);

        cumdist += abs(curr_d);

        auto rel_t = curr_t - prev_t;
        auto rel_alt = curr.ralt - first.ralt;

        printf("%d %.5f %.6f\n", rel_t, cumdist, rel_alt);
//		cout << rel_t << " " << setprecision(6) << cumdist << " " << setprecision(7) << rel_alt << endl;

        prev = curr;
    }
    return 0;
}
