//
// Created by Psy.C on 2026/11/22.
//

/**
真正学会的起点..
a, b：两个序列。
c, d：各自对应的差分数组。
f：标记是否不匹配（0=匹配，1=不匹配）
若 首元素不同或尾元素不同，直接输出 "No" 并终止
把 a 的差分 c[1..n] 和 b 的差分 d[1..n] 分别排序。
逐位比较：若有任何一位不同，置 f=1 并跳出。
若 f=0（所有差分排序后相等）→ 输出 "Yes"；否则 "No"
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
using namespace std;

constexpr int N = 1e5+5;
int n, a[N], c[N], b[N], d[N], f;
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i], c[i] = a[i] - a[i-1];
    rep(i,n) cin >> b[i], d[i] = b[i] - b[i-1];
    if (a[1] != b[1] || a[n] != b[n]) { cout << "No"; return 0; }
    sort(c+1,c+n+1); sort(d+1,d+n+1);
    rep(i,n) if (c[i] != d[i]) { f = 1; break; }
    if (!f) cout << "Yes"; else cout << "No";
    return 0;
}