//
// Created by Psy.C on 2026/4/26.
//
/**
f[i][j]表示选择i个元素，消耗值为j时的最大收益
sum: 所有a值的总和
tot: 累计的b值总和
a1: 第一个输出结果
a2: 第二个输出结果
从b值最大的开始累加，直到tot >= sum
输出所需的元素个数a1

外层循环: 遍历所有元素
中层循环: 从a1递减到1（选择的物品数量）
内层循环: 从tot递减到b[i].b（背包容量）
状态转移: 选择当前物品i，更新f[j][k]
在所有可行范围内找到最大收益a2
输出sum - a2作为答案
O(n × a1 × tot)，其中a1 ≤ n，tot ≤ n × max(b)

f[j-1][k-b[i].b]
表示在**前(i-1)个物品中选择(j-1)个物品，消耗值为(k-b[i].b)**时的最大收益
这是选择当前物品i之前的状态
+ b[i].a
加上当前物品i的价值（注意是a值，不是b值）
物品i的属性是{a值, b值}，这里选择后获得的是a值收益
f[j-1][k-b[i].b]+b[i].a
整体含义：选择第i个物品后的新状态收益
从(j-1)个物品状态转移到j个物品状态
消耗了b[i].b的容量，获得了b[i].a的收益

f[j][k] - 不选物品i的收益（保持原状）
f[j-1][k-b[i].b]+b[i].a - 选物品i的收益

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 107;

struct node {
    int a, b;
    bool operator<(const node &o) const {
        return b > o.b;
    }
} b[N];

int n, f[N][N*N], sum, tot, a1, a2;
int main() {
    fast;
    cin >> n;
    memset(f, -0x3f, sizeof f); f[0][0] = 0;
    for (int i = 1; i <= n; ++i)
        cin >> b[i].a, sum += b[i].a;
    for (int i = 1; i <= n; ++i) cin >> b[i].b;
    sort(b + 1, b + n + 1);
    while (sum > tot) tot += b[++a1].b;
    cout << a1 << ' ';
    for (int i = 1; i <= n; ++i)
        for (int j = a1; j; --j)
            for (int k = tot; k >= b[i].b; --k)
                f[j][k] = max(f[j][k], f[j-1][k-b[i].b]+b[i].a);
    for (int i = sum; i <= tot; ++i)
        a2 = max(a2, f[a1][i]);
    cout << sum - a2;
    return 0;
}