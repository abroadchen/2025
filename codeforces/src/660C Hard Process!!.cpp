//
// Created by Psy.C on 2026/4/11.
//
/**
如果num[i]非零，sum[i]保持与sum[i-1]相同
如果num[i]为零，sum[i]比sum[i-1]增加1

使用upper_bound找到我们可以改变最多k个零的第一个位置
pos: 零的数量≤ k的最右边索引
l: 初始段的长度（从0到pos）
st: 开始索引（0）
ed: 结束索引（pos）

滑动窗口遍历数组以找到最长子数组
对于每个起始位置i，找到最远的结束位置pos，这样我们可以在范围[i, pos]内最多改变k个零
如果找到更长的子数组，更新最佳结果

将最优范围[st, ed]内的所有元素改为1
输出最长段的长度
输出修改后的数组

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 3e5+5;
int n, k, num[N], sum[N];
int main() {
    fast;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> num[i];
        if (num[i]) sum[i] = sum[i-1];
        else sum[i] = sum[i-1] + 1;
    }
    int pos = upper_bound(sum, sum + n, k) - 1 - sum, l = pos + 1, st = 0, ed = pos;
    for (int i = 0; i < n; ++i) {
        pos = upper_bound(sum, sum + n, sum[i] + k) - 1 - sum;
        if (pos - i > l) {
            l = pos - i;
            st = i + 1;
            ed = pos;
        }
    }
    for (int i = st; i <= ed; ++i) num[i] = 1;
    cout << l << '\n';
    for (int i = 0; i < n; ++i) cout << num[i] << ' ';
    cout << '\n';
    return 0;
}