//
// Created by Psy.C on 2026/11/5.
//

/**
真正学会的起点..
当 k == 0 时：输出 n，然后输出 1..n 每个整数，直接结束。
这表示：当 k=0，答案就是 n 个独立"块"，每个块是单个数字 1..n。
len = 2k+1：每个块的长度为奇数 2k+1。
b = n / len：初始分块数 = n 整除块长。
rep(i,b)：为前 b 个块设置 l[i]（左端点）与 r[i]（右端点）。
l[i] = r[i-1] + 1：前一块末尾 +1。
r[i] = len * i：第 i 块右端 = len·i（所以块 i 覆盖 [len(i-1)+1, len*i]）。
if (r[b] < n)：
如果前 b 块没覆盖完 n（即 n 不是 len 的整数倍），则增加一块，把剩余 [r[b]+1, n] 作为最后一块。
于是 b 变成"向上取整"的块数：b = ceil(n / len)。
所以这段就是把 1..n 划分成若干长度为 2k+1 的连续块（最后一块可能不足 2k+1）
先输出块数 b。
情况 1：n % len == 0（n 是块长的整数倍）
对每块输出 (l[i]+r[i])/2，即每块的中点（块长为奇数 2k+1，中点是整数）。
情况 2：n % len != 0（最后一块不足）
x = n%len，对每块输出 l[i] + x/2
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=(n); ++i)
#define ll long long
using namespace std;

constexpr int N = 1005;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}


ll n, k, l[N], r[N];
int main() {
    fast;
    n = rd(), k = rd();
    if (k == 0) {
        cout << n << '\n';
        rep(i,n) cout << i << ' ';
        return 0;
    }
    ll len = 2*k+1, b = n/len;
    rep(i,b) { l[i] = r[i-1] + 1; r[i] = len*i; }
    if (r[b] < n) {
        b++;
        l[b] = r[b-1] + 1; r[b] = n;
    }
    cout << b << '\n';
    if (n%len != 0) {
        ll x = n%len;
        rep(i,b) cout << l[i]+x/2 << ' ';
    } else {
        rep(i,b) cout << (l[i]+r[i])/2 << ' ';
    }
    return 0;
}