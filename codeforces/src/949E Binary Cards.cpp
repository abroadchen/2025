//
// Created by Psy.C on 2026/10/18.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define sz(x) ((int)(x).size())
using namespace std;

constexpr int N = 1e5+5;

int n, a[N], b[20][N], r[20];
vector<int> solve(int d) {
    if (d >= 20) return vector{0};
    bool flg = true;
    rep(i,1,n) if (a[i]&1) flg = false;
    if (flg) {
        rep(i,1,n) a[i] >>= 1;
        return solve(d+1);
    }
    rep(i,1,n) b[d][i] = a[i];
    r[d] = n;
    rep(i,1,n) {
        if (a[i]&1) a[i]++;
        a[i] >>= 1;
    }
    n = unique(a+1, a+n+1) - a - 1;
    vector<int> ans = solve(d+1); n = r[d];
    rep(i,1,n) a[i] = b[d][i];
    rep(i,1,n) {
        if (a[i]&1) a[i]--;
        a[i] >>= 1;
    }
    n = unique(a+1, a+n+1) - a - 1;
    vector<int> ans2 = solve(d+1); n = r[d];
    rep(i,1,n) a[i] = b[d][i];
    ans.push_back(-(1<<d)); ans2.push_back(1<<d);
    if (sz(ans) > sz(ans2)) return ans2;
    return ans;
}


int main() {
    fast;
    cin >> n;
    rep(i,1,n) cin >> a[i];
    sort(a+1, a+n+1);
    vector<int> ans = solve(0);
    cout << sz(ans) << '\n';
    for (int i : ans) cout << i << ' ';
    cout << '\n';
    return 0;
}