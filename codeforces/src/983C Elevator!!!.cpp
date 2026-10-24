//
// Created by Psy.C on 2026/10/24.
//

/**
真正学会的起点..
N = 1e4：DP 的状态上限（掩码状态空间）。
M = 2e3+5：数组大小。
inf = 1e9：较大值，用于求最小值时的初始值。
INF = 0x3f3f3f3f：约 10 亿，用于 memset 填充字节，表示"不可达/无穷大"
msk 是一个"4 位十进制数"，每一位代表一个槽位的数值。
返回第 p（0-3）位的数字：p=0 取个位，p=1 取十位，p=2 取百位，p=3 取千位
sub（0-15）是 4 位的位掩码，表示选择掩码中的哪些位。
对每一位：若 sub 对应位为 1，则把 msk 中该位的数字取出来，乘以该位的权重（1/10/100/1000）加到 ans 上。
如果某一位 sub 要求取，但 msk 对应位是 0（为空），返回 -1 表示非法。
返回所选位拼接成的数值
从低位到高位找第一个"空的槽位"（值为 0 的位置）。
返回该位置索引；若全满返回 -1
在 msk 的第 p 个空位上写入 to（此时该位原为 0，相加即写入）
dfs(x, sum, st, gl)：
x：已处理的元素个数。
sum：已累计的移动代价。
st：当前指针所在位置。
gl：目标位置（固定）。
当 x == v.size()（所有元素都处理完）时，把 sum + |st - gl|（最后把指针移动到目标点的代价）纳入 ans 最小值。
否则枚举每个未访问的元素 v[i]，把指针从 st 移动到 v[i]（代价 |v[i]-st|），递归处理。
本质：对集合 v 做排列，求一条从起点 x（初始位置 st）依次访问完所有点、最后到终点 gl 的最短路径（代价为曼哈顿一维距离之和
dp 初始化为 0x3f（无穷大）。
读入 n 对 (a[i], b[i])。
三重循环预处理 w[x][y][g]：
对每个起点 x（1-9）、终点 y（1-9）、状态掩码 g（0-9999）。
把掩码 g 中所有非零的数字收集到 v 中。
用 DFS 求"从 x 出发，访问 v 中所有数字，最后到 y"的最小代价。
w[x][y][g] = 从起点 x 到终点 y，需要顺路访问掩码 g 中所有数字的最小路径代价
a[0] = 1：初始指针位置是 1（起始数字键）。
dp[0][0] = 0：处理 0 个数、掩码为 0 时代价为 0。
外层 i：表示处理到第 i 个数。
外层 j：上一个状态 dp[i-1][j] 的掩码（已积累但尚未消耗的数字）。
若 dp[i-1][j] 不可达则跳过。
内层 k（0-15）：枚举这次要"消耗"的掩码 j 的某个子集。
x = getsub(j,k)：取出子集 k，得到要顺路访问的数字组合；若某位为空则 -1，跳过。
pos = getmn(j-x)：找到消耗后剩下的掩码 j-x 中第一个空位。
y = j - x 后 merge(y, pos, b[i])：把当前数 b[i] 写入这个空位。
转移：dp[i][y] = min(dp[i][y], dp[i-1][j] + w[a[i-1]][a[i]][x])
即在从 a[i-1] 到 a[i] 的移动过程中，顺路消耗掩码子集 x 里的数字，代价为 w[a[i-1]][a[i]][x]，并把 b[i] 存入某个空位得到新掩码 y。
DP 状态含义（推断）：dp[i][j] 表示处理完第 i 个数、当前还没有"消耗"的数字集合为掩码 j 的最小代价。数字可以缓存（掩码）以后再顺路访问
最后枚举所有可能的结束掩码 j 和结束位置 k（1-9）：
dp[n][j]：处理完 n 个数后的最小代价。
w[a[n]][k][j]：最后从 a[n] 出发，顺路访问完掩码 j 里所有数字，最终停在 k 的代价。
取最小值 res。
输出 res + 2*n：
额外的 2*n 是每个数本身需要付出的固定代价
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
using namespace std;

constexpr int N = 1e4, M = 2e3+5, inf = 1e9, INF = 0x3f3f3f3f;

int get(int msk, int p) {
    if (p == 0) return msk%10;
    if (p == 1) return msk/10%10;
    if (p == 2) return msk/100%10;
    return msk/1000;
}

int getsub(int msk, int sub) {
    int ans = 0;
    if (sub&1) {
        if (!(msk%10)) return -1;
        ans += msk%10;
    }
    if ((sub>>1)&1) {
        if (!(msk/10%10)) return -1;
        ans += msk/10%10*10;
    }
    if ((sub>>2)&1) {
        if (!(msk/100%10)) return -1;
        ans += msk/100%10*100;
    }
    if ((sub>>3)&1) {
        if (!(msk/1000)) return -1;
        ans += msk/1000*1000;
    }
    return ans;
}
int getmn(int msk) {
    if (!(msk%10)) return 0;
    if (!(msk/10%10)) return 1;
    if (!(msk/100%10)) return 2;
    if (!(msk/1000)) return 3;
    return -1;
}
int merge(int msk, int p, int to) {
    if (p == 0) return msk+to;
    if (p == 1) return msk+to*10;
    if (p == 2) return msk+to*100;
    return msk+to*1000;
}

int ans;
bool vis[5];
vector<int> v;
void dfs(int x, int sum, int st, int gl) {
    if (x == v.size())
        return ans = min(ans, sum+abs(st-gl)), void();
    rep(i,0,v.size()-1) {
        if (vis[i]) continue;
        vis[i] = 1;
        dfs(x+1, sum+abs(v[i]-st),  v[i], gl);
        vis[i] = 0;
    }
}

int dp[M][N], n, a[M], b[M], w[10][10][N];
int main() {
    fast;
    memset(dp, 0x3f, sizeof(dp)); cin >> n;
    rep(i,1,n) cin >> a[i] >> b[i];
    rep(x,1,9) rep(y,1,9) rep(g,0,N-1) {
        v.clear();
        rep(p,0,3) if (get(g,p) != 0) v.push_back(get(g,p));
        ans = inf;
        dfs(0,0,x,y);
        w[x][y][g] = ans;
    }
    a[0] = 1; dp[0][0] = 0;
    rep(i,1,n) rep(j,0,N-1) {
        if (dp[i-1][j] == INF) continue;
        rep(k,0,15) {
            int x = getsub(j,k);
            if (x == -1) continue;
            int pos = getmn(j-x);
            if (pos == -1) continue;
            int y = j-x;
            y = merge(y, pos, b[i]);
            dp[i][y] = min(dp[i][y], dp[i-1][j]+w[a[i-1]][a[i]][x]);
        }
    }
    int res = inf;
    rep(j,0,N-1) rep(k,1,9) res = min(res, dp[n][j]+w[a[n]][k][j]);
    cout << res+2*n << '\n';
    return 0;
}