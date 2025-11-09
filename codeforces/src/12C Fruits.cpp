//
// Created by Psy.C on 2025/9/15.
//

#include <ios>
#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m; cin >> n >> m;
    vector<int> prices(n);
    for (int i = 0; i < n; i++) cin >> prices[i];

    map<string, int> fruit_count;
    for (int i = 0; i < m; ++i) {
        string fruit; cin >> fruit;
        fruit_count[fruit]++;
    }
    vector<int> counts;
    for (auto& pair : fruit_count) {
        counts.push_back(pair.second);
    }

    sort(counts.begin(), counts.end(), greater<int>());
    sort(prices.begin(), prices.end());

    int min_cost = 0, max_cost = 0;
    for (int i = 0; i < counts.size(); ++i) {
        min_cost += counts[i] * prices[i];
        max_cost += counts[i] * prices[n - 1 - i];
    }
    cout << min_cost << " " << max_cost << endl;
    return 0;
}