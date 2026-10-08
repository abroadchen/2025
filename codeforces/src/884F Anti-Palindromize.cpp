//
// Created by Psy.C on 2026/10/8.
//
/***
e[N][N]：可达的二分图边权矩阵。
vis：本趟增广中是否访问（右侧点）。
pre：增广路径前驱。
sl：松弛值 slack。
mt：右侧点的匹配对象（mt[y] = 左侧点 x）。
wx、wy：左、右两侧顶标（可行顶标，KM 核心）
把前一半与后一半对称位置配对，a[i] 取这对中较大者，并把较大值先计入 ans（作为"必然选中的边"的权值基底）
构图：左右各 n 个点。仅当左侧字符 s[i] 不等于其对称位置字符 s[nn-j+1] 时建边，边权取决于另一侧对称位置的字符是否相等（取 a[nn-i+1] 或 0）
依次对每个左侧点做一次 KM 增广，最终得到最大权完美匹配；wx+wy 之和即为最大匹配权值，加到之前的基座上输出
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 1e3+5, M = N/10+5, inf = 0x3f3f3f3f;

int n, vis[M], pre[M], sl[M], mt[M], wx[M], wy[M], e[N][N];
void bfs(int x) {
    for (int i = 0; i <= n; ++i)
        vis[i] = pre[i] = 0, sl[i] = inf;
    int y = 0, p = 0; mt[y] = x;//把左侧点 x 挂在"虚拟根" y=0 上
    while (mt[y]) {//只要 y 已被匹配，就继续找增广路
        x = mt[y]; vis[y] = 1;
        int mn = inf;
        for (int i = 1; i <= n; ++i) {
            if (vis[i]) continue;
            if (sl[i] > wx[x]+wy[i]-e[x][i])//更新松弛量
                sl[i] = wx[x]+wy[i]-e[x][i], pre[i] = y;
            if (sl[i] < mn) p = i, mn = sl[i];
        }
        for (int i = 0; i <= n; ++i) {//调整顶标
            if (vis[i]) wx[mt[i]] -= mn, wy[i] += mn;
            else sl[i] -= mn;
        }
        y = p;
    }
    while (y) mt[y] = mt[pre[y]], y = pre[y];//沿增广路翻转匹配
}

int nn, s[M], a[M], ans;
signed main() {
    fast;
    cin >> n; nn = n;
    for (int i = 1; i <= n; ++i) {
        char c; cin >> c;
        s[i] = c - 'a' + 1;//读字符串（a..z 映射到 1..26）
    }
    for (int i = 1; i <= n; ++i) cin >> a[i];//读权值
    n>>=1;//n 变为一半
    for (int i = 1; i <= n; ++i) {
        if (a[i] < a[nn-i+1])//取对称位置较大者
            swap(a[i], a[nn-i+1]), swap(s[i], s[nn-i+1]);
        ans += a[i];//先累加所有较大权值
    }
    memset(e, -0x3f, sizeof e);//边权初始为极小
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (s[i] != s[nn-j+1])//左右字符不等才建边
                e[i][j] = s[nn-i+1]==s[nn-j+1]?a[nn-i+1]:0;
    for (int i = 1; i <= n; ++i) bfs(i);//对每个左侧点跑增广，得到完美匹配
    for (int i = 1; i <= n; ++i) ans += wx[i] + wy[i];//加上最大权匹配的顶标和
    cout << ans << '\n';
    return 0;
}