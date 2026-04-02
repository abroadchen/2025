//
// Created by Psy.C on 2026/4/1.
//

#include <ranges>
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;
map<string, set<string>> h2u;
string url;
map<int, vector<string>> cnt;
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> url;
        string a = url.substr(7);
        auto p = a.find('/');
        string hn = p != string::npos ? a.substr(0, p) : a;
        h2u[hn].insert(url);
    }
    for (auto& [host, urls] : h2u) {
        int x = urls.size();
        cnt[x].push_back(host);
    }
    vector<pair<int, vector<string>>> res;
    for (auto& [count, hosts] : cnt) {
        if (hosts.size() > 1) {
            vector<string> t;
            for (auto& h : hosts) t.push_back("http://" + h);
            res.emplace_back(count, t);
        }
    }
    ranges::sort(res);
    cout << res.size() << '\n';
    for (auto &hosts: res | views::values) {
        for (int i = 0; i < hosts.size(); ++i) {
            if (i > 0) cout << ' ';
            cout << hosts[i];
        }
        cout << '\n';
    }
    return 0;
}