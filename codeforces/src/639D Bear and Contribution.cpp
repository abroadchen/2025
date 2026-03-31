//
// Created by Psy.C on 2026/3/31.
//
/**
M = 5：模数（固定为5）
b, c：成本参数
sum[M]：每个余数类别的和
k：选取数量限制
ans：答案（初始化为极大值）
q[M]：5个优先队列（最大堆），按余数分类

分类处理：z = x%M - 按x的模M值分类
权重计算：w = y*c - b*(x/M) - 计算权重
加入队列：将w加入对应分类的优先队列
维护大小：如果队列大小超过k，移除最大值并更新sum
更新答案：当队列大小正好为k时，尝试更新最小值

b = min(b, c*M) - 确保b不会过大
读入数组并偏移：a[i] += 1e9 - 避免负数
对每个输入元素和每个可能的偏移量j（0到4）调用get函数
get(a[i]+j, j) - 尝试将a[i]调整j个单位的代价

a[i] 是原始数值
可以花费 j*c 的代价将 a[i] 增加 j
每增加 M 单位需要花费 b 的代价
目标是选择k个元素使其总成本最小
时间复杂度：O(nMlog k)，空间复杂度：O(M*k)

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 5e6+5, M = 5;

ll b, c, sum[M], k, ans=1e18;
priority_queue<ll> q[M];
void get(int x, int y) {
    int z = x%M;
    ll w = y*c - b*(x/M);
    q[z].push(w); sum[z] += w;
    if (q[z].size() > k)
        sum[z] -= q[z].top(), q[z].pop();
    if (q[z].size() == k)
        ans = min(ans, sum[z]+x/M*b*k);
}
ll n, a[N];
int main() {
    fast;
    cin >> n >> k >> b >> c; b = min(b, c*M);
    for (int i = 1; i <= n; ++i)
        cin >> a[i], a[i] += 1e9;
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < M; ++j)
            get(a[i]+j, j);
    cout << ans << '\n';
    return 0;
}