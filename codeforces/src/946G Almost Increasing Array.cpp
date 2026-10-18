//
// Created by Psy.C on 2026/10/18.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define low_bit(x) (x&(-x))
using namespace std;

constexpr int N = 1e6+5;

int cnt;
struct node {
    int c[N];
    int find(int p) {
        int res = 0;
        while (p) {
            res = max(res, c[p]);
            p -= low_bit(p);
        }
        return res;
    }
    void add(int p, int x) {
        while (p <= cnt) {
            c[p] = max(c[p], x);
            p += low_bit(p);
        }
    }
} tr[3];

int n, a[N], ls[N<<1], b[N], f[N][2], mx;
int main() {
    fast;
    cin >> n;
    rep(i,1,n) {
        cin >> a[i]; a[i] -= i;
        ls[++cnt] = a[i], ls[++cnt] = a[i] + 1;
    }
    sort(ls+1, ls+cnt+1);
    int tot = unique(ls+1, ls+cnt+1)-ls-1;
    rep(i,1,n) b[i] = lower_bound(ls+1, ls+cnt+1, a[i]) - ls;
    rep(i,1,n) {
        f[i][0] = tr[0].find(b[i]) + 1;
        f[i][1] = 1 + max(tr[1].find(b[i]), tr[2].find(b[i]+1));
        mx = max(mx, max(f[i][1], f[i][0]));
        tr[0].add(b[i], f[i][0]), tr[1].add(b[i], f[i][1]);
        if (i != 1) tr[2].add(b[i-1], f[i-1][0]);
    }
    cout << max(0, n-mx-1);
    return 0;
}