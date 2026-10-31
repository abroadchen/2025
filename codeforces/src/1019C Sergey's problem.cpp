//
// Created by Psy.C on 2026/10/31.
//

/**
真正学会的起点..
N = 1e6+10：点数上限；
n 点数、m 边数；
x, y：临时读边的两个端点；
vis[i]：状态数组，值是 0/1/-1（见下）;
cnt：最终选入集合点的个数；
v[x]：出边邻接表，v[x].push_back(y) 存 x→y 的边
读入 n 个点、m 条有向边；
对每条边 x→y，加入邻接表 v[x]
按 i = 1..n 递增（正向）‍ 遍历每个点：
若 vis[i] == 0（未访问）：
令 vis[i] = 1：把 i 标记为"候选入选集合"；
对 i 的所有出边指向的点 t：若 vis[t] == 0，则 vis[t] = -1（标记为"已被某入选点覆盖/支配，禁止再选"）。
按 i = n..1 递减（反向）‍ 遍历每个点：
若 vis[i] == 1（之前被标为候选入选的）：
cnt++：计数入选点；
对 i 的每个后继 t：vis[t] = -1（确保其后继都被覆盖）
第一行输出入选集合大小 cnt；
第二行输出所有 vis[i] == 1 的点编号（空格分隔）；
最后换行
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
#define per(i,n) for(int i=n;i>=1;i--)
using namespace std;

constexpr int N = 1e6+10;

int n, m, x, y, vis[N], cnt;
vector<int> v[N];
int main() {
    fast;
    cin >> n >> m;
    rep(i,m) cin >> x >> y, v[x].push_back(y);
    rep(i,n) if (!vis[i]) {
        vis[i] = 1;
        for (auto t : v[i]) if (!vis[t]) vis[t] = -1;
    }
    per(i,n) if (vis[i] == 1) {
        cnt++;
        for (auto t : v[i]) vis[t] = -1;
    }
    cout << cnt << '\n';
    rep(i,n) if (vis[i] == 1) cout << i << ' ';
    cout << '\n';
    return 0;
}