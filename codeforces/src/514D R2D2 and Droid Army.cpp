//
// Created by Psy.C on 2026/2/28.
//
/**
n：行数，m：列数，k：目标和的上限
a[N][M]：输入的二维数组
b[M]：存储最优解的数组
s[M]：每列维护一个多重集合，存储当前窗口中的元素

j：当前处理的行
q：滑动窗口的左边界
cnt：当前最长的有效窗口长度
将当前行的每个元素插入对应列的多重集合中
当前窗口的和超过k时，收缩左边界
*s[i].rbegin()：获取第i列当前的最大值
如果最大值之和超过k，说明窗口无效
移除第q行的所有元素（从每列的集合中删除）
增加左边界q
如果当前窗口长度更大，更新最优解
j-q+1：当前窗口的长度
记录每列的最大值到数组b中

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 0; i < n; ++i)
using namespace std;
constexpr int N = 1e5+1, M = 6;
int n, m, k, a[N][M], b[M];
multiset<int> s[M];
int main() {
    fast;
    cin >> n >> m >> k;
    rep(i,n) rep(j,m) cin >> a[i][j];
    for (int j = 0, q = 0, cnt = 0; j < n; ++j) {
        rep(i,m) s[i].insert(a[j][i]);
        while (q <= j) {
            int sum = 0;
            rep(i,m) sum += *s[i].rbegin();
            if (sum <= k) break;
            rep(i,m) s[i].erase(s[i].find(a[q][i]));
            q++;
        }
        if (cnt < j-q+1) {
            cnt = j-q+1;
            rep(i,m) b[i] = *s[i].rbegin();
        }
    }
    rep(i,m) {
        if (i) cout << ' ';
        cout << b[i];
    }
    return 0;
}