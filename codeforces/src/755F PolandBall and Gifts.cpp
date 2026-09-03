//
// Created by Psy.C on 2026/9/2.
//
/**
n 节点总数
k 目标选中节点数
g[N] 桶计数： g[s] = 大小为 s 的分量有多少个
h 所有分量大小的列表（排序后）
nh 优化后的重量列表 （用于多重背包的二进制拆分）
bt bitset 背包 ： bt[s] = 1 表示可以选出和为 s 的子集
q 优先队列 （最大堆）：用于贪心

k=0 时不用选任何东西，直接输出 0 0 。 void() 是为了让 return 后面可以跟表达式（void 表达式）。

- 对每个未访问节点 i，做一次 dfs，得到该分量的总大小 cnt
- h 存所有分量大小
- g[s]++ 统计"大小为 s 的分量有几个"

- 一个数 m 可以拆成 1, 2, 4, 8, ..., 余数 的和
- 用这些数可以组合出 1~m 的 任何值
- 把 g[i] 拆成若干个 i*t （t 是 2 的幂），每个当成独立物品 → 转成 0/1 背包

bt 是一个 bitset，bt[s] = 1 表示"是否能选出和为 s 的子集"
初始: bt[0] = 1（什么都不选，和为 0）
处理重量 i: bt |= bt << i
  原来能得到的和 s，现在也能得到 s+i

把所有分量大小放入优先队列
最大堆，堆顶是最大的分量大小
- bt[k] == 1 → 能选出和恰好为 k 的子集 → 输出 k
- bt[k] == 0 → 不能恰好选 k，输出 k+1 （至少要 k+1 个节点）
每次取最大的分量 y:
  如果 y >= 2:
    cnt += 1       （选了一个分量/或"操作"）
    mx += 2         （mx 增加 2）
    把 y-2 放回堆
  如果 y == 1:
    cnt += 1
    mx += 1       （mx 只增加 1）
  当 cnt == p 时停止
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

namespace june {
    constexpr int N = 1e6+5;

    bool vis[N];//访问标记
    int cnt = 0, ne[N];//cnt=当前环大小, ne[i]=节点i指向谁
    void dfs(int u) {
        if (vis[u]) return;//已访问 → 说明回到环起点了
        vis[u] = true;
        cnt++;
        dfs(ne[u]);//沿出边走
    }

    int n, k, g[N];
    vector<int> h, nh;
    bitset<N> bt;
    priority_queue<int> q;
    void solve() {
        cin >> n >> k;
        if (k == 0) return cout << "0 0", void();
        for (int i = 1; i <= n; ++i) cin >> ne[i];
        for (int i = 1; i <= n; ++i) {
            if (vis[i] == 0) {
                cnt = 0; dfs(i); h.push_back(cnt);
                g[cnt]++;
            }
        }
        ranges::sort(h);
        for (int i = 1; i <= n; ++i) {
            if (g[i] == 0) continue;
            int t = 1;
            while (true) {
                if (g[i] < t) break;
                nh.push_back(i*t);
                g[i] -= t;
                t <<= 1;
            }
            if (g[i]) nh.push_back(i*g[i]);
        }
        bt[0] = 1;
        for (int i : nh) bt |= bt<<i;
        for (int i : h) q.push(i);
        int p = k, cnt = 0, mx = 0;
        if (bt[k]) cout << k << ' '; else cout << k+1 << ' ';
        while (!q.empty()) {
            int y = q.top(); q.pop();
            if (y >= 2) {
                cnt++; mx += 2;
                if (y-2 > 0) q.push(y-2);
            } else if (y == 1) { cnt++; mx++; }
            if (cnt == p) break;
        }
        cout << mx;
    }
}


int main() {
    fast;
    int T = 1;
    while (T--) june::solve();
    return 0;
}