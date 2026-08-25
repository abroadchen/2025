//
// Created by Psy.C on 2026/5/9.
//
///时间复杂度：O(n²·∑len_i)，空间复杂度：O(n·∑len_i)
#include <bits/stdc++.h>
#define ll long long
using namespace std;
///字符串前缀哈希值
void init(int *h, const char *s, int base, int mod, int lim) {
    for (int i = 1; i <= lim; ++i)
        h[i] = (1ll*h[i-1]*base + s[i] - 'a') % mod;
}
///[l,r]区间子串的哈希值
int get(const int *h, const int *pw, int mod, int l, int r) {
    return (h[r] - 1ll*pw[r-l+1]*h[l-1]%mod + mod) % mod;
}
///len:字符串长度，h1/h2:双哈希数组，pw1/pw2:幂次数组
constexpr int maxn = 1e5+7, m1 = 998244353, m2 = 1e9+7, lim = 1e5, b1 = 17, b2 = 23;
int len[35], h1[35][maxn], pw1[maxn], h2[35][maxn], pw2[maxn];
int match(int i, int j, int k) {///字符串i从位置j开始的后缀是否与字符串k匹配
    int L = min(len[i]-j+1, len[k]);//匹配长度
    //双哈希验证
    if (get(h1[i], pw1, m1, j, j+L-1) == get(h1[k], pw1, m1, 1, L) &&
        get(h2[i], pw2, m2, j, j+L-1) == get(h2[k], pw2, m2, 1, L))
        return true;
    return false;
}
///sr:超级源点，id[i][j]:字符串i的第j个位置的节点ID
int sr, id[35][maxn];
vector<int> ch[maxn];///邻接表存储图
void link(int i, int j, int k, int l) {//在图中添加边
    if (k == sr) { ch[id[i][j]].push_back(sr); return; }//连接到超级源点
    ch[id[i][j]].push_back(id[k][l]);//连接到其他节点
}
///flag:是否有环，ins:在栈中标记，vis:访问标记
int flag, ins[maxn], vis[maxn];
void dfs(int x) {//检测环
    if (flag) return;
    ins[x] = vis[x] = 1;//标记当前节点正在访问
    for (int y : ch[x]) {
        if (ins[y]) { flag = 1; return; }//发现后向边，存在环
        if (!vis[y]) dfs(y);//继续DFS
    }
    ins[x] = 0;//退出时清除栈标记
}
///tl:节点总数，n:字符串数量
int tl, n;
int ok(int l, int r) {//区间[l,r]内的字符串是否存在环
    memset(vis, 0, sizeof(vis));
    memset(ins, 0, sizeof(ins));
    for (int i = 1; i <= tl; ++i) ch[i].clear();//清空图
    ch[sr].clear(); flag = 0;//清空超级源点的边，重置flag
    //构建图的边
    for (int i = l; i <= r; ++i)
        for (int j = 1; j <= len[i]; ++j)
            for (int k = l; k <= r; ++k) {
                if (len[i]-j+1 < len[k])//当前后缀长度小于匹配串
                    if (match(i, j, k)) link(i, j, k, len[i]-j+1+1);
                if (len[i]-j+1 == len[k]) {
                    if (j == 1 && len[i] == len[k]) continue;//跳过自身匹配
                    if (match(i, j, k)) link(i, j, sr, 0);
                }
                if (len[i]-j+1 > len[k])
                    if (match(i, j, k)) link(i, j, i, j+len[k]);
            }
    //添加超级源点到各字符串首字符的边
    for (int i = 1; i <= n; ++i) ch[sr].push_back(id[i][1]);
    for (int i = 1; i <= tl+1; ++i) dfs(i);//对所有节点进行DFS检测环
    return flag^1;//返回是否无环（1为无环，0为有环）
}

char s[35][maxn];
int ans;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s[i] + 1);
        len[i] = strlen(s[i] + 1);
        for (int j = 1; j <= len[i]; ++j)
            id[i][j] = ++tl;//为每个字符位置分配唯一ID
    }
    sr = tl + 1;//设置超级源点ID
    int r = 0; pw1[0] = pw2[0] = 1;
    for (int i = 1; i <= lim; ++i) pw1[i] = 1ll*pw1[i-1]*b1%m1;
    for (int i = 1; i <= lim; ++i) pw2[i] = 1ll*pw2[i-1]*b2%m2;
    for (int i = 1; i <= n; ++i) {//预计算所有字符串的哈希值
        init(h1[i], s[i], b1, m1, lim);
        init(h2[i], s[i], b2, m2, lim);
    }
    for (int l = 1; l <= n; ++l) {//枚举左端点
        if (r < l - 1) r = l - 1;
        while (r < n && ok(l, r + 1)) r++;//扩展右端点直到出现环
        ans += r - l + 1;//累加以l为左端点的有效区间数量
    }
    printf("%d", ans);
    return 0;
}