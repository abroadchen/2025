//
// Created by Psy.C on 2026/1/12.
//
/**
* node：包含值 x 和原始索引 id
重载 < 运算符，用于优先队列排序
priority_queue<node>：最大堆（由于重载了 < 运算符）
*ans：存储操作结果
tot：操作计数器
*执行操作：将 x 的值加到自己，从 y 中减去
记录操作：(x.id, y.id) 表示从 x 向 y 转移
 *
*当 t.x > 0 时继续循环
计算 k = b.x / t.x，即可以执行多少次转移
使用倍增思想处理大量操作
重新排序三个节点，使最小的成为新的 t
返回处理后的两个较大节点
 *
 *检查是否有解（倒数第二大值不能为0）
*跳过值为0的元素
将非零元素加入优先队列
每次取3个最小元素，合并后放回2个结果
*输出操作总数
输出每步操作
 *
 *k&1<<i 检查 k 的第 i 位是否为1
 *
*从节点 y 向节点 x 转移 x 的原始值
节点 x 的值翻倍
节点 y 的值减少 x 的原始值
*将较小的值 x 增大（翻倍）
将较大的值 y 减小
通过这种方式逐渐使所有值趋向平衡
 */
#include <algorithm>
#include <iostream>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1005
#define M 100005
using namespace std;

struct node { int x, id; } a[N];
bool operator<(const node p, const node q) { return p.x < q.x; }
priority_queue<node> q;

pair<int, int> ans[M];
int tot;
void d(node& x, node& y) {
    const int t = x.x;
    x.x += t; y.x -= t;
    ans[++tot] = {x.id, y.id};
}

pair<node, node> merge(node t, node b, node c) {
    while (t.x) {
        const int k = b.x / t.x;
        for (int i = 0; 1<<i <= k; ++i) {
            if (k&1<<i) d(t, b); else d(t, c);
        }
        node x[3] = {t, b, c};
        sort(x, x+3, [](const node p, const node q) {
            return p.x < q.x;
        });
        t = x[0]; b = x[1]; c = x[2];
    }
    return {b, c};
}

int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i].x, a[i].id = i;
    sort(a + 1, a + 1 + n, [](const node p, const node q) {
        return p.x < q.x;
    });
    if (a[n-1].x == 0) { cout << "-1\n"; return 0; }
    int l = 1;
    while (a[l].x == 0) l++;
    for (int i = l; i <= n; ++i) q.push(a[i]);
    while (q.size() > 2) {
        const auto A = q.top(); q.pop();
        const auto B = q.top(); q.pop();
        const auto C = q.top(); q.pop();
        auto [fst, snd] = merge(A, B, C);
        if (fst.x) q.push(fst);
        if (snd.x) q.push(snd);
    }
    cout << tot << '\n';
    for (int i = 1; i <= tot; ++i)
        cout << ans[i].first << ' ' << ans[i].second << '\n';
    return 0;
}