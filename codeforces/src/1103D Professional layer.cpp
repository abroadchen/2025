//
// Created by Psy.C on 2026/11/20.
//

/**
真正学会的起点..
结构体 node 存每个数的值 a 与代价 c，数组 p 存 n 个
递归求最大公约数，欧几里得算法
f[i][j]：做了 i 次选取后，质因子被覆盖情况为 j（状压）时的最小总代价。12 表示质因子数上限约 12（1e6 内最多约 7 个不同质因子，取 12 宽裕）。
m：不同质因子个数。
lim：上限（所求目标值）。
mp：键为"该数含有的、属于 target 因子集合的那部分积"，值为对应代价列表。
fac：res 的所有不同质因子集合
sizeof(f) 以字节单位，memset(f, 2, ...) —— 注意这里 2 是字节填充，会把每个 long long 填成 0x0202...（十六进制 0x0202020202020202），即一个极大值（约 1.4e17）。后面 <= inf 判断当"已可达"处理不太准，但实际用 inf 比较……细看：
实际上 f 里存的是"已达，则费用"，初始填 0x02… 为极大值，表示不可达；f[0][0]=0 表示 "0 次选取、未覆盖任何因子" 费用为 0
遍历每个不同的"因子积"桶 v：
x = v.first：该桶代表的一整块质因子积。
v.second：该桶下的代价候选列表，升序排序（贪心优先用代价小的）。
若候选数多于 m，只保留前 m 个（最便宜的），因为每个状态最多被转移 m 次，多余没用
预计算 mul[i]：对每个状压 i（表示选了哪些质因子），算出 x 中被 i 选中质因子的那部分乘积。
tmp = x，遍历质因子 j，若 i 包含 j，则不断把 j 从 tmp 里乘进 tot。
即 mul[i] = "取出 x 中 i 所指质因子之积"
对每个候选代价 y（已升序）：
从大到小遍历已用次数 i（per，避免同一桶重复叠加同一件——保证 0/1 背包性质），对所有已覆盖状态 j 做转移：
C = (1<<m)-1-j：j 的补集，即尚未覆盖的质因子位。
枚举补集的子集 k（k=(k-1)&C），若 mul[k] <= lim（该组合不大于上限），则尝试转移：选这个候选，状态从 (i,j) 变到 (i+1, j|k)，代价 +y，取更小。
flg=1 记录有更新。
若这一轮没有任何状态被更新（!flg），说明当前桶后面的更大代价没用，break 提前结束（剪枝）。
整体是分组背包：每个桶是一组，组内候选只能选一件（因 per 倒序保证不会重复自叠），用 j|k 合并覆盖位

读入 n、lim，读入 n 个 a[i] 并边读边累加 res = gcd(res, a[i])。
再读入 n 个代价 c[i]。（注意这里读入是分两轮的，先全部 a 再全部 c，需输入格式为：一行 a……然后一行 c……）
若 res == 1（所有数的 gcd 为 1，质因子集合为空），则无需任何操作，最小代价为 0，直接输出 0 结束。
对 res 做质因数分解，把不同质因子存进 fac（去重：每次 while 除尽，故不重复）。
从 2 试到 N-5；当 i > res 直接退出（res 已变小）。若最后 res 还 >1，则它本身是质因子，push 进去。
质因子个数。
对每个数 p[i].a，把其中属于 fac 质因子集合的部分提取出来：
x 累乘该数含有的、属于 target 因子的积；
同时 p[i].a /= fac[j] 逐位除尽（去掉这些因子）。
所得 x 作为桶键，把代价 c 塞进 mp[x]。这样每个数按"覆盖到的因子积"分桶。
跑核心背包 DP。
目标是覆盖全部 m 个质因子（状态 (1<<m)-1）。
枚举用了 i 次选取的情况，取 f[i][full] * i 的最小值 —— 这里乘 i 是题目要求（可能是"每次选取贡献可计算多次"，如数组循环 cost 与次数成正比，或题意限定每轮代价放大）。
若最小 ans > inf，说明无解，输出 -1；否则输出 ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i = j; i <= k; ++i)
#define per(i,j,k) for (int i = j; i >= k; --i)
#define int long long
#define vi vector<int>
using namespace std;

constexpr int N = 1e6+5, inf = 1e13;

struct node { int a, c; } p[N];

inline int gcd(int x, int y) { return !y ? x : gcd(y, x % y); }

int f[12][1<<12], m, lim;
map<int,vi> mp;
vi fac;
void solve() {
    memset(f,2,sizeof(f)); f[0][0] = 0;
    for (auto v : mp) {
        int x = v.first; vi mul; ranges::sort(v.second);
        if (v.second.size() > m) v.second.resize(m);
        rep(i,0,(1<<m)-1) {
            int tot = 1, tmp = x;
            rep(j,0,m-1) if (i&(1<<j))
                while (!(tmp%fac[j])) tot *= fac[j], tmp/=fac[j];
            mul.push_back(tot);
        }
        for (auto y : v.second) {
            bool flg = 0;
            per(i,m-1,0) rep(j,0,(1<<m)-1) {
                if (f[i][j] <= inf) {
                    int C = (1<<m)-1-j;
                    for (int k = C; k; k=(k-1)&C) if (mul[k] <= lim)
                        if (f[i+1][j|k] > f[i][j]+y)
                            f[i+1][j|k] = f[i][j]+y, flg = 1;
                }
            }
            if (!flg) break;
        }
    }
}

int n, res, ans = 1e15;
signed main() {
    fast;
    cin >> n >> lim;
    rep(i,1,n) cin >> p[i].a, res = gcd(res, p[i].a);
    rep(i,1,n) cin >> p[i].c;
    if (!(res-1)) return cout << "0", 0;
    rep(i,2,N-5) {
        if (i <= res && !(res%i)) {
            fac.push_back(i);
            while (!(res%i)) res/=i;
        } else if (i > res) break;
    }
    if (res-1) fac.push_back(res);
    m = fac.size();
    rep(i,1,n) {
        int x = 1;
        rep(j,0,m-1) while (!(p[i].a%fac[j])) x *= fac[j], p[i].a /= fac[j];
        mp[x].push_back(p[i].c);
    }
    solve();
    rep(i,1,m) ans = min(ans, f[i][(1<<m)-1]*i);
    if (ans > inf) cout << "-1"; else cout << ans;
    return 0;
}