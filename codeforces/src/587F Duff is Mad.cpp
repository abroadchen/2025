//
// Created by Psy.C on 2026/3/18.
//
/**
tr[M][26]: Trie树，26个字母
tot: 节点总数
v[M]: 每个节点的计数
b[N]: 每个字符串在Trie树中的结束节点
insert(): 在指定根节点处插入字符串s，u是字符串编号
get_fail(): 构建AC自动机的fail指针
BFS遍历建立fail指针
v[u] += v[f]: 传递匹配计数
build(): 构建线段树
为每个线段树节点建立Trie树
递归构建左右子树
pre(): 对每个线段树节点构建AC自动机
递归处理子节点
query(): 查询区间[l,r]内有多少个字符串匹配s[k]
如果完全覆盖，直接在当前Trie树上匹配
否则递归查询左右子树
dfs(): 在fail树上统计每个节点的子树和

长度≥505的字符串放入特殊处理数组
对长字符串预处理
在Trie树上标记匹配位置
用DFS统计子树和
计算前缀和

如果查询的是长字符串，使用预处理数组
否则在线段树上查询

 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 1e5+5, M = 1450005;

struct node { int nxt, to; } e[N];
struct tree { int l, r, mid, rt; } t[N<<2];

int cnt, head[N];
void add(int x, int y) {
    e[++cnt] = {head[x], y}, head[x] = cnt;
}

int tr[M][26], tot = 1, v[M], b[N];
void insert(string& s, int rt, int u) {
    int root = rt, y, len = s.length();
    for (int i = 0; i < len; ++i) {
        y = s[i] - 'a';
        if (!tr[root][y]) tr[root][y] = ++tot;
        root = tr[root][y];
    }
    v[root]++;
    if (rt == 1) b[u] = root;
}

int l, r, q[N], fail[M];
void get_fail(int rt) {
    for (int i = 0; i < 26; ++i) tr[0][i] = rt;
    l = 1, r = 1; q[l] = rt;
    while (l <= r) {
        int u = q[l], f = fail[u]; l++; v[u] += v[f];
        for (int i = 0; i < 26; ++i) {
            int j = tr[u][i];
            if (!j) { tr[u][i] = tr[f][i]; continue; }
            fail[j] = tr[f][i];
            q[++r] = j;
        }
    }
}

string s[N];
void build(int id, int l, int r) {
    t[id].l = l, t[id].r = r, t[id].mid = (l + r) / 2;
    t[id].rt = ++tot;
    for (int i = l; i <= r; ++i) insert(s[i], t[id].rt, i);
    if (l == r) return;
    int mid = (l + r) / 2;
    build(id<<1, l, mid); build(id<<1|1, mid+1, r);
}

void pre(int id) {
    get_fail(t[id].rt);
    if (t[id].l == t[id].r) return;
    pre(id<<1); pre(id<<1|1);
}

int query(int id, int l, int r, int k) {
    if (t[id].l >= l && t[id].r <= r) {
        int u = t[id].rt, len = s[k].length(), sum = 0;
        for (int j = 0; j < len; ++j) {
            u = tr[u][s[k][j] - 'a'];
            sum += v[u];
        }
        return sum;
    }
    int sum = 0;
    if (l <= t[id].mid) sum += query(id<<1, l, r, k);
    if (r > t[id].mid) sum += query(id<<1|1, l, r, k);
    return sum;
}

int c[N];
void dfs(int u) {
    for (int i = head[u]; i; i = e[i].nxt) {
        int j = e[i].to; dfs(j);
        c[u] += c[j];
    }
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

inline string rd_str() {
    char ch=getchar(); string str="";
    while (!((ch>='a')&&(ch<='z'))) ch=getchar();
    while ((ch>='a')&&(ch<='z')) str+=ch,ch=getchar();
    return str;
}

template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}


int n, m, sn, bk[N], sc;
string ls[106];
ll a[N][106];
int main() {
    n = rd(), m = rd(); sn = 505;
    for (int i = 1; i <= n; ++i) {
        s[i] = rd_str(); insert(s[i], 1, i);
        if (s[i].length() >= sn) {
            bk[i] = ++sc;
            ls[sc] = s[i];
        }
    }
    get_fail(1);
    for (int i = 2; i <= tot; ++i) add(fail[i], i);
    for (int i = 1; i <= sc; ++i) {
        int u = 1, len = ls[i].length();
        memset(c, 0, sizeof(c));
        for (int j = 0; j < len; ++j) {
            u = tr[u][ls[i][j] - 'a'];
            c[u]++;
        }
        dfs(1);
        for (int j = 1; j <= n; ++j)
            a[j][i] = a[j-1][i] + c[b[j]];
    }
    build(1, 1, n); pre(1);
    while (m--) {
        int x = rd(), y = rd(), z = rd();
        write(bk[z] ? a[y][bk[z]] - a[x-1][bk[z]] : query(1, x, y, z));
        putchar('\n');
    }
    return 0;
}