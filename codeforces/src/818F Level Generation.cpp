//
// Created by Psy.C on 2026/9/22.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

int n;
int f(int x) {
    int t1;
    if (x&1) t1=x*((x-1)>>1);
    else t1=(x>>1)*(x-1);
    int t2 = n-x;
    return min(t1, t2) + (n-x);
}

int rd() {
    int x; cin >> x;
    return x;
}

signed main() {
    fast;
    int q = rd();
    while (q--) {
        n = rd();
        int l = 0, r = n;
        if (n == 1) { cout << 0 << '\n'; continue; }
        while (l + 1 < r) {
            int lm = (l+r)>>1, rm = (lm+r)>>1;
            if (f(lm) > f(rm)) r = rm;
            else l = lm;
        }
        cout << f(l) << '\n';
    }
    return 0;
}