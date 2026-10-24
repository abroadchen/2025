//
// Created by Psy.C on 2026/10/24.
//

/**
真正学会的起点..
add(x,v)：单点加 v，向上更新（x += x&-x）。
query(x)：前缀和（x -= x&-x），返回 [1..x] 的和。
标准树状数组，用来统计逆序对
从右往左扫排列。
对当前的 a[i]，query(a[i]) 得到已经出现在它右边且值小于 a[i] 的元素个数——这就是以 a[i] 为左元素的逆序对数（右边较小元素数）。
累加进 ans 得到总逆序对数。
然后把 a[i] 加入树状数组（标记该值已出现）。
这样 O(n log n) 求出排列的逆序对总数
ans &= 1：取逆序对数的奇偶性（0 偶 / 1 奇）。
n &= 1：取 n 的奇偶性。
若二者相同 → 输出 Petr，否则 Um_nik
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e6+10;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, s[N];
inline void add(int x, int v) { while (x <= n) s[x] += v, x += x&-x; }
inline int query(int x) {
    ll t = 0;
    while (x) t += s[x], x -= x&-x;
    return t;
}

int a[N];
ll ans;
int main() {
    fast;
    n = rd();
    for (int i = 1; i <= n; ++i) a[i] = rd();
    for (int i = n; i; --i) {
        ans += query(a[i]);
        add(a[i], 1);
    }
    ans &= 1; n &= 1;
    if (ans == n) cout << "Petr\n"; else cout << "Um_nik\n";
    return 0;
}