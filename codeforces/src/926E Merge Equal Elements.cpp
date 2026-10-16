//
// Created by Psy.C on 2026/10/15.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 2e5+5;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

stack<int> st;
vector<int> vc;
signed main() {
    fast;
    int n = rd();
    for (int i = 1; i <= n; ++i) {
        int x = rd();
        while (!st.empty() && x == st.top()) { x++; st.pop(); }
        st.push(x);
    }
    while (!st.empty()) {
        int v = st.top(); st.pop();
        vc.push_back(v);
    }
    ranges::reverse(vc);
    cout << vc.size() << '\n';
    for (auto v : vc) cout << v << ' ';
    return 0;
}