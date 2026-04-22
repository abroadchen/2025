//
// Created by Psy.C on 2026/4/21.
//
/**
L[i], R[i]：第i个位置的左右属性值
cnt[6]：统计不同类型元素的个数
n：输入大小
p[2][N]：两个排列数组
pos[2][N]：值到位置的映射
读入两个排列：p[0]和p[1]
建立值到位置的映射：pos[t][value] = position
初始化并查集：每个节点独立
设置L,R值：L[i]=p[0][i], R[i]=p[1][i]
合并相同元素：如果元素i在两个排列中都存在，则合并其位置

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int mod = 998244353, N = 251;

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int L[N], R[N], cnt[6];
void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) {//已经在同一集合
        L[x] = R[x] = -1;//标记为无效
        ++cnt[4];//增加冲突计数
        return;
    }
    R[x] = R[y], fa[y] = x;//合并两个集合
}

int n, p[2][N], pos[2][N], dp[N];
signed main() {
    fast;
    cin >> n;
    for (int t = 0; t < 2; ++t)
        for (int i = 1; i <= n; ++i)
            cin >> p[t][i], pos[t][p[t][i]] = i;
    for (int i = 1; i <= n; ++i)
        fa[i] = i, L[i] = p[0][i], R[i] = p[1][i];
    for (int i = 1; i <= n; ++i)
        if (pos[0][i] && pos[1][i])
            merge(pos[1][i], pos[0][i]);
    for (int i = 1; i <= n; ++i)
        if (!pos[0][i] && !pos[1][i]) ++cnt[5];//两个排列中都不存在的元素
    for (int i = 1; i <= n; ++i) if (find(i) == i && L[i] != -1) {
        if (L[i] && R[i]) ++cnt[0];//两类属性都存在
        else if (L[i]) ++cnt[1];//只有左属性
        else if (R[i]) ++cnt[2];//只有右属性
        else ++cnt[3];//都不存在（但不是两个排列中都没有）
    }
    dp[cnt[4]] = 1;
    for (int i = 1; i <= cnt[5]; ++i)
        dp[cnt[4]] = dp[cnt[4]]*i%mod;//用冲突数量和完全不存在的元素初始化
    //处理类型3的元素（L[i]=0, R[i]=0）
    for (int i = 0; i < cnt[3]; ++i)
        for (int j = n; j >= 0; --j)
            dp[j] = (dp[j]*i + (j?dp[j-1]:0))%mod;
    //处理类型0的元素（L[i]≠0, R[i]≠0）
    for (int i = 0; i < cnt[0]; ++i)
        for (int j = n; j >= 0; --j)
            dp[j] = dp[j]*(cnt[3]-i)%mod;
    //处理类型1的元素（只有L[i]≠0）
    for (int i = 0; i < cnt[1]; ++i)
        for (int j = n; j >= 0; --j)
            dp[j] = (dp[j]*(i+cnt[3])+(j?dp[j-1]:0))%mod;
    //处理类型2的元素（只有R[i]≠0）
    for (int i = 0; i < cnt[2]; ++i)
        for (int j = n; j >= 0; --j)
            dp[j] = (dp[j]*(i+cnt[3])+(j?dp[j-1]:0))%mod;
    for (int i = n; i; --i)
        cout << dp[i] << (i==1 ? '\n' : ' ');//从高到低输出：dp[n], dp[n-1], ..., dp[1]
    return 0;
}