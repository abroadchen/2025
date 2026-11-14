//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
g[k]：第 k 组的数值序列（元素可能正负）。
id[k]：组编号的排列，作用是按某个顺序枚举组。
a[k]：当前已从第 k 组累计的总和（每组只累加正收益的部分）。
vis[k]：标记第 k 组是否"报废"（收益为负、停止处理）。
res：当前所有参与组的总和。
lst：当前还"活跃"的组数量上界（会不断收缩）
把组按元素个数从多到少排序。这样"长的组"先被处理，配合 ranges::sort(g[i], greater()) 把每个组内部按从大到小排序——目的是让每组的收益从大到小递减，取前缀时优先取大的正收益
外层 i 表示"当前考虑第 i 组参与"（即尝试让答案落到正好 i 个组）。lst 是活跃组上界
若第 i 组元素数 < i（不够取第 i 项），说明该组此后无法再跟上，把它及后面所有组从候选里剔除，并扣除它们已贡献的收益 a[id[l]]，收缩 lst。
若该组收益前缀已转负（a[k]+g[k][i-1]<0），标记 vis[k]，把该组已累计的收益 a[k] 从 res 里扣除（因为贡献变负，不该计入），但 a[k] 仍累加这一项以备后用。
否则收益仍为正，累加到 res 和 a[k]。
ans = max(ans,res) 用每步后的 res 更新最优答案
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= (n); i++)
using namespace std;

constexpr int N = 1e5+5;

vector<int> g[N];
inline bool cmp(int a, int b) { return g[a].size() > g[b].size(); }

int n, m, id[N], s, r, vis[N], a[N];
void solve() {
    cin >> n >> m;
    rep(i,m) id[i] = i;
    rep(i,n) { cin >> s >> r; g[s].push_back(r); }
    sort(id+1, id+1+m, cmp);
    int lst = m, ans = 0, res = 0;
    rep(i,m) ranges::sort(g[i], greater());
    rep(i,n) {
        rep(j,lst) {
            int k = id[j];
            if (g[k].size() < i) {
                for (int l = j; l <= lst; l++)
                    if (!vis[id[l]]) res -= a[id[l]];
                lst = j-1;
                break;
            }
            if (vis[k]) continue;
            if (a[k] + g[k][i-1] < 0) {
                vis[k] = 1, res -= a[k], a[k] += g[k][i-1];
                continue;
            }
            res += g[k][i-1], a[k] += g[k][i-1];
        }
        ans = max(ans, res);
    }
    cout << ans;
}


int main() {
    fast;
    solve();
    return 0;
}