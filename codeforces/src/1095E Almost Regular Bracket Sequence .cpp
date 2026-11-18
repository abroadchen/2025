//
// Created by Psy.C on 2026/11/18.
//

/**
真正学会的起点..
sum[i] = 前 i 个字符中 "(" 数减 ")" 数（前缀和）。
最终 sum[n] 是总平衡值
mn[i] = 从位置 i 到 n 的前缀和最小值（后缀区间内 min）。
用于快速判断"翻转某位置后，从该位置往后的前缀和是否还会跌到负数"
情况 1：sum[n] == 2（总的多一个 (）‍

只有把某个 ( 翻成 )（换成 -1）才能让总和变 0。
要求该位置是 (（s[i-1]=='('）。
翻转后，从位置 i 起后续所有前缀和都会 -2。为保证仍全程 ≥0，需 mn[i] >= 2（后缀最小前缀和 ≥ 2，-2 后才 ≥ 0）。
满足则 ans++。
情况 2：sum[n] == -2（总的少一个 (）‍

只有把某个 ) 翻成 (（换成 +1）才能让总和变 0。
要求该位置是 )（s[i-1]==')'）。
翻转后，从位置 i 起后续前缀和都会 +2，不会更危险；但要保证翻转之前的状态也合法，即 mn[i] >= -2（翻转前后缀最小前缀和 ≥ -2，因为翻转后它会提高，但翻转位置之前的部分必须已合法）。
满足则 ans++。
一旦某个位置的前缀和已经 < 0（在翻转位置之前串已"提前非法"了，无论后面怎么翻都无法补救，且后续更靠右的位置也救不回来），直接结束循环
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 1e6+10;

int n, sum[N], mn[N], ans;
string s;
int main() {
    fast;
    cin >> n >> s;
    rep(i,n) {
        sum[i] = sum[i-1];
        if (s[i-1] == '(') sum[i]++; else sum[i]--;
    }
    mn[n] = sum[n];
    for (int i = n-1; i; i--) mn[i] = min(mn[i+1], sum[i]);
    rep(i,n) {
        if (sum[n] == 2 && mn[i] >= 2 && s[i-1] == '(') ans++;
        else if (sum[n] == -2 && mn[i] >= -2 && s[i-1] == ')') ans++;
        if (sum[i] < 0) break;
    }
    cout << ans;
    return 0;
}