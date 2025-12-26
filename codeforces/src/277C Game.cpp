//
// Created by Psy.C on 2025/12/26.
//

#include <iostream>
#include <map>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

struct node {
    int l, r;
    bool operator<(const node rhs) const {
        return l != rhs.l ? l < rhs.l : r < rhs.r;
    }
};

int main() {
    fast;
    int n, m, k; cin >> n >> m >> k;
    map<int, vector<pair<int, int>>> h, v;
    for (int i = 0, x1, y1, x2, y2; i < k; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 == x2) {
            if (y1 > y2) swap(y1, y2);
            v[x1].emplace_back(y1, y2);
        } else {
            if (x1 > x2) swap(x1, x2);
            h[y1].emplace_back(x1, x2);
        }
    }
    for (auto& p : h) {
        sort(p.second.begin(), p.second.end());
        vector<pair<int, int>> mg;
        for (auto seg : p.second) {
            if (mg.empty() || mg.back().second < seg.first) {
                mg.push_back(seg);
            } else {
                mg.back().second = max(mg.back().second, seg.second);
            }
        }
        p.second = mg;
    }
    for (auto& p : v) {
        sort(p.second.begin(), p.second.end());
        vector<pair<int, int>> mg;
        for (auto seg : p.second) {
            if (mg.empty() || mg.back().second < seg.first) {
                mg.push_back(seg);
            } else {
                mg.back().second = max(mg.back().second, seg.second);
            }
        }
        p.second = mg;
    }
    int ans = 0;
    for (auto& p : h) {
        int used = 0;
        for (const auto seg : p.second) {
            used += seg.second - seg.first;
        }
        const int x = n - used;
        ans ^= x;
    }
    for (auto& p : v) {
        int used = 0;
        for (const auto seg : p.second) {
            used += seg.second - seg.first;
        }
        const int x = m - used;
        ans ^= x;
    }
    const int r = m - static_cast<int>(h.size()),
    c = n - static_cast<int>(v.size());
    ans ^= r * n;
    ans ^= c * m;
    if (ans == 0) cout << "SECOND\n";
    else {
        cout << "FIRST\n";
        bool f = false;
        for (auto& p : h) {
            int used = 0;
            for (auto seg : p.second) {
                used += seg.second - seg.first;
            }
            int x = n - used, t = x ^ ans;
            if (t < x) {
                vector<pair<int, int>> sgs = p.second;
                sgs.emplace_back(n, n);
                int pos = 0, tot = 0;
                for (auto seg : sgs) {
                    if (pos < seg.first) {
                        int gap = seg.first - pos;
                        if (tot + gap >= t) {
                            int st = pos + (t - tot);
                            cout << st << ' ' << p.first << ' ' <<
                                st + t << ' ' << p.first << '\n';
                            f = true;
                            break;
                        }
                        tot += gap;
                    }
                    pos = seg.second;
                }
            }
            if (f) break;
        }
        if (!f) {
            for (auto& p : v) {
                int used = 0;
                for (auto seg : p.second) {
                    used += seg.second - seg.first;
                }
                int x = m - used, t = x ^ ans;
                if (t < x) {
                    vector<pair<int, int>> sgs = p.second;
                    sgs.emplace_back(m, m);
                    int pos = 0, tot = 0;
                    for (auto seg : sgs) {
                        if (pos < seg.first) {
                            int gap = seg.first - pos;
                            if (tot + gap >= t) {
                                int st = pos + (t - tot);
                                cout << p.first << ' ' << st << ' ' <<
                                    p.first << ' ' << st + t << '\n';
                                f = true;
                                break;
                            }
                            tot += gap;
                        }
                        pos = seg.second;
                    }
                }
                if (f) break;
            }
        }
        if (!f) {
            for (int i = 0; i < m && !f; ++i) {
                if (h.find(i) == h.end()) {
                    int t = n ^ (ans ^ n);
                    if (t <= n) {
                        cout << 0 << ' ' << i << ' ' << t << ' ' << i << '\n';
                        f = true;
                    }
                }
            }
        }
        if (!f) {
            for (int i = 0; i < n && !f; ++i) {
                if (v.find(i) == v.end()) {
                    int t = m ^ (ans ^ m);
                    if (t <= m) {
                        cout << i << ' ' << 0 << ' ' << i << ' ' << t << '\n';
                        f = true;
                    }
                }
            }
        }
    }
    return 0;
}