//
// Created by Psy.C on 2026/3/24.
//
/**
l, r: 查询范围的左边界和右边界
k: 倍数因子
t: 当前计算的幂值
flag: 标志变量，标记是否输出过结果

循环条件：t <= r，当当前幂值不超过右边界时继续
范围检查：如果t >= l，说明t在范围内，输出t并设置flag
溢出预防：if (t > r/k) break;
避免t * k时发生整数溢出
如果t > r/k，则t * k > r，无需继续计算
幂值更新：t *= k，计算下一个k的幂次

时间复杂度：O(log_k(r))，只需要计算有限个幂次
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ull unsigned long long
using namespace std;

ull l, r, k, t;
int flag;
int main() {
    fast;
    cin >> l >> r >> k; t = 1;//k^0 = 1
    while (t <= r) {
        if (t >= l) {
            cout << t << ' ';
            flag = 1;
        }
        if (t > r/k) break;
        t *= k;
    }
    if (!flag) cout << "-1\n";
    return 0;
}