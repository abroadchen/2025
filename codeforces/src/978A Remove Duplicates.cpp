//
// Created by Psy.C on 2026/10/22.
//
/**
n 个数读入 a。
用双指针把数组整体前后翻转（i 与 n-i+1 交换），循环 n/2 次
翻转后的数组从头遍历（此时等于原数组的从末尾倒着往前）。
f[] 是标记数组。若该值还没出现过（f[a[i]] != 1），就把它加入 b[]（推进 cnt），并标记 f[a[i]]=1，个数 tot++。
由于遍历顺序是"原数组的最后一个元素→第一个元素"，所以每个值第一次被遇到的是它在原数组里最后一次出现的那个位置，因此保留下来的正是每个值最后一次出现的位置
输出去重后元素个数 tot。
b 中存的是"按翻转后顺序"保留的值，即原数组从末尾往前去重的顺序；代码再倒着输出 b，即恢复成正序——即按原数组中各保留元素出现的位置顺序输出
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
using namespace std;

constexpr int N = 1e3+1, M = 1e5+1;

int n, a[N], t, f[M], b[N], cnt, tot;
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i];
    rep(i,n/2) { t = a[i]; a[i] = a[n-i+1]; a[n-i+1] = t; }
    rep(i,n) if (f[a[i]] != 1) {
        b[++cnt] = a[i];
        f[a[i]] = 1;
        tot++;
    }
    cout << tot << '\n';
    for (int i = cnt; i >= 1; i--) cout << b[i] << ' ';
    return 0;
}