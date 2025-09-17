//
// Created by Psy.C on 2025/9/16.
//

#include <ios>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n; int m; cin>>n>>m;

    vector<pair<long long, long long>> containers(m);
    for (int i = 0; i < m; ++i) cin >> containers[i].first >> containers[i].second;

    sort(containers.begin(), containers.end(), [](const pair<long long, long long>& a, const pair<long long, long long>& b) {
        return a.second > b.second;
    });

    long long total_matches = 0, boxes_taken = 0;
    for (int i = 0; i < m && boxes_taken < n; ++i) {
        long long boxes_available = containers[i].first;
        long long matches_per_box = containers[i].second;

        long long boxes_to_take = min(n - boxes_taken, boxes_available);
        total_matches += boxes_to_take * matches_per_box;
        boxes_taken += boxes_to_take;
    }

    cout << total_matches << endl;

    return 0;
}