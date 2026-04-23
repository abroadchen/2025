//
// Created by Psy.C on 2026/4/22.
//
/**
长度为30的周期序列
形成一个山峰形状：0→15→0
前半部分：0到15递增
后半部分：15到0递减
尝试将输入序列与数组d的每个可能起始位置进行匹配
当只有一个元素且不是边界值（0或15）时，跳过

flag = 1: 匹配成功的标志
now = 0: 当前匹配的输入数组索引
s = i: 当前匹配的基准数组d的索引
循环比较d[s]和a[now]是否相等
如果相等，继续匹配下一个元素
如果不相等，设置flag = 0并退出循环

m = (s + 1) % 30: 计算下一个位置
比较d[m]和d[s]的大小关系：
如果d[m] > d[s]：趋势上升 → 输出"UP"
如果d[m] ≤ d[s]：趋势下降 → 输出"DOWN"
O(30×n) = O(n)，其中30是固定的周期长度
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, a[100], d[] = {
    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1
};
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < 30; ++i) {
        if (n == 1 && a[0] != 15 && a[0] != 0) continue;
        int flag = 1, now = 0, s = i;
        while (flag) {
            if (d[s] != a[now]) flag = 0;
            if (now == n-1) break;
            now++;
            s = (s + 1) % 30;
        }
        if (flag == 0) continue;
        int m = (s + 1) % 30;
        if (d[m] > d[s]) cout << "UP\n";
        else cout << "DOWN\n";
        return 0;
    }
    cout << "-1\n";
    return 0;
}