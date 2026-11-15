//
// Created by Psy.C on 2026/11/15.
//

/**
真正学会的起点..
遇到 'a'：计数并前进。
遇到 'b'：立即 break——本 a 段在这里结束，cnt 就是该段 a 的个数。
遇到其他字符：跳过（不计数也不断段，即"杂字符"当不存在）。
循环结束后 i = cur：跳到当前处理到的位置。
每个 a 段内有 cnt 个 'a'。本题统计"不同取法数"，每段内可以选择任意多个 a 加入跳过的集合（0 个到全部 cnt 个），共 cnt+1 种选择。各段独立，总方案数 = Π (cnt_i + 1)。
ans = ans*(cnt+1) % mod 就是把每段的"选择数"乘起来。最后 ans--：因为"全都不选"（每段都不取 a，即一种空方案）不算，减掉它。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 2e5+5, mod = 1e9+7;

string s;
int main() {
    fast;
    cin >> s; s = " " + s;
    int len = s.length();
    ll ans = 1, cnt;
    for (int i = 1, cur; i <= len; i++) {
        cnt = 0; cur = i;
        while (cur <= len) {
            if (s[cur] == 'a') cnt++, cur++;
            else if (s[cur] == 'b') break;
            else cur++;
        }
        i = cur;
        ans = ans*(cnt+1)%mod;
    }
    ans--;
    cout << ans << '\n';
    return 0;
}