//
// Created by Psy.C on 2025/11/10.
//
/*
*n：节点数，m：边数
f[N]：并查集父节点数组
r[N]：并查集秩（集合大小）数组
dp[N]：动态规划数组
*mp：映射容器，记录每种大小的连通分量个数
it：映射迭代器
 *
*v：最大容量（通常是n）
c：连通分量的大小
k：选择该大小连通分量的个数
 *
*选择 k 个大小为 c 的连通分量（总共 c*k 个节点）
之前状态：需要选择 i - c*k 个节点
*不选择这个组合：dp[i]（保持原值）
选择这个组合：dp[i - c*k] + k（从前一个状态转移而来，加上本次代价）
 *
 *ans-1
*dp[0] = 0;  // 选择0个节点代价为0
// 但实际问题中可能选择0个节点不算有效解
 */
#include <algorithm>
#include <cstdio>
#include <map>
#define rep(i,n) for(int (i)=0;(i)<(n);++(i))
using namespace std;

int read() {
    char c; int f(1);
    while ((c=getchar()) < '0' || c > '9') if (c == '-') f = -1;
    int res = c - '0';
    while ((c=getchar()) >= '0' && c <= '9') res = res * 10 + c - '0';
    return res * f;
}

const int N = 1e5+10, inf = 1<<29;
int n, m, f[N], r[N], dp[N];
map<int, int> mp;
map<int, int>::iterator it;

int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }
void merge(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return;
    if (r[x] <= r[y]) { f[x] = y; r[y] += r[x]; }
    else { f[y] = x; r[x] += r[y]; }
}

void fd(int v, int c, int k) {//动态规划优化函数，类似于多重背包的优化
    for (int i = v; i >= c*k; --i) {
        dp[i] = min(dp[i], dp[i - c*k] + k);
    }
}

bool dfs(int x) {//判断数字是否只由'4'和'7'组成
    if (x % 10 != 4 && x % 10 != 7) return false;
    if (x < 10) return true;
    return dfs(x / 10);
}

int main() {
    n = read(); m = read();
    rep(i,n) { f[i] = i; r[i] = 1; }
    rep(i,m) {//读取m条边并合并对应的节点（注意节点编号从0开始）
        int x = read(), y = read();
        merge(x - 1, y - 1);
    }
    rep(i,n) if (find(i) == i) mp[r[i]]++;//统计每种大小的连通分量个数
    rep(i,n+1) dp[i] = inf; dp[0] = 0;
    for (it = mp.begin(); it != mp.end(); ++it) {
        int sz = it->first, sum = it->second;
        while (sum > 0) {
            fd(n, sz, (sum+1)/2);//二进制优化：O(log sum) 次调用
            sum /= 2;
        }
    }
    int ans(inf);
    rep(i,n+1) if (dfs(i)) ans = min(ans, dp[i]);
    printf("%d\n", ans == inf ? -1 : ans - 1);
    return 0;
}