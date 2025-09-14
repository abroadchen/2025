//
// Created by Psy.C on 2025/9/13.
//

#include <ios>
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, vb, vs; cin >> n >> vb >> vs;
    vector<int> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];

    int xu, yu; cin >> xu >> yu;
    int best_stop = 1;
    double min_time = numeric_limits<double>::max();
    double min_distance = numeric_limits<double>::max();

    for (int i = 1; i < n; ++i) {
        double bus_time = (double)x[i] / vb;
        double distance = sqrt(pow(x[i] - xu, 2) + pow(0 - yu, 2));
        double run_time = distance / vs;
        double total_time = bus_time + run_time;

        if (total_time < min_time || (total_time == min_time && distance < min_distance)) {
            min_time = total_time;
            min_distance = distance;
            best_stop = i + 1;
        }
    }

    cout << best_stop << endl;
    return 0;
}