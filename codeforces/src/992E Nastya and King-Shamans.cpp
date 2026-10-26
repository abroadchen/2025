//
// Created by Psy.C on 2026/10/26.
//

/**
真正学会的起点..
c[] 是树状数组（1-based）。
add(x, y)：在位置 x 增加 y（单点更新），i += i&-i 沿树向上更新所有受影响的节点。
sum(x)：查询前缀和 a[1]+a[2]+…+a[x]，i -= i&-i 沿树向下累计。
这里树状数组存储的是数组 a 中每个位置的值，sum(x) 就是数组前 x 项之和
int x = 1;：从位置 1 开始。

if (sum(1) == 0) return cout << "1\n", void();：若第一个位置前缀和为 0（即 a[1]=0），直接输出 1。

进入 while 循环（x < n 时）：

l = x+1, r = n, k = x：二分区间范围，k 记录"最后一个 sum(mid) < now 的位置"。

now = 2*sum(x)：目标值（两倍的前缀和）。

if (sum(x+1) == now)：若下一个位置的前缀和正好等于 2*sum(x)，则找到分界点 x+1，输出并返回。

二分：在 [x+1, n] 内找最后一个满足 sum(mid) < now 的 mid，记为 k。

while (l <= r) {
    int mid = (l+r)>>1;
    if (sum(mid) < now) k = mid, l = mid+1;
    else r = mid-1;
}
（因为前缀和单调不降，可用二分找分界）

if (k+1 > n) break;：若 k+1 越界，无法继续，退出循环。

x = k==x ? k+1 : k;：

若 k == x（二分没向前推进），则 x 至少 +1，避免死循环。
否则 x 跳到 k，继续下一轮迭代。
cout << "-1\n";：若整个循环都找不到满足条件的分界位置，输出 -1。
读入 n、q。
读入初始数组 a[1..n]，逐个 add(i, a[i]) 建树状数组。
循环 q 次：
读入 x、y，把 a[x] 改为 y：
add(x, y - a[x])：增量更新（先减旧值再加新值，等价于把位置 x 的值改为 y）。
a[x] = y：同步记录。
调用 solve()：在修改后的数组上找分界位置并输出
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=n; i++)
#define int long long
using namespace std;

constexpr int N = 3e5+5;

int n, c[N];
inline void add(int x, int y) { for (int i = x; i <= n; i += i&-i) c[i] += y; }
inline int sum(int x) {
    int res = 0;
    for (int i = x; i; i -= i&-i) res += c[i];
    return res;
}

inline void solve() {
    int x = 1;
    if (sum(1) == 0) return cout << "1\n", void();
    while (x < n) {
        int l = x+1, r = n, k = x, now = 2*sum(x);
        if (sum(x+1) == now) return cout << x+1 << '\n', void();
        while (l <= r) {
            int mid = (l+r)>>1;
            if (sum(mid) < now) k = mid, l = mid+1;
            else r = mid-1;
        }
        if (k+1 > n) break;
        x = k==x ? k+1 : k;
    }
    cout << "-1\n";
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int q, i, a[N], x, y;
signed main() {
    fast;
    read(n), read(q);
    rep(i,n) read(a[i]), add(i, a[i]);
    rep(i,q) {
        read(x), read(y);
        add(x, y-a[x]), a[x] = y, solve();
    }
    return 0;
}