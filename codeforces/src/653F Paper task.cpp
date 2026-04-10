//
// Created by Psy.C on 2026/4/7.
//
/**
t转移数组(只有'('和')'两种字符)，f后缀链接，len最长串长度，ed结束位置
tn节点总数，lst最后插入的节点
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 5e5+5;
struct node { int t[2], f, len, ed; } a[N<<1];

int tn, lst;
void add(int c) {
    int p = lst, np = ++tn; lst = np;
    a[np].len = a[p].len + 1;//新节点长度+1
    //沿着后缀链接向上更新转移
    for (; p&&!a[p].t[c]; p = a[p].f) a[p].t[c] = np;
    if (!p) a[np].f = 1;//p为空，np的后缀链接指向根
    else {
        int v = a[p].t[c];
        if (a[v].len == a[p].len + 1) a[np].f = v;//直接连接
        else {
            int nv = ++tn; a[nv] = a[v];//复制节点
            a[nv].len = a[p].len + 1;
            for (; p&&a[p].t[c] == v; p = a[p].f) a[p].t[c] = nv;
            a[np].f = a[v].f = nv;//更新后缀链接
        }
    }
}

int lg2[N], t[20][N];
int query(int l, int r) {
    int k = lg2[r-l+1];
    return min(t[k][l], t[k][r-(1<<k)+1]);
}

///g后缀链接树，p按权值分组的结束位置
vector<int> g[N<<1], p[N<<1];
int s[N], n;///s前缀和数组，n字符串长度
ll ans = 0;
void dfs(int u) {
    for (int i = 0; i < g[u].size(); ++i) {
        dfs(g[u][i]);//递归处理子节点
        a[u].ed = a[g[u][i]].ed;//更新结束位置
    }
    int ed = a[u].ed, l = ed-a[u].len+1, sr = ed-a[a[u].f].len, mid, r = sr+1;
    while (l < r) {
        mid = (l+r)>>1;
        if (query(mid, ed) >= s[ed+1]) r = mid;
        else l = mid + 1;
    }
    ans += ranges::upper_bound(p[n+s[ed+1]], sr) - ranges::lower_bound(p[n+s[ed+1]], r);
}

char str[N];
int main() {
    fast;
    scanf("%d%s", &n, str+1);
    //预处理前缀和：'('为-1，')'为+1（这样匹配的括号段和为0）
    for (int i = n; i; --i)
        t[0][i] = s[i] = s[i+1] + (str[i] == '(' ? -1 : 1);
    //按前缀和值分组结束位置
    for (int i = 1; i <= n+1; ++i) p[n+s[i]].push_back(i);
    //预处理lg数组和ST表
    for (int i = 2; i <= n; ++i) lg2[i] = lg2[i>>1]+1;
    for (int j = 1; 1<<j <= n; ++j)
        for (int i = 1; i <= n; ++i)
            t[j][i] = min(t[j-1][i], t[j-1][i+(1<<(j-1))]);
    //构建后缀自动机
    lst = tn = 1;
    for (int i = 1; i <= n; ++i) add(str[i] - '(');
    //设置每个节点的结束位置
    for (int i = 1, x = 1; i <= n; ++i)
        a[x=a[x].t[str[i]-'(']].ed = i;
    //构建后缀链接树
    for (int i = 2; i <= tn; ++i) g[a[i].f].push_back(i);
    dfs(1);
    cout << ans << '\n';
    return 0;
}