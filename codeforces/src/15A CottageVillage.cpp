//
// Created by Psy.C on 2025/9/16.
//

#include <ios>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, t; cin >> n >> t;
    vector<pair<double, double>> houses(n);
    for (int i = 0; i < n; ++i) {
        int x, a; cin >> x >> a;
        houses[i] = {x - a / 2.0, x + a / 2.0};
    }

    set<double> pos;
    for (int i = 0; i < n; ++i) {
        double left_edge = houses[i].first;
        double right_edge = houses[i].second;
        pos.insert(left_edge - t / 2.0);
        pos.insert(right_edge + t / 2.0);
    }

    int count = 0;
    for (double p : pos) {
        double new_left = p - t / 2.0;
        double new_right = p + t / 2.0;
        bool no_overlap = true;
        bool touches = false;

        for (int i = 0; i < n; ++i) {
            double l = houses[i].first;
            double r = houses[i].second;

            if (new_left < r && new_right > l) {
                no_overlap = false;
                break;
            }
            if (new_right == l || new_left == r) touches = true;
        }
        if (no_overlap && touches) count++;
    }

    cout << count << endl;

    return 0;
}