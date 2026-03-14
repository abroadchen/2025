//
// Created by Psy.C on 2026/3/13.
//
/**
mod: 修改记录二维数组
f是树状数组，存储前缀和信息
add函数实现单点更新操作，在位置x处增加y值
sum函数计算从1到x的前缀和
计算区间[l+1, r]的和（注意这里是左开右闭）
get函数通过二分查找找到第x小的元素位置

n: 节点数量
q: 查询数组，存储每个节点对应的查询索引
lb: 存储查询结果的下界
在t2树上进行DFS遍历
对当前节点的修改进行加法操作
如果是叶子节点，则处理查询
递归访问左右子树
撤销修改操作
在t1树上进行第二次DFS遍历
类似于dfs函数，但添加的是size值
计算并存储最终答案

'U': 合并操作，在t1树上创建新节点
'M': 另一种合并操作，在t2树上创建新节点
'A': 添加标记到t1树
'Z': 添加标记到t2树
其他: 查询操作，将查询与节点关联
遍历所有根节点执行两次DFS
输出所有有效答案
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 5e5;

struct node {
    vector<int> fa, l, r, id;
    vector<vector<int>> mod;
    void init(int x) {
        fa.assign(2*x-1, -1);
        l.assign(2*x-1, -1); r.assign(2*x-1, -1);
        id.resize(x); iota(id.begin(), id.end(), 0);
        mod.resize(2*x-1);
    }
} t1, t2;

ll f[N+5];
void add(int x, int y) {
    for (int i = x + 1; i <= N; i += i&-i) f[i] += y;
}
ll sum(int x) {
    ll res = 0;
    for (int i = x; i > 0; i -= i&-i) res += f[i];
    return res;
}
ll sum(int l, int r) { return sum(r) - sum(l); }

int get(int x) {
    int s = sum(x); x = 0;
    for (int i = 1<<18; i > 0; i >>= 1) {
        if (x + i <= N && f[x+i] < s) {
            x += i;
            s -= f[x];
        }
    }
    return x;
}

int n;
vector<vector<int>> q;
vector<int> lb;
void dfs(int u) {
    for (int i : t2.mod[u]) add(i, 1);
    if (u < n) {
        for (int i : q[u])
            lb[i] = get(i);
    } else {
        dfs(t2.l[u]); dfs(t2.r[u]);
    }
    for (int i : t2.mod[u]) add(i, -1);
}

vector<int> sz;
vector<ll> ans;
void dfs2(int u) {
    for (int i : t1.mod[u]) add(i, sz[u]);
    if (u < n) {
        for (int i : q[u])
            ans[i] = sum(lb[i], i);
    } else {
        dfs2(t1.l[u]); dfs2(t1.r[u]);
    }
    for (int i : t1.mod[u]) add(i, -sz[u]);
}

int m, a, b, x;
char op, c[5];
int main() {
    fast;
    cin >> n >> m;
    t1.init(n), t2.init(n); q.resize(n); lb.resize(m);
    sz.resize((n<<1)-1);
    for (int i = 0; i < n<<1; ++i) sz[i] = 1;
    ans.resize(m);
    for (int i = 0; i < m; ++i) ans[i] = -1;
    int c1 = 0, c2 = 0;
    for (int i = 0; i < m; ++i) {
        cin >> c; op = *c;
        if (op == 'U') {
            cin >> a >> b; a--; b--;
            int p = n + c1++;
            t1.fa[t1.id[a]] = t1.fa[t1.id[b]] = p;
            t1.l[p] = t1.id[a]; t1.r[p] = t1.id[b]; t1.id[a] = p;
            sz[p] = sz[t1.l[p]] + sz[t1.r[p]];
        } else if (op == 'M') {
            cin >> a >> b; a--; b--;
            int p = n + c2++;
            t2.fa[t2.id[a]] = t2.fa[t2.id[b]] = p;
            t2.l[p] = t2.id[a]; t2.r[p] = t2.id[b]; t2.id[a] = p;
        } else if (op == 'A') {
            cin >> x; x--;
            t1.mod[t1.id[x]].push_back(i);
        } else if (op == 'Z') {
            cin >> x; x--;
            t2.mod[t2.id[x]].push_back(i);
        } else {
            cin >> x; x--;
            q[x].push_back(i);
        }
    }
    for (int i = 0; i < n+c2; ++i) if (t2.fa[i] == -1) dfs(i);
    for (int i = 0; i < n+c1; ++i) if (t1.fa[i] == -1) dfs2(i);
    for (int i = 0; i < m; ++i)
        if (ans[i] != -1) cout << ans[i] << '\n';
    return 0;
}