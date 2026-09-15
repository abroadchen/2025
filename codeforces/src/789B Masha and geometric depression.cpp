//
// Created by Psy.C on 2026/9/15.
//
/**
首项为 0，则整个数列全是 0（0*q=0）。
若 0 不在黑名单 → 无限多个 0 都合法 → inf。
若 0 在黑名单 → 全被屏蔽 → 0
当公比 q=0，数列变成：b, 0, 0, 0, ...。
合法项只可能是 b 和 0（反复的 0）。
如果 b 和 0 都在黑名单，或无合法首项（abs(b)>l）→ 0。
否则根据 0 是否在黑名单决定答案是 1（只剩首项）还是 inf（0 无限多个）——需保证这些数 |·|<=l
公比为 1：数列全等于 b。
b 不在黑名单且 |b|<=l → 无限多个 b → inf。
否则 → 0
公比为 -1：数列在 b 和 -b 间交替。
若 b 和 -b 都在黑名单（或首项本身超界）→ 全被屏蔽 → 0。
否则至少有一个循环项可记录 → inf（无限交替）
当 |q| >= 2 时，数列会单调发散，最终超出 |b| <= l，项数有限。
循环：只要当前 |b| <= l，若 b 不在黑名单则 ans++，然后 b *= q 进入下一项。
有限次后 |b| > l 跳出，输出 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

set<int> a;
signed main() {
    fast;
    int b, q, l, m; cin >> b >> q >> l >> m;
    for (int i = 0, t; i < m; ++i) {
        cin >> t; a.insert(t);
    }
    if (b == 0) {
        if (!a.contains(0)) cout << "inf"; else cout << 0;
        return 0;
    }
    if (q == 0) {
        if (a.contains(b) && a.contains(0) || abs(b) > l) cout << 0;
        else {
            if (a.contains(0)) cout << 1; else cout << "inf";
        }
        return 0;
    }
    if (q == 1) {
        if (!a.contains(b) && abs(b) <= l) cout << "inf";
        else cout << 0;
        return 0;
    }
    if (q == -1) {
        if (a.contains(b) && a.contains(-b) || abs(b) > l) cout << 0;
        else cout << "inf";
        return 0;
    }
    int ans = 0;
    while (abs(b) <= l) {
        if (!a.contains(b)) ans++;
        b *= q;
    }
    cout << ans;
    return 0;
}