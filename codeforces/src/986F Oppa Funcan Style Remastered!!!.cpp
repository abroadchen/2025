//
// Created by Psy.C on 2026/10/24.
//

/**
真正学会的起点..
N：最大查询个数（q ≤ 1e4）。
M：同余最短路里 dis 数组的上限（因为做最短路时要取模 x = pr[0]，x 是某个质因子，最大不超过……实际这里 M 应大于模数，见后面分析）。
L：筛子的上限 31630000 ≈ 3.16e7。这里 L 取到约 31623000（= sqrt(1e15) 左右）‍，是为了筛出 v = k 的所有小质因子 —— 因为 k ≤ 1e15（可能），其质因子要么 ≤ sqrt(k)，要么是剩下一个大于 sqrt(k) 的质数
欧拉筛（线性筛）‍：

vis[i] 标记合数，pri[] 存素数，cnt 记录质数个数。
外层遍历 i，若 vis[i]==0 则 i 是质数入表。
内层用 i 去筛掉 pri[j]*i，并一旦 i%pri[j]==0 就 break（关键：保证每个合数只被其最小质因子筛一次 → 线性复杂度）。
筛出 <= n 的所有质数
对 v 做去重质因数分解：

遍历所有筛出的质数，若整除则记入并连除干净（while 去掉该因子的所有幂次）。
因为筛到了 L ≈ 3.16e7，若还有剩余 v > 1，那 v 要么本身就是 > L 的质数、要么是剩余的大质数，直接 push_back。
返回互不相同的质因子集合 ret（已去重
q：查询数。
res[]：记录每个查询的答案（1=YES，0=NO）。
mp：map<ll, vector<li>>，把相同 k 的所有查询分组。键是 k，值是该 k 下的所有查询 (n, 序号i)。这样同一个 k 只需处理一次质因子分解和一次最短路，避免重复算。
dis[]：同余最短路用的距离数组
先筛 L 以内素数。
读入 q 组 (n, k)。
如果 k==1：k 没有质因子，1 无法用"大于 1 的质数"组合表示任何 n（n>=1 情况下），所以这种情况不加入 mp（res 默认 0 = NO）。
否则按 k 分组：mp[k] 里存一堆 (n, 序号i)
v = k，pr 为 k 的质因子集合（升序排列，因为 dec 按 pri 升序遍历）。
记 pr[0] 为最小质因子 x。
有三种情况，按质因子个数区分：

情况一：只有一个质因子（pr.size()==1）
k 只有一个质因子 pr[0]。因为只能用这一个质数组合，能表示的只能是它的倍数。所以判断 n % pr[0] == 0
情况二：两个质因子（pr.size()==2
两个质因子 x（小）和 y（大），问题变成：判断 n 能否写成 ax + by（a,b ≥ 0 整数）‍。

这是经典"两个数能否凑成目标"问题，解法是关键推导：

找 mn = y^(-1) mod x（即满足 mn*y ≡ 1 (mod x) 的那个数），用快速幂 y^(x-2) mod x（费马小定理，x 是质数）。
令 resid = (n mod x) * mn mod x，这样 resid*y ≡ n (mod x)，且 resid < x。
最小能整除 x 同余类里、"用 y 的个数最少、成本最小"的表示是 resid*y（因为要保证 b = resid 满足 0 ≤ resid，且这是该同余类中能由整数个 y 构成的最小值）。
若 n ≥ resid*y，则剩余 n - resid*y 是 x 的倍数（因为两者同余 mod x），可用 x 补足 → YES；否则 NO。
这就是"模最小质因子 + 逆元"的经典判定
情况三：≥3 个质因子（else，用同余最短路）
质因子 ≥ 3 个，用同余最短路（Dijkstra on residues mod x）‍：

取最小质因子 x = pr[0] 作为模数。
以"除以 x 的余数"为节点（0..x-1），用其余质因子（pr[1..] 共 ≥2 个）做加减转移：从余数 cur 加一个 pr[i] 得到新余数 (cur+pr[i])%x，代价为 pr[i]。
Dijkstra 求 dis[r] = 凑出满足"≡ r (mod x)"的数的"最小数值"。
关键性质：若某个余数 r 有 dis[r]（即最该余类里能凑出的最小数），那么该余类中任何 ≥ dis[r] 且同余的数都能被凑出（因为可以再加 x 的整数倍）。
因此判断 n ≥ dis[n mod x] → YES，否则 NO。
dis[0] = 0：余数 0 的最小可凑数为 0（不加任何质因子）。其余初始为无穷大（memset(dis,63,...)）。
为什么 M 要 1e5？ dis 数组下标最大是 x-1，若 k 的最大质因子较小、x 也较小，足够；M=1e5 为边界安全值（x 是质因子，若 k≤1e5，则 x 也 ≤1e5）。严格来说应保证 M > 最大可能的 x
按输入顺序输出每个查询的答案。res[i] 若为 1 输出 YES，0 输出 NO。未处理的（k=1）默认 0 → NO
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define li pair<ll, int>//"距离 + 节点编号"，用于 Dijkstra 堆
using namespace std;

constexpr int N = 1e4, M = 1e5, L = 3.163e7;

int ksm(int x, int e, int mod) {
    int ret = 1;
    for (; e; e>>=1,x=1ll*x*x%mod)
        if (e&1) ret=1ll*ret*x%mod;
    return ret;
}

int vis[L+5], pri[L/8+5], cnt;
void sieve(int n) {
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) pri[++cnt] = i;
        for (int j = 1; j <= cnt && pri[j]*i <= n; j++) {
            vis[pri[j]*i] = 1;
            if (i%pri[j] == 0) break;
        }
    }
}

vector<ll> dec(ll v) {
    vector<ll> ret;
    for (int i = 1; i <= cnt; i++) if (v%pri[i] == 0) {
        ret.push_back(pri[i]);
        while (v%pri[i] == 0) v /= pri[i];
    }
    if (v > 1) ret.push_back(v);
    return ret;
}

int q, res[N+5];
map<ll, vector<li>> mp;
ll dis[M+5];
int main() {
    fast;
    sieve(L); cin >> q;
    for (int i = 1; i <= q; i++) {
        ll n, k; cin >> n >> k;
        if (k != 1) mp[k].emplace_back(n,i);
    }
    for (auto it : mp) {
        ll v = it.first; auto qv = it.second;
        vector<ll> pr = dec(v);
        if (pr.size() == 1) {
            for (auto p : qv)
                res[p.second] = (p.first%pr[0]==0);
        } else if (pr.size() == 2) {
            ll x = pr[0], y = pr[1], ivy = ksm(y%x, x-2, x);
            for (auto p : qv) {
                int mn = 1ll*(p.first%x)*ivy%x;
                res[p.second] = p.first>=1ll*mn*y;
            }
        } else {
            int x = pr[0]; memset(dis, 63, sizeof(dis)); dis[0] = 0;
            priority_queue<li, vector<li>, greater<>> pq; pq.emplace(0,0);
            while (!pq.empty()) {
                auto p = pq.top(); pq.pop();
                int cur = p.second;
                for (int i = 1; i < pr.size(); i++)
                    if (dis[(cur+pr[i])%x] > dis[cur] + pr[i]) {
                        dis[(cur+pr[i])%x] = dis[cur] + pr[i];
                        pq.emplace(dis[(cur+pr[i])%x], (cur+pr[i])%x);
                    }
            }
            for (auto p : qv)
                res[p.second] = p.first >= dis[p.first%x];
        }
    }
    for (int i = 1; i <= q; i++) printf("%s\n", res[i]?"YES":"NO");
    return 0;
}