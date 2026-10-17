//
// Created by Psy.C on 2026/10/17.
//
/**
从 y 向下枚举 i（i = y, y-1, ..., p+1）。范围是 (p, y]，不含 p。
枚举方向是从大到小，因为要找到最大的那个满足条件的数，找到就能直接输出退出
内层：用 j 从 2 到 √i 试探 i 是否有因子。
if (j > p) break：关键剪枝——一旦 j 超过 p 就不再往后试。含义：只检查 ≤ p 的因子，因为题目要求「i 的所有（最小）因子都要 ≤ p 才算合格」，我们只关心 j ≤ p 的因子是否存在。
if (i%j == 0)：j 整除 i，说明 i 在 ≤ p 范围内有因子 → 不合格，flg=false 并跳出。
注意这里其实是两段逻辑合并：如果 i 本身是质数（2..√i 都试不到因子），那 flg 保持 true；如果 i 有 ≤ p 的因子则 false
若 flg 仍为 true（i 满足条件），输出 i 并结束程序
若整个区间都找不到，输出 -1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll p, y;
int main() {
    fast;
    cin >> p >> y;
    for (int i = y; i > p; --i) {
        bool flg = true;
        for (int j = 2; j*j <= i; ++j) {
            if (j > p) break;
            if (i%j == 0) { flg = false; break; }
        }
        if (flg == true) { cout << i << '\n'; return 0; }
    }
    cout << "-1";
    return 0;
}