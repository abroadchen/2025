//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
s：输入的数字串。
a[i]：第 i 个数字（0-9）。
sum[i]：前缀和，sum[i] = a[1] + a[2] + ... + a[i]。
f[i]：DP 状态，f[i] 表示"前 i 个字符，能划分成的最多段数"
a[i] = s[i-1] - '0'：把字符数字转成整数（'0'-'9' → 0-9）。
sum[i] = sum[i-1] + a[i]：递推前缀和。
这样 sum[l..r] = sum[r] - sum[l-1] 可以 O(1) 得到任意区间和
j 从 i 向下走到 max(1, i-2)。也就是说，j 只取 {i, i-1, i-2}（最多往前数 3 个起点，且不小于 1）
sum[i] - sum[j-1]：段 [j, i] 的数字和。
若 %3 == 0：这段满足条件，可以作为一个新段，段数 +1。
那么从「前 j-1 个字符的最优段数 f[j-1]」后面接上这一整段，总段数 = f[j-1] + 1。
对所有候选 j 取 max，得到 f[i]
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=(n); i++)
using namespace std;

constexpr int N = 2e5+10;

string s;
int n, i, a[N], sum[N], f[N];
int main() {
    fast;
    cin >> s; n = s.size();
    rep(i,n) a[i] = s[i-1]-'0', sum[i] = sum[i-1] + a[i];
    rep(i,n) for (int j = i; j >= max(1,i-2); j--)
        f[i] = max(f[i], f[j-1]+((sum[i]-sum[j-1])%3 == 0 ? 1 : 0));
    cout << f[n] << '\n';
    return 0;
}