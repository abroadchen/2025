//
// Created by Psy.C on 2025/9/17.
//

#include <ios>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int INF = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    vector<int> q(n + 1);
    for (int i = 1; i <= n; ++i) cin >> q[i];

    int m; cin >> m;
    vector<tuple<int, int, int>> edges(m);
    for (int i = 0; i < m; ++i) {
        int a, b, c; cin >> a >> b >> c;
        edges[i] = {a, b, c};
    }

    vector<int> min_cost(n + 1, INF); min_cost[0] = 0;
    for (auto& [a, b, c] : edges)
        min_cost[b] = min(min_cost[b], c);

    int root_count = 0, total_cost = 0;
    for (int i = 1; i <= n; ++i) {
        if (min_cost[i] == INF) root_count++;
        else total_cost += min_cost[i];
    }

    if (root_count != 1) cout << -1 << endl;
    else cout << total_cost << endl;
    
    return 0;
}