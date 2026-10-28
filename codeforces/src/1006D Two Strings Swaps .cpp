//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
char t[10] = {'i', q, w, e, r};——把四个字符放进数组（t[1..4]），下标从 1 开始用（t[0]='i' 只是占位）。

sort(t+1, t+5)——对四个字符升序排序（t[1..4]）。

if (t[1]==t[2] && t[3]==t[4]) return;——若排序后为两两相等（如 x,x,y,y），即 4 个元素能组成"两对相同"，则此组不需要操作（return，不加 cnt）。

这个条件的意思是：当 4 个字符中，排序后 t[1]==t[2] 且 t[3]==t[4]，即"能配成两组相同字符"，那么通过对称摆放天然满足约束，无需额外操作。
cnt++;——否则（不满足两两配对），需要一次操作（基础计数 +1）。

if (q==e || q==r || w==e || w==r || e==r) return;——如果这四个字符之间存在某些相等关系（q 与 e/r 相等、w 与 e/r 相等、或 e==r），则不需要再加（前面那一步已经算过一次操作，这里直接 return）。

cnt++;——否则再多加一次操作。

本质上 solve 在统计这一组四连字符需要几个操作（0、1 或 2 次），规则是：

排序后能两两配对 → 0 次；
存在相等跨排/同排关系（能使交换后合法）→ 1 次；
其余 → 2 次。
读入 a、b 两个数组。
rep(i,n>>1)（即 i=1..n/2）对每个对称组调用 solve，传入：
a[i] 与 a[n-i+1]（a 的对称一对）
b[i] 与 b[n-i+1]（b 的对称一对）
即 solve(a[i], a[n-i+1], b[i], b[n-i+1]) → 对应函数的 q,w,e,r。
奇数长度特殊处理：if (n%2==1) cnt += a[n/2+1] != b[n/2+1];
当 n 为奇数时，正中间一个位置（a[n/2+1] 与 b[n/2+1]）没有对称配对，刚好是"中心"。
若这两个中心字符不相等，则需一次操作（cnt += 1，因为 a!=b 为 1，相等为 0）。
输出 cnt
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i = 1; i <= n; ++i)
using namespace std;

constexpr int N = 2e5+5;

int cnt;
inline void solve(char q, char w, char e, char r) {
    char t[10] = {'i', q, w, e, r};
    sort(t+1, t+5);
    if (t[1] == t[2] && t[3] == t[4]) return;
    cnt++;
    if (q == e || q == r || w == e || w == r || e == r) return;
    cnt++;
}

int n, i;
char a[N], b[N];
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i];
    rep(i,n) cin >> b[i];
    rep(i,n>>1) solve(a[i], a[n-i+1], b[i], b[n-i+1]);
    if (n%2 == 1) cnt += a[n/2+1] != b[n/2+1];
    cout << cnt;
    return 0;
}