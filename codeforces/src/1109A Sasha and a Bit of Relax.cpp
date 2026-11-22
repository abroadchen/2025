//
// Created by Psy.C on 2026/11/22.
//

/**
真正学会的起点..
a[N]：原数组。
s[N]：前缀异或（s[i] = a[0]^a[1]^...^a[i-1]）。
cnt[2]：两个哈希表，cnt[k] 记录"下标奇偶性为 k"的前缀异或值出现次数
读 n 和数组 a[0..n-1]。
rep(i,n) s[i] = s[i-1] ^ a[i-1]：s[i] 是第 1 到第 i 个元素（即 a[0..i-1]）的异或和。s[0]=0（全局默认）
cnt[0][0] = 1：下标奇偶为 0 的情况下，前缀异或值 0 已出现 1 次（即 s[0]=0，下标记 0，奇偶为 0）。这是为了能统计从开头开始的子段。
ans = 0：答案计数
对每个 i（从 1 到 n）：
k = i%2：当前下标 i 的奇偶性（0 偶 1 奇）。
若 cnt[k] 中已存在 s[i]：
ans += cnt[k][s[i]]：累加"之前出现过相同前缀异或值 s[i] 的次数"——这些都能形成异或和为 0 的合法子段（因为 s[i] == s[j-1] 时，[j, i] 的异或和 = s[i] XOR s[j-1] = 0）。
cnt[k][s[i]]++：该值出现次数 +1。
否则 cnt[k][s[i]] = 1：首次出现
cout << ans << '\n'：输出满足条件的连续子段个数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
#define ll long long
using namespace std;

constexpr int N = 3e5+5;
int a[N], s[N];
unordered_map<int,int> cnt[2];
int main() {
    fast;
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    rep(i,n) s[i] = s[i-1]^a[i-1];
    cnt[0][0] = 1;
    ll ans = 0;
    rep(i,n) {
        int k = i%2;
        if (cnt[k].contains(s[i])) { ans += cnt[k][s[i]]; cnt[k][s[i]]++; }
        else cnt[k][s[i]] = 1;
    }
    cout << ans << '\n';
    return 0;
}