//
// Created by Psy.C on 2026/8/28.
//
/**
200005 规则数组的 大小上限 （支持最多 20 万条规则）
M 1900 关键阈值 ，类型 1 和类型 2 的判断条件都围绕 1900 展开
inf 1000000000 二分查找的边界值 （ l=-inf , r=inf ），表示理论上的初始值范围

- n ：当前测试用例的规则总数（ while 循环中反复覆盖）。
- d[N] ：每条规则的 类型 （ 1 或 2 ）。
- c[N] ：每条规则的 增量 （执行后当前值加上 c[i] ）

- 当规则类型是 1 ，且当前值 x < 1900 ： 直接通过！
- 注意：这里的 return true 是 提前返回 ，只要遇到这种情况就判定合法，不再继续执行后面的规则
- 当规则类型是 2 ，且当前值 x >= 1900 ： 直接失败！
- 同样是提前返回，遇此情况立刻判定不合法
规则执行后，当前值加上增量 c[i] ，准备进入下一条规则
如果 所有规则都走完了 （没有触发提前 return），判定合法

ans INT_MIN 最终答案 （最大合法初始值）， INT_MIN 是 <climits> 中的极小值，用作"未找到"标记

- 类型 1 且 ans < 1900 → 触发了提前通过的条件，标记 flag=false ，退出循环。
- 类型 2 且 ans >= 1900 → 触发了提前失败的条件（但 check 已经过了，说明不会触发）。
- 正常情况： ans += c[i] 更新值
- flag == false ：执行过程中触发了特殊条件 → 输出 Impossible 。
- flag == true ：成功执行完所有规则 → 输出最终值 ans

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5, M = 1900, inf = 1e9;

int n, d[N], c[N];
//给一个候选初始值 x ，判断它能否合法地通过 所有规则 。返回 true 表示合法
bool check(int x) {
    for (int i = 0; i < n; ++i) {
        if (d[i] == 1 && x < M) return true;
        if (d[i] == 2 && x >= M) return false;
        x += c[i];
    }
    return true;
}

int main() {
    fast;
    while (cin >> n) {
        int l = -inf, r = inf, ans = INT_MIN;
        for (int i = 0; i < n; ++i) cin >> c[i] >> d[i];
        while (l <= r) {
            //记住这个合法值 尝试更大的值（合法区间向右收缩）
            if (int mid = (l + r) / 2; check(mid)) { ans = mid; l = mid + 1; }
            else r = mid - 1;//中间值不合法，去左边找
        }
        //如果二分找到的最大合法初始值 ans ≥ 1e9 ，说明 没有上界约束 ——任意大的初始值都合法 → 输出 Infinity
        if (ans >= inf) puts("Infinity");
        else {
            bool flag = true;//执行过程没触发任何特殊条件
            for (int i = 0; i < n; ++i) {
                if (d[i] == 1 && ans < M) { flag = false; break; }
                if (d[i] == 2 && ans >= M) { flag = false; break; }
                ans += c[i];
            }
            if (flag == false) puts("Impossible");
            else cout << ans << '\n';
        }
    }
    return 0;
}