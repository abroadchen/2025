//
// Created by Psy.C on 2026/10/1.
//
/**
读入 n 和 m，再读入 m 对 (a[i], b[i]) 作为约束
外面枚举所有可能的分母 i（题目把可能范围限定在 1..100）。
对每个 i，内层检查所有约束是否同时成立：
(a[j] + i - 1) / i 是整数形式的向上取整 ceil(a[j]/i)（避免浮点）。
若对某对约束 ceil(a[j]/i) != b[j]，则这个 i 不合法，置 flag = 1
若这个 i 满足所有约束（!flag）：
计算 w = ceil(n / i)。
若 ans 仍为 0（还没有合法值），直接记录 ans = w。
否则若新 w 与已有 ans 不同，说明存在多个不同的合法答案 → 置 ans = -1（题目要求输出唯一值）。
这里 w = ceil(n/i) 的语义：n 个元素、每组大小为 i 时的组数——即题目真正的答案是 ceil(n / 那个唯一合法的 i)
若遍历完 1-100 后 ans 仍为 0，说明没有任何 i 满足全部约束 → 输出 -1。
否则输出 ans（唯一确定的值，或 -1 表示多解冲突）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e3;
int a[N], b[N];
int main() {
    fast;
    int n, m; cin >> n >> m;
    for (int i = 1; i <= m; ++i) cin >> a[i] >> b[i];
    int ans = 0, x;
    for (int i = 1; i <= 100; ++i) {
        int flag = 0;
        for (int j = 1; j <= m; ++j) {
            x = (a[j] + i - 1)/i;
            if (x != b[j]) flag = 1;
        }
        if (!flag) {
            int w = (n + i - 1)/i;
            if (!ans) ans = w;
            else if (ans != w) ans = -1;
        }
    }
    if (!ans) ans = -1;
    cout << ans << '\n';
    return 0;
}