//
// Created by Psy.C on 2026/10/27.
//

/**
真正学会的起点..
num：统计字符串里 0 的个数。
关键：如果字符串末尾是 0，在末尾补一个 1。这样保证后面统计"0 段"时，末尾那段 0 也能被正确算作一段（因为统计是用"1 前一个是 0"来数的）
全为 0（num==n）：只有一个 0 段，直接翻转这段成 1，代价 y。
全为 1（num==0）：没有 0，代价 0
cnt：统计 "10" 边界（前一位是 0、当前位是 1）的个数。这代表 0 段的个数（在末尾补 1 后，每个 0 段之后都会有一个这样的边界）。

实际上若末尾没补 1，则最后一个 0 段后没有 1，不会计数；补上 1 后所有 0 段都被计入，cnt = 0 段总数。

然后枚举：i 次"合并"(代价 i*x)，其余 (cnt-i) 次"翻转"(代价 (cnt-i)*y)，取使总和最小的方案
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; i++)
#define ll long long
using namespace std;

int n;
ll x, y;
string s;
int main() {
    fast;
    while (cin >> n >> x >> y) {
        cin >> s;
        int num = 0;
        rep(i,s.length()) if (s[i] == '0') num++;
        if (s[s.length()-1] == '0') s += '1';
        if (num == n) cout << y << '\n';
        else if (num == 0) cout << 0 << '\n';
        else {
            ll cnt = 0;
            rep(i,s.length()) if (s[i] == '0') break;
            rep(i,s.length()) if (s[i] == '1' && s[i-1] == '0') cnt++;
            ll ans = 1e18;
            rep(i,cnt) {
                ll p = i*x, q = (cnt-i)*y;
                ans = min(ans, p+q);
            }
            cout << ans << '\n';
        }
    }
    return 0;
}