//
// Created by Psy.C on 2026/9/16.
//
/**
base = 13131：哈希基数（一个大质数）。
G[N]：原无向图邻接表
先把点 x 的邻居列表排序（保证邻居顺序不影响哈希，即"无序集合"编码成有序结果）。
然后用进制哈希逐项累加：hash = hash*base + 邻居编号。
返回该点的"邻居结构指纹"。两点指纹相同 ⇒ 它们互为结构等价（邻居集合一样，这里含自环——见下）。
注：读入时 G[i].push_back(i) 把每个点自身也加进自己列表（相当于加了自环），所以哈希把"点自己是否出现在邻居里"也算进去，用来区分有自环/无自环。这是去重标记的技巧
读入点数、边数。
每个点先放入自身（自环）。
读入无向边
每个点算邻居哈希 h[i]。
用下标数组 idx 按 h 值排序
因为已按 h 排序，相邻哈希相等 ⇒ 属于同一等价类：fa[x] = fa[y]（沿用前者代表元）。
不相等则自成代表元：fa[x] = x。
于是 fa[i] 指向点 i 所在等价类的代表元。
（这里 i=1 时 idx[0] 越界读 0，h[0] 是 0，一般不会与 h[1] 相等，所以 fa[idx[1]]=idx[1]，安全。）
对每条原边 (i,j)，若两端不在同一等价类，则在等价类之间连一条边：F[fa[i]].push_back(fa[j])。
这样得到以"等价类"为节点、连接不同类的边构成的压缩图 F
对每个代表元（等价类），把它的邻居去重。
若某个类度数 >2 → 压缩图不是路径，直接输出 NO 结束。
度数 ≤1 的类是路径的端点，记录其编号到 x。
注意：如果图不连通，会得到多个端点，后面 BFS 只从一个端点起，最终未访问到的点 res 仍是 0——这题假设输入保证可成链（或题意如此）
从端点 x 出发 BFS，给每个等价类打上层号 res（1,2,3,… 沿链递增
打印 YES（表示可成链）。
对每个原始点 i，输出它所属等价类的层号 res[fa[i]]。因为同一个等价类内的点层号相同，所以本质是按"等价类"给每个点一个层标签
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 3e5+5, base = 13131;

vector<int> G[N];
int res[N];
ll get(int x) {
    ranges::sort(G[x]);
    ll res = 0;
    for (int& it : G[x]) res = res*base+it;
    return res;
}

ll h[N];
bool cmp(int a, int b) { return h[a] < h[b]; }

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int idx[N], fa[N];
vector<int> F[N];
queue<int> q;
int main() {
    int n, m; rd(n); rd(m);
    for (int i = 1; i <= n; ++i) G[i].push_back(i);
    for (int i = 1, u, v; i <= m; ++i) {
        rd(u); rd(v);
        G[u].push_back(v); G[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) h[i] = get(i), idx[i] = i;
    sort(idx+1, idx+1+n, cmp);
    for (int i = 1; i <= n; ++i) {
        int x = idx[i], y = idx[i-1];
        fa[x] = h[x] != h[y] ? x : fa[y];
    }
    for (int i = 1; i <= n; ++i)
        for (auto it = G[i].begin(); it != G[i].end(); ++it) {
            int j = *it;
            if (fa[i] != fa[j]) F[fa[i]].push_back(fa[j]);
        }
    int x;
    for (int i = 1; i <= n; ++i) {
        if (fa[i] != i) continue;
        ranges::sort(F[i]);
        F[i].erase(ranges::unique(F[i]).begin(), F[i].end());
        if (F[i].size() > 2) return puts("NO"), 0;
        if (F[i].size() <= 1) x = i;
    }
    q.push(x); res[x] = 1;
    while (!q.empty()) {
        int o = q.front(); q.pop();
        for (auto it = F[o].begin(); it != F[o].end(); ++it)
            if (!res[*it]) q.push(*it), res[*it] = res[o]+1;
    }
    puts("YES");
    for (int i = 1; i <= n; ++i) printf("%d ", res[fa[i]]);
    puts("");
    return 0;
}