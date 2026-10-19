//
// Created by Psy.C on 2026/10/18.
//
/**
若 a >= 2*b，则把 a 变成 a mod (2b)（等价于"从 a 中减去 2b、2·2b、… 直到 a 小于 2b"）；
若 b >= 2*a，则把 b 变成 b mod (2a)。
当不能再进行任何操作（即 a < 2b 且 b < 2a，或某数为 0）时停止，输出最终的 a b

if (a == 0 || b == 0) break;

只要有一方为 0，博弈结束，退出循环。
if (a >= b*2) a = a%(b*2);

如果 a 至少是 b 的两倍，就把 a 约减成 a mod (2*b)。
原理：当 a >= 2*b 时，这一轮"取石子"的玩家可以选择 减去 b 个 或 减去 2b 个 来翻转局面/占优。数学上，最终可行的约减结果是 a mod (2b)，所以可以直接跳到最终状态，不必一步步模拟。
用取模一步到位，正是欧几里得算法思想的扩展——大幅减少循环次数（本来可能是线性次数，变成近 log 次）。
else if (b >= a*2) b = b%(a*2);

对称：如果 b 至少是 a 的两倍，就约减 b → b mod (2*a)。
else break;

都不满足（即 a < 2b 且 b < 2a），左右两边都不再能"一口吃掉"对方一大块，博弈进入"均衡"阶段，直接退出，输出当前状态即可
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll a, b;
int main() {
    fast;
    cin >> a >> b;
    while (true) {
        if (a == 0 || b == 0) break;
        if (a >= b*2) a = a%(b*2);
        else if (b >= a*2) b = b%(a*2);
        else break;
    }
    cout << a << ' ' << b << '\n';
    return 0;
}