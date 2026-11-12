//
// Created by Psy.C on 2026/11/12.
//

/**
真正学会的起点..
m > n：需要的组大小 m 大于总数量 n → 不可能，输出 -1。
k+l > n：k 与 l 的和超过总数量 n → 也不可能，输出 -1。
任一条件成立：cout << -1; return 0; 直接结束。
[推] 含义：m 是要填满的每组大小；k+l 是某种"必须满足的最低需求量"，不能超过 n
(l+k)/m：整型除法（向下取整）。
(l+k)%m ? 1 : 0：若有余数则 +1（向上取整）。
两行合并等价于：cnt = ceil((l+k)/m)，即 (l+k) 除以 m 向上取整得到需要的组/轮次数。
含义：需要 ceil((k+l)/m) 个大小为 m 的组来覆盖 k+l 的数量
cnt*m：实际会占用的总数（cnt 组 × 每组 m 个）。
if (cnt*m > n)：所需总量超过 n → 资源不够，输出 -1。
否则：输出 cnt（可行所需的组数）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, m, k, l;
int main() {
    fast;
    cin >> n >> m >> k >> l;
    if (m > n || k+l > n) { cout << -1; return 0; }
    ll cnt = (l+k)/m; cnt += (l+k)%m ? 1 : 0;
    if (cnt*m > n) cout << -1; else cout << cnt;
    return 0;
}