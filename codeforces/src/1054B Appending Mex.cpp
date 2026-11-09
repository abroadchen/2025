//
// Created by Psy.C on 2026/11/8.
//

/**
真正学会的起点..
n：元素个数（最多 N=1e5+5）。
a[]：存储读入的序列。
cnt：当前"应该出现的下一个期望值"（期望序列是 0,1,2,3,…）
cnt 记录当前希望看到的"最小期望数"（从 0 开始递增）。

a[i] < cnt：当前数比期望值小。说明它可以被后面更大的数"间接满足"，因此直接忽略 continue。
a[i] == cnt：当前数正好是期望值，成功匹配一次，cnt++ 把期望值提高。
a[i] > cnt：当前数比期望值大。这意味着中间缺了期望值 cnt（少了这个数），后面的数再怎么大也补不回 cnt → 这个位置就是"断点"，输出下标 i 并结束。
如果整个数组扫完都满足 a[i] <= cnt（即没有出现"跳过期望值"的情况），输出 -1
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=(n); i++)
using namespace std;

constexpr int N = 1e5+5;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, a[N], cnt;
int main() {
    fast;
    n = rd();
    rep(i,n) a[i] = rd();
    rep(i,n) {
        if (a[i] < cnt) continue;
        if (a[i] == cnt) cnt++;
        else { cout << i << '\n'; return 0; }
    }
    cout << "-1";
    return 0;
}