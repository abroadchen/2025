//
// Created by Psy.C on 2026/3/29.
//
/**
a[]: 原始数组
b[]: 操作类型数组（1或2）
c[]: 时间戳数组
t[]: 临时数组，用于排序
ans[]: 结果数组
x: 操作类型 (1或2)
y: 位置（转换为0基索引）
c[y-1] = i: 记录操作时间戳
将原数组复制到ans和t
对前mx个元素排序（t用于后续选择）
从后向前传播最新的操作（如果后面有更新的操作）
这确保了每个位置都有最新的操作信息
从后向前处理，优先处理后面的操作
b[i] == 2: 从排序数组左边取（较小值）
b[i] == 1: 从排序数组右边取（较大值）
双指针策略：贪心选择
排序：O(mx log mx)
其他操作：O(n + m)
总体：O(mx log mx + n + m)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;
int n, m, a[N], b[N], c[N], t[N], ans[N];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> a[i];
    int mx = 0;
    for (int i = 1, x, y; i <= m; ++i) {
        cin >> x >> y;
        b[y-1] = x; c[y-1] = i;
        mx = max(mx, y);
    }
    for (int i = 0; i < n; ++i) ans[i] = t[i] = a[i];
    sort(t, t + mx);
    int l = 0, r = mx - 1;
    for (int i = mx-1; i >= 0; --i) {
        if (c[i] < c[i+1]) {
            c[i] = c[i+1]; b[i] = b[i+1];
        }
    }
    for (int i = mx-1; i >= 0; --i) {
        if (b[i] == 2) ans[i] = t[l++];
        else ans[i] = t[r--];
    }
    for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
    return 0;
}