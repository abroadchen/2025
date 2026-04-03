//
// Created by Psy.C on 2026/4/2.
//
/**
bct: 离散化后的值域大小
update: 单点更新，维护最大值
query: 前缀最大值查询
n, m: 数组长度和询问数
a[N]: 输入数组
b[N]: 离散化数组
f[N]: 以i结尾的LIS长度
g[N]: 从i开始的LDS长度
h[N]: LIS长度为i的元素个数
pre[N], suf[N]: 前缀和后缀查询结果
q[N]: 每个位置的查询

读入数组和查询
将所有值收集到b数组中用于离散化
离散化处理
将原值转换为离散化后的索引
计算LIS：f[i]是以位置i结尾的最长递增子序列长度
查询小于a[i]的所有值的最大f值
计算LDS：g[i]是从位置i开始的最长递减子序列长度
使用反向映射来处理递减子序列
k: 最长的单峰子序列长度（LIS+LDS-1）
统计每个LIS长度在关键路径中的出现次数
对于每个查询，计算在位置i前，值小于x的LIS最大长度
对于每个查询，计算在位置i后，值小于x的LDS最大长度
如果修改后最长单峰子序列长度小于k，且当前点在唯一的关键路径上
则答案是k-1
否则答案是max(pre[id] + suf[id] + 1, k)

时间复杂度：O((n+m)log(n+m))
 */
#include <ranges>
#include <bits/stdc++.h>
#define ii pair<int, int>
using namespace std;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

constexpr int N = 1e6+5;

int bct;
namespace fwt {
    int t[N];
    int low_bit(int x) { return x & -x; }
    void update(int x, int d) {
        for (int i = x; i <= bct; i += low_bit(i))
            t[i] = max(t[i], d);
    }
    int query(int x) {
        int res = 0;
        for (int i = x; i >= 1; i -= low_bit(i))
            res = max(res, t[i]);
        return res;
    }
    void init() { memset(t, 0, sizeof(t)); }
}

int n, m, a[N], b[N], f[N], g[N], h[N], pre[N], suf[N], ans[N];
vector<ii> q[N];
int main() {
    n = rd(), m = rd();
    for (int i = 1; i <= n; ++i) {
        a[i] = rd();
        b[++bct] = a[i];
    }
    for (int i = 1; i <= m; ++i) {
        int x = rd(), d = rd();
        q[x].emplace_back(d, i);
        b[++bct] = d;
    }
    sort(b + 1, b + bct + 1);
    bct = unique(b + 1, b + 1 + bct) - b - 1;
    for (int i = 1; i <= n; ++i) {
        a[i] = lower_bound(b + 1, b + bct + 1, a[i]) - b;
        for (auto &x: q[i] | views::keys)
            x = lower_bound(b + 1, b + bct + 1, x) - b;
    }
    fwt::init();
    for (int i = 1; i <= n; ++i) {
        f[i] = fwt::query(a[i] - 1) + 1;
        fwt::update(a[i], f[i]);
    }
    fwt::init();
    for (int i = n; i >= 1; --i) {
        g[i] = fwt::query(bct - a[i]) + 1;
        fwt::update(bct - a[i] + 1, g[i]);
    }
    int k = 0;
    for (int i = 1; i <= n; ++i) k = max(k, f[i]+g[i]-1);
    for (int i = 1; i <= n; ++i)
        if (f[i] + g[i] - 1 == k) h[f[i]]++;
    fwt::init();
    for (int i = 1; i <= n; ++i) {
        for (auto [x, id] : q[i])
            pre[id] = fwt::query(x-1);
        fwt::update(a[i], f[i]);
    }
    fwt::init();
    for (int i = n; i >= 1; --i) {
        for (auto [x, id] : q[i])
            suf[id] = fwt::query(bct - x);
        fwt::update(bct - a[i] + 1, g[i]);
    }
    for (int i = 1; i <= n; ++i)
        for (auto id: q[i] | views::values) {
            if (pre[id] + suf[id] + 1 < k && f[i] + g[i] - 1 == k && h[f[i]] == 1)
                ans[id] = k - 1;
            else ans[id] = max(pre[id] + suf[id] + 1, k);
        }
    for (int i = 1; i <= m; ++i)
        cout << ans[i] << '\n';
    return 0;
}