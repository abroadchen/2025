//
// Created by Psy.C on 2026/10/25.
//

/**
真正学会的起点..
N=210：点规模上限。
n：实际点数。
mtx：n×n 的实数矩阵，g 存储矩阵元素。
operator*：标准矩阵乘法 C = A × B，c[i][j] += g[i][k]*a.g[k][j]。因为矩阵是对称的还是转移矩阵，乘法按普通矩阵乘。
f[15]：预处理倍增矩阵。f[0] 是单步转移矩阵，f[i] = f[i-1]²（f[1] = f[0]²，f[2] = f[0]⁴，…），用于快速求 m 步转移矩阵。14 个倍增层可覆盖 m ≤ 2^14 的步数
把方向向量 (dx, dy) 标准化成"方向描述符"：

若 dx == 0（竖直方向）→ 返回 (0,1)。
若 dy == 0（水平方向）→ 返回 (1,0)。
否则约分（除以 gcd），并保证 dx>0（即分子非负），这样 (1,2) 和 (-1,-2) 视为同一方向。
作用：对任意两点，用它们的位置差 方向（斜率）来分组，同一个方向上的点属于同一"射线组"
x[], y[]：各点的坐标。
flg：内部辅助标志（判断某直线组是否构成"闭环"）。
ln：记录的"特殊直线组"（后面求概率均值的目标集合）
对每个点 p：

按方向分组：遍历其他所有点 i，计算从 p 到 i 的方向向量，用 fix 标准化后作为 key，把 i 塞入对应方向组 cnt。
sz = cnt.size()：p 有多少个不同方向。
遍历每个方向组 val（该组包含与 p 同方向的点）：
val.push_back(p)：把 p 自己加进组（因为同一方向上的点会形成链）。
flg=1（先假设是闭环）。
对组内每个 v：f[0].g[p][v] += 1./val.size()/sz。
转移概率：从 p 跳到 v 的概率 = 1/组大小（在组内均匀）再 /方向数（先均匀选方向）。即：先等概率选一个方向（1/sz），再在该方向上等概率选一个目标（1/val.size()）。
if (v < p) flg = 0：若组内存在编号小于 p 的点，说明该组不是严格"递增朝向"的闭环，则 flg 置0。
若 flg==1（该方向组内所有点编号都 ≥ p，构成一个严格递增的射线链）→ 把这个组记录进 ln（这些是"特殊直线组"，题目要求计算这些组上的平均概率）。
注意：1./val.size()/sz 是浮点除法，1. 保证 double

读点数 n 和每个点坐标。
对每个点调用 add(i)，构建单步转移矩阵 f[0] 并记录特殊直线组 ln
f[1] = f[0]*f[0]（2步转移），f[2] = f[1]*f[1]（4步），…，f[14]（2^14 步）。
这就是矩阵快速幂：要算 m 步转移矩阵 = 分解 m 的二进制，把对应 f[i] 相乘
读询问数 q。
每个询问：起始点 t（减1转0基）、步数 m（减1，注意这里是 -1）
初始化概率分布 pr：全部0，pr[t]=1（初始在点 t）。
遍历 m 的每个二进制位 1<<i，若该位为1，则把 pr 乘上 f[i]（对应 2^i 步转移矩阵）：
先把 pr 存到 tmp，pr 清零。
pr[j] += tmp[k]*f[i].g[j][k]：行向量 × 转移矩阵，得到新的 pr（新概率分布）。
循环结束后，pr[j] = 从 t 出发走 m 步后落在点 j 的概率。
这里是行向量右乘转移矩阵方式：pr_new[j] = Σ_k pr_old[k] * M[k][j]
ans=0（初始最大均值）。
遍历记录在 ln 中的每个特殊直线组 l：
o：该组内所有点被访问概率之和 sum(pr[u])。
o/l.size()：该组上概率的平均值。
ans = max(ans, …)：取所有组中的最大值。
输出 ans，12位小数。
因此每个询问的答案为：走 m 步后，所有"特殊直线组"中"组内概率平均值"的最大值。
*/
#include <bits/stdc++.h>
#define rep(i,n) for (int i=0; i<(n); i++)
#define ii pair<int,int>
#define db double
using namespace std;

constexpr int N = 210;

int n;
struct mtx {
    db g[N][N];
    mtx operator*(const mtx &a) const {
        mtx c{}; memset(c.g, 0, sizeof(c.g));
        rep(i,n) rep(j,n) rep(k,n) c.g[i][j] += g[i][k]*a.g[k][j];
        return c;
    }
} f[15];

ii fix(ii a) {
    if (a.first == 0) return {0, 1};
    if (a.second == 0) return {1, 0};
    int d = __gcd(a.first, a.second); a.first/=d, a.second/=d;
    if (a.first < 0) a.first *= -1, a.second *= -1;
    return a;
}

int x[N], y[N], flg;
vector<vector<int>> ln;
void add(int p) {
    map<ii, vector<int>> cnt;
    rep(i,n) if (i != p) {
        int dx = x[i] - x[p], dy = y[i] - y[p];
        cnt[fix({dx,dy})].push_back(i);
    }
    int sz = cnt.size();
    for (auto val: cnt | views::values) {
        val.push_back(p), flg = 1;
        for (auto v : val) {
            f[0].g[p][v] += 1./val.size()/sz;
            if (v < p) flg = 0;
        }
        if (flg) ln.push_back(val);
    }
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

db pr[N], tmp[N], ans;
int main() {
    n = rd();
    rep(i,n) x[i] = rd(), y[i] = rd();
    rep(i,n) add(i);
    for (int i = 1; i <= 14; i++) f[i] = f[i-1]*f[i-1];
    for (int q = rd(); q; q--) {
        int t = rd()-1, m = rd()-1;
        rep(i,n) pr[i] = 0; pr[t] = 1.;
        rep(i,15) if (m&(1<<i)) {
            rep(j,n) tmp[j] = pr[j], pr[j] = 0;
            rep(j,n) rep(k,n) pr[j] += tmp[k]*f[i].g[j][k];
        }
        ans = 0;
        for (const auto& l : ln) {
            db o = 0;
            for (auto u : l) o += pr[u];
            ans = max(ans, o/l.size());
        }
        printf("%.12f\n", ans);
    }
    return 0;
}