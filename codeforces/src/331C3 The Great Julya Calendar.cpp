//
// Created by Psy.C on 2026/1/9.
//
/**
*mx: 最大值约束
n: 当前处理的数字
返回 {操作次数, 余数}
 *
 *
*如果 n 是单位数（≤ 9）：
第一个元素：如果 n > 0 或 mx > 0（需要操作），返回 1，否则返回 0
第二个元素：减去 max(mx, n) 后的余数
 *
*寻找 ≤ n/10 的最高 10 的幂次
t 成为最高位的位值
 *
*l (低位): 用约束 max(mx, n/t) 处理低位数字
n/t 是最高位数字
n % t 是移除最高位后的剩余数字
h (高位): 用更新的余数处理高位部分
n - n % t 是最高位乘以其位值
l.second 是处理低位数字后的余数
 *
*合并两部分的操作次数
返回高位部分处理的余数
 *
 *复杂度为 O(log n)
 *每个数字在每个约束值下只处理一次
 *
*将数字 n 的低位部分清零：
n % t: 保留 n 的低位部分（除最高位外的数字）
n - n % t: 清除低位，只保留最高位部分
 *将高位部分与低位处理后的余数合并，形成下一步要处理的新数字
 *
*如果 n ≥ mx：结果为 n - n = 0（n 被完全消耗）
如果 n < mx：结果为 n - mx（负值，表示需要"借位"或特殊处理）
 */
#include <iostream>
#include <map>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define ii pair<int,int>
using namespace std;

map<ii, ii> mp;//{最大值约束, 数字}, {计数, 余数}
ii dfs(int mx, int n) {
    if (mp.contains({mx, n})) return mp[{mx, n}];
    if (n <= 9) return { n > 0 || mx > 0, n - max(mx, n) };
    int t = 1;
    while (t <= n / 10) t *= 10;
    const ii l = dfs(max(mx, n / t), n % t),
    h = dfs(mx, n - n % t + l.second);
    return mp[{mx, n}] = {l.first + h.first, h.second};
}

signed main() {
    fast;
    int n; cin >> n;
    cout << dfs(0, n).first;
    return 0;
}