//
// Created by Psy.C on 2025/9/12.
//


#include <iostream>
#include <string>

using namespace std;

int main() {
    string trip, first, second;
    getline(cin, trip);
    getline(cin, first);
    getline(cin, second);

    long posF1 = trip.find(first);
    long posF2 = trip.find(second);
    while (posF2 != string::npos) {
        long test = trip.find(second, posF2 + 1);
        if (test != string::npos) posF2 = test;
        else break;
    }
    bool forward = (posF1 != string::npos) && (posF2 != string::npos) &&
        (posF1 + first.size() - 1 < posF2);
    string retTrip = trip;
    for (long p = 0; p < trip.size(); p++) {
        retTrip[p] = trip[trip.size() - 1 - p];
    }
    long posB1 = retTrip.find(first);
    long posB2 = retTrip.find(second);
    while (posB2 != string::npos) {
        long test = retTrip.find(second, posB2 + 1);
        if (test != string::npos) posB2 = test;
        else break;
    }
    bool backward = (posB1 != string::npos) && (posB2 != string::npos) &&
        (posB1 + first.size() - 1 < posB2);

    if (forward && backward) puts("both");
    else if (forward && !backward) puts("forward");
    else if (!forward && backward) puts("backward");
    else puts("fantasy");
    return 0;
}