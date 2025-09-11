//
// Created by Psy.C on 2025/9/11.
//

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int d, sumTime;
    cin >> d >> sumTime;

    vector<int> minTime(d);
    vector<int> maxTime(d);

    int minTotal = 0;
    int maxTotal = 0;

    for (int i = 0; i < d; i++) {
        cin >> minTime[i] >> maxTime[i];
        minTotal += minTime[i];
        maxTotal += maxTime[i];
    }

    if (sumTime < minTotal || sumTime > maxTotal) {
        cout << "NO" << endl;
        return 0;
    }

    vector<int> schedule(d);
    int remaining = sumTime - minTotal;

    for (int i = 0; i < d; i++) {
        schedule[i] = minTime[i];
    }

    for (int i = 0; i < d && remaining > 0; i++) {
        int canAdd = min(remaining, maxTime[i] - schedule[i]);
        schedule[i] += canAdd;
        remaining -= canAdd;
    }

    cout << "YES" << endl;

    for (int i= 0; i < d; i++) {
        cout << schedule[i];
        if (i < d - 1) cout << " ";
    }
    cout << endl;

    return 0;
}