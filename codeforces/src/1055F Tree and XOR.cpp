//
// Created by Psy.C on 2026/11/9.
//

/**
真正学会的起点..
建树（读入父节点和边权），DFS 从根计算每个点 dis[i] = 根到 i 的路径异或
树形 DP 求根到每个点的异或前缀——dis[u]^dis[v] 即 u 到 v 路径异或
所有点初始都从根节点 1 开始（还没确定任何二进制位）
从最高位向下处理，保证决定第 K 小的最高位优先
now 只取 0/1，用来在两组通道间翻转（复用空间）。
第一步：重建桶（分组）‍
对每个点按已经确定的若干高位数 + 当前位 c 分桶。p1[i] 记录点 i 所在的桶，sz 统计每桶大小
第二步：统计当前位能贡献多少对
p2[i] 指向的是在另一套指针（p2 体系）下、点 i 当前所处的桶。从该桶再按当前位 c 走到子桶，sz 就是"在当前位异或结果为 0（相同 c 与 c）的配对数"。
异或同一位：0^0=0、1^1=0 → 第 k 位为 0；0^1=1 → 第 k 位为 1。
对每个点 i，统计"第 k 位能和它异或出 0（即同 c）的配对个数"并累加，sum = 第 k 位为 0 的配对数（枚举每个点作为左侧点）。
第三步：判断第 K 个在 0 侧还是 1 侧
若 K > sum：第 K 小不落在"第 k 位=0"的候选里，而是落在"第 k 位=1"的一侧，于是从第 k 位为 0 的候选里排除（K-=sum），并把答案第 k 位置 1（ans |= 1<<k）。
（注意代码里是 K>sum 时置位 1，这表示第 K 小，因为 0 < 1，第 =0 的有 sum 个，第 sum+1 起才轮到 =1 的。）

第四步：按决策方向让 p2 下移到对应方向
若 f 为真（K 落在 1 侧），对点 i 来说，与其异或得 1 的另一半在当前位必为 !c，所以把 p2[i] 降到 !c 子桶继续。
否则降到 c 子桶（异或得 0 的方向）。
这样 p2 与 p1 两套指针协同：p1 用于重建分桶，p2 用于决定搜索方向。
ans 每一位在向上处理过程中按"是否置位"决定，最终即为第 K 小的点对路径异或值
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<=k; i++)
#define per(i,j,k) for (int i=j; i>=k; i--)
#define ll long long
using namespace std;

constexpr int N = 1e6+10;

vector<pair<int,ll>> G[N];
ll dis[N];
void dfs(int u) {
    for (auto [fst, snd] : G[u]) {
        int v = fst; ll w = snd;
        dis[v] = dis[u]^w;
        dfs(v);
    }
}

int n, p1[N], p2[N], tot[2], sz[2][N], tr[2][N][2];
ll K, ans;
int main() {
    fast;
    cin >> n >> K;
    rep(i,2,n) { int p; ll w; cin >> p >> w; G[p].emplace_back(i,w); }
    dfs(1);
    rep(i,1,n) p1[i] = p2[i] = 1;
    per(k,61,0) {
        int now = k&1; ll sum = 0; tot[now] = 0;
        rep(i,1,n) {
            int c = (dis[i]>>k)&1;//点 i 的异或值在第 k 位是 0 还是 1
            sz[now^1][p1[i]] = 0;//清理上一层的计数
            if (!tr[now^1][p1[i]][c]) tr[now^1][p1[i]][c] = ++tot[now];//若还没有 c 子桶则新建
            //把 i 下放到对应子桶  该桶元素 +1 清空当前节点的两个子指针，准备下一层
            p1[i] = tr[now^1][p1[i]][c], sz[now][p1[i]]++, tr[now][p1[i]][0] = tr[now][p1[i]][1] = 0;
        }
        rep(i,1,n) {
            int c = (dis[i]>>k)&1;
            sum += sz[now][tr[now^1][p2[i]][c]];
        }
        bool f = K > sum;
        if (K > sum) K -= sum, ans |= 1ll<<k;
        rep(i,1,n) {
            int c = (dis[i]>>k)&1;
            if (f) p2[i] = tr[now^1][p2[i]][!c]; else p2[i] = tr[now^1][p2[i]][c];
        }
    }
    cout << ans << '\n';
    return 0;
}