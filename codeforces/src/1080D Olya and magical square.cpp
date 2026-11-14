//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
对每个候选 i：

p = n - i
下界 l = Σ_{j=1..p} (2^j - 1) = (2^{p+1} - 2) - p（即 2^{p+1} - p - 2）——必须 l <= k。
上界 r = pw[n] - ((2^{p+1}-1)·pw[i])——必须 k <= r。
满足 l <= k <= r 时返回 i。
本质是在区间 [l, r] 内找满足条件的最小可行 i，用来回答"能不能、以及在哪一步"。
当 n > 31，直接输出 YES n-1（跳过
c
h
e
c
k
check）——很可能是为了避免位运算 1ll<<p 溢出（p 接近 64 或更大）或数值边界问题。
n <= 31 时调用 check，返回 -1 输出 NO，否则输出 YES ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
#define ll long long
using namespace std;

constexpr int N = 35;

ll pw[N];
int check(int n, ll k) {
    for (int i = 0; i < n; ++i) {
        int p = n-i; ll l = 0;
        rep(j,p) l += (1ll<<j)-1;
        if (l > k) continue;
        ll r = pw[n] - ((1ll<<(p+1))-1)*pw[i];
        if (r < k) continue;
        return i;
    }
    return -1;
}

int T;
int main() {
    fast;
    rep(i,32) pw[i] = 4ll*pw[i-1]+1;
    for (cin >> T; T--; ) {
        int n; ll k; cin >> n >> k;
        if (n > 31) cout << "YES " << n-1 << '\n';
        else {
            int ans = check(n, k);
            if (ans < 0) cout << "NO\n"; else cout << "YES " << ans << '\n';
        }
    }
    return 0;
}