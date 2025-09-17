//
// Created by Psy.C on 2025/9/16.
//

#include <ios>
#include <iostream>
#include <string>
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n; cin.ignore();
    int days = 1, last_time = -1, same_time_count = 0;

    for (int i = 0; i < n; ++i) {
        string line;
        getline(cin, line);

        int hour, minute;
        string period;
        hour = (line[1] - '0') * 10 + (line[2] - '0');
        minute = (line[4] - '0') * 10 + (line[5] - '0');
        period = line.substr(7, 4);

        int current_time;
        if (period == "a.m.") {
            if (hour == 12) hour = 0;
            current_time = hour * 60 + minute;
        } else {
            if (hour != 12) hour += 12;
            current_time = hour * 60 + minute;
        }

        if (last_time == current_time) {
            same_time_count++;
            if (same_time_count > 10) {
                days++;
                same_time_count = 1;
            }
        } else {
            if (current_time < last_time) days++;
            same_time_count = 1;
        }
        last_time = current_time;
    }

    cout << days << endl;
    return 0;
}