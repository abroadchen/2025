//
// Created by Psy.C on 2026/10/16.
//
/***
排序后若 max - min ≤ 1，已经符合要求，无需任何修改，直接输出原数组和元素个数 n
由于排序后 a[1] 是最小值 m，a[n] 是最大值 M，而且 M-m ≥ 2（否则早返回了），中间的元素必然严格介于两者之间：

s1：等于最小值 m 的个数。
s3：等于最大值 M 的个数。
s2：中间值（介于 m 和 M 之间）的个数。
这里用 a[1] 和 a[n] 作为哨兵判断，是因为排序后所有等于最小/最大的都聚在两端
最终目标是让数组只含两个相邻值（差 ≤1），只有两种可能的结果集合：

方案 A：{m, m+1}（保留原最小值 m，把大的往下改）。
方案 B：{m+1, m+2}（把小的往上改，保留最大值方向）。
对应两种改动的"最少改动数"：

方案 A（变到 {m,m+1}）：把一部分最大值 M 改成 m+1 或把一部分中间值改成 m。改动次数 = 被改动元素的个数。设改 t = min(s1,s3)。
方案 B：把一部分最小值改成 m+1、把一部分中间值改成 m+2，改动次数与 s2/2 对比
t vs k 用于比较两种方案谁改动更少：

k = s2/2
这是方案 B 里能改动的中间元素对数的一半（每个中间元素改 1 次，需成对处理）
分支 1：t > k → 采用方案 A（改动 t 个）
这里把两端各 t 个元素都改成 m+1，改动 2t 个元素，剩余 n-2t 个元素不动（输出 n-t*2 表示无需改动的数量）。

注：这里 a[i]（最小值端 t 个）和 a[n-i+1]（最大值端 t 个）都被设为 m+1。会把原来的两个极值合并到中间值，代价是改 2t 个。输出为 n - 2t
分支 2：t ≤ k → 采用方案 B（改动 2k 个）
跳过前 s1 个最小值保持不变，把后面的中间值两两一组改成一个 m 和一个 m+2，改动 2k 个，其余不动，输出 n-2k

排序 O(n log n)。
统计与构造 O(n)。
总 O(n log n)，适合 n ≤ 1e5
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
using namespace std;

constexpr int N = 1e5+5;

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int a[N];
int main() {
    fast;
    int n; read(n);
    rep(i,1,n) read(a[i]);
    sort(a+1,a+n+1);
    if (a[n] - a[1] <= 1) {
        cout << n << '\n';
        rep(i,1,n) cout << a[i] << ' ';
        return 0;
    }
    int s1 = 0, s2 = 0, s3 = 0;
    rep(i,1,n) {
        if (a[i] == a[1]) s1++;
        else if (a[i] == a[n]) s3++;
        else s2++;
    }
    int t = min(s1, s3), k = s2/2, m = a[1];
    if (t > k) {
        rep(i,1,t) a[i] = m + 1;
        rep(i,1,t) a[n-i+1] = m + 1;
        cout << n-t*2 << '\n';
        rep(i,1,n) cout << a[i] << ' ';
    } else {
        rep(i,1,k) a[s1+i*2-1] = m, a[s1+i*2] = m + 2;
        cout << n-k*2 << '\n';
        rep(i,1,n) cout << a[i] << ' ';
    }
    return 0;
}