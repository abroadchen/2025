//
// Created by Psy.C on 2025/12/21.
//

#include <iostream>
#include <queue>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


bool tps(const int n, const vector<pair<int,int>>& e, vector<int>& res) {
    vector<vector<int>> adj(n + 1);
    vector<int> ind(n + 1, 0);
    for (auto& i : e) {
        adj[i.first].push_back(i.second);
        ind[i.second]++;
    }
    queue<int> q;
    for (int i = 1; i <= n; ++i) if (ind[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        res.push_back(u);
        for (int v : adj[u]) {
            ind[v]--;
            if (ind[v] == 0) q.push(v);
        }
    }
    return res.size() == n;
}


int main() {
    fast;
    int n, m; cin >> n >> m;
    vector<pair<int, int>> lr, lt, lb, tr, tb, rb;
    for (int i = 0; i < n + m; ++i) {
        string s1, s2; int p1, p2; cin >> s1 >> s2 >> p1 >> p2;
        if (s1 > s2) { swap(s1, s2), swap(p1, p2); }
        if (s1 == "L" && s2 == "R") lr.emplace_back(p1, p2);
        else if (s1 == "L" && s2 == "T") lt.emplace_back(p1, p2);
        else if (s1 == "L" && s2 == "B") lb.emplace_back(p1, p2);
        else if (s1 == "T" && s2 == "R") tr.emplace_back(p1, p2);
        else if (s1 == "T" && s2 == "B") tb.emplace_back(p1, p2);
        else if (s1 == "R" && s2 == "B") rb.emplace_back(p1, p2);
    }
    vector<pair<int, int>> r, c;
    for (int i = 0; i < lr.size(); ++i) for (int j = i + 1; j < lr.size(); ++j) {
        int r1 = lr[i].first, c1 = lr[i].second, r2 = lr[j].first, c2 = lr[j].second;
        if (r1 < r2 && c1 > c2) { cout << "No solution\n"; return 0; }
        if (r1 > r2 && c1 < c2) { cout << "No solution\n"; return 0; }
        if (r1 < r2) r.emplace_back(r1, r2);
        else if (r1 > r2) r.emplace_back(r2, r1);
        if (c1 < c2) c.emplace_back(c1, c2);
        else if (c1 > c2) c.emplace_back(c2, c1);
    }
    for (int i = 0; i < tb.size(); ++i) for (int j = i + 1; j < tb.size(); ++j) {
        int c1 = tb[i].first, c2 = tb[j].first, c3 = tb[i].second, c4 = tb[j].second;
        if (c1 < c2 && c3 > c4) { cout << "No solution\n"; return 0; }
        if (c1 > c2 && c3 < c4) { cout << "No solution\n"; return 0; }
        if (c1 < c2) c.emplace_back(c1, c2);
        else if (c1 > c2) c.emplace_back(c2, c1);
        if (c3 < c4) c.emplace_back(c3, c4);
        else if (c3 > c4) c.emplace_back(c4, c3);
    }
    for (auto& p : lt) for (auto& q : tr) {
        if (p.second == q.first) r.emplace_back(p.first, q.second);
    }
    vector<int> rr, cr;
    if (!tps(n, r, rr) || !tps(m, c, cr)) { cout << "No solution\n"; return 0; }
    for (int i = 0; i < n; ++i) cout << rr[i] << " \n"[i == n - 1];
    for (int i = 0; i < m; ++i) cout << cr[i] << " \n"[i == m - 1];
    return 0;
}