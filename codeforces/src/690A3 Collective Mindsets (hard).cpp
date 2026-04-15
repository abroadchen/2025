//
// Created by Psy.C on 2026/4/15.
//
/**
q：查询次数
n：循环序列的长度
r：目标位置
cnt：计数器，用于统计输入的总和
读取n-1个偏移量并累加到cnt中
cnt%n：计算所有偏移量对n取模的总和 总的偏移量在循环中的有效部分
r-cnt%n：从目标位置减去总的偏移量 调整后的位置（可能为负数)
(r-cnt%n+n)%n：确保结果在[0, n-1]范围内
+1：转换为1基索引
时间复杂度：O(n*q)，其中q是查询次数，n是每次查询的平均处理长度
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int q, n, r, cnt;
int main() {
    fast;
    cin >> q;
    while (q--) {
        cnt = 0;
        cin >> n >> r;
        for (int i = 1, x; i < n; ++i) {
            cin >> x; cnt += x;
        }
        cout << (r-cnt%n+n)%n+1 << '\n';
    }
    return 0;
}