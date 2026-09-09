//
// Created by Psy.C on 2026/9/8.
//
/**
N = 2e4 + 4e2（即 20000+400=20400）：数组大小。
M = 1e4 + 4e2（即 10400）：值的上限 + 1（用于遍历）。
num[N]：打表数组，num[x] 存整数 x 二进制表示中 1 的个数（popcount）

对所有 i in [0, N)，统计其二进制中 1 的个数存入 num[i]。
方法：反复取 t%2 累加、t/=2（等价于逐位右移看最低位）。
预处理一次即可供后面对多次查询 O(1) 使用（num[xx] 直接取值）

外层 while (cin >> n >> k)：多组测试用例，读到 EOF 结束。
每次重置 vis 为 0。
读入 n 个数，用 vis[x]++ 做计数（频率）统计——vis[x] 表示数值 x 在输入中出现的次数
外层枚举 i（vis[i]==0 的跳过，只处理出现过的值）。
内层 j 从 i 开始枚举（保证 i<=j，从而每个无序对只被统计一次，避免重复）。
若 vis[j]>0（j 也出现过）：
if (num[i^j] == k)：若 i 与 j 异或后二进制 1 的个数恰好等于 k，则这一对 (i,j) 满足条件。
配对计数：
if (i == j)：i 与 j 相同，则从 vis[i] 个同类元素里任选 2 个组成一对，即组合数 C(vis[i], 2) = vis[i]*(vis[i]-1)/2。
else：i≠j 时，i 的每个元素和 j 的每个元素各配一个，共 vis[i] * vis[j] 对。
累加进 ans，最后输出

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e4+4e2, M = 1e4+4e2;

int num[N];
void init() {
    memset(num, 0, sizeof(num));
    for (int i = 0; i < N; ++i) {
        int t = i;
        while (t) { num[i] += t%2; t /= 2; }
    }
}

int n, k;
ll vis[N];
int main() {
    fast;
    init();
    while (cin >> n >> k) {
        memset(vis, 0, sizeof(vis));
        for (int i = 0, x; i < n; ++i) {
            cin >> x; vis[x]++;
        }
        ll ans = 0;
        for (int i = 0; i < M; ++i) {
            if (vis[i] == 0) continue;
            for (int j = i; j < M; ++j) {
                if (vis[j] > 0) {
                    if (num[i^j] == k) {
                        if (i == j) ans += vis[i]*(vis[i]-1)/2;
                        else ans += vis[i]*vis[j];
                    }
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}