//
// Created by Psy.C on 2026/9/30.
//
/**
t[i]：任务 i，含 id（原始编号）和 c（权值）。
priority_queue<node> q：默认大根堆，按 c 从大到小排（operator< 定义为 c < o.c，即 c 越大的"优先级越高"）
入堆扩展：内层 for 从 tot（上次入到的位置）一路推到 i+k（且不超过 n），把所有"位置 ≤ i+k 的任务"都塞进堆 q，tot 更新为新推进到的位置。

含义：填"时间槽 i+k"时，可选的候选任务必须满足其原始位置 ≤ i+k（因为任务只允许原位置向后推迟，不能往前）。
取最大 c 任务放到当前槽：tmp = q.top() 取出堆里 c 最大的任务，在本次时间槽 x = i+k 执行它，ans[tmp.id] = x。

累加代价：res += c * (x - id)，即该任务被安排到了 x，比原始位置 id 推迟了 (x-id)，代价 = c × 推迟量。

循环 i 从 1 到 n，每个循环对应一个时间槽 x = i+k，共填 n 个槽

因为代价是"权值 c × 推迟量"，要让总代价尽量小，就应该把 c 大的任务尽量早安排（推迟量小），所以每次从当前可用候选里挑 c 最大的放到最靠前的空槽 —— 这等价于经典的"按权值 c 从大到小优先调度"贪心，优先队列保证取最大 c 是 O(log) 的
先输出最小代价 res，再按任务编号 1..n 输出各自被安排到的槽位 x
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 3e5+5;

struct node {
    int id, c;
    bool operator<(const node &o) const {
        return c < o.c;
    }
} t[N];

priority_queue<node> q;
node tmp;
int ans[N];
ll res;
int main() {
    fast;
    int n, k; cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> t[i].c; t[i].id = i;
    }
    int tot = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = tot; j <= i+k && j <= n; ++j)
            q.push(t[j]), tot++;
        tmp = q.top(); q.pop();
        int x = i + k;
        ans[tmp.id] = x;
        res += 1ll*tmp.c*1ll*(x-tmp.id);
    }
    cout << res << '\n';
    for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
    return 0;
}