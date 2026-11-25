//
// Created by Psy.C on 2026/11/25.
//

/**
真正学会的起点..
a[] 存原始输入，b[] 存重排后的答案
双指针：l 从数组开头（放小值），r 从数组末尾（放大值）。
第奇数个元素（i=1,3,5,...）取 a[i]（当前最小），放到 b[l++]；
第偶数个元素（i=2,4,6,...）取 a[i]（当前较大），放到 b[r--]。
效果：小值填头部往前，大值填尾部往后，中间交替衔接
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;

constexpr int N = 10010;
inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int a[N], b[N];
int main() {
    fast;
    int n = rd();
    rep(i,n) a[i] = rd();
    sort(a+1,a+1+n);
    int l = 1, r = n;
    rep(i,n) if (i&1) b[l++] = a[i]; else b[r--] = a[i];
    rep(i,n) cout << b[i] << ' ';
    return 0;
}