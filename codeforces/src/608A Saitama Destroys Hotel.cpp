//
// Created by Psy.C on 2026/3/23.
//
/**
n: 输入的人数
s: 起始位置
a[N]: 存储每个位置所需的最大时间的数组
读取每个人的位置x和时间t
对于每个位置x，存储该位置上所有人的最大时间
这表示在位置x的最晚到达时间

从位置s开始，向后移动到位置0
ans跟踪到达位置0所需的时间
在每个位置i，更新ans为以下两者的最大值：
当前ans（不考虑这个位置的所需时间）
a[i]（在位置i的最晚到达时间）
将ans加1（移动到左边一格所需的时间）

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1005;
int n, s, a[N];
int main() {
    fast;
    cin >> n >> s;
    for (int i = 1, x, t; i <= n; ++i) {
        cin >> x >> t;
        a[x] = max(t, a[x]);
    }
    int ans = 0;
    for (int i = s; i >= 0; --i) {
        ans = max(ans, a[i]);
        ans++;
    }
    cout << ans-1 << '\n';
    return 0;
}