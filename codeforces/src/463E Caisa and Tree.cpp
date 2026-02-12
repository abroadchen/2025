//
// Created by Psy.C on 2026/2/12.
//
/**
目标节点to和下一条边的索引nxt
num：边的总数
head[N<<1]：头指针数组
val[N]：节点权值数组
ans[N]：答案数组
q[N]：询问数组，q[u]存储在节点u的询问索引
st：栈，用于DFS过程中的路径记录

DFS遍历树，参数u为当前节点，fa为父节点
如果当前节点u有询问：
从栈顶开始向前查找，直到找到与u的权值GCD不为1的节点
__gcd(val[st[k]], val[u]) == 1：计算GCD是否为1
if (~k) k = st[k]：如果找到了节点，k赋值为该节点编号
更新所有在u节点的询问的答案
st.push_back(u)：将当前节点压入栈
遍历所有子节点，递归DFS
st.pop_back()：回溯时弹出节点

操作类型1：询问操作
将询问索引i加入节点y的询问列表
cnt++增加未处理询问数
操作类型2：修改操作
如果有未处理询问，先执行DFS
修改节点x的权值为y
重置cnt为0
ans[i] = -2标记此操作的结果
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;

struct node { int to, nxt; } e[N<<1];

int num, head[N<<1];
void add(const int u, const int v) {
    e[num].to = v; e[num].nxt = head[u]; head[u] = num++;
}

int val[N], ans[N];
vector<int> q[N], st;
void dfs(const int u, const int fa) {
    if (!q[u].empty()) {
        int k = st.size() - 1;
        while (k >= 0 && __gcd(val[st[k]], val[u]) == 1) k--;
        if (~k) k = st[k];
        for (const auto i : q[u]) ans[i] = k;
        q[u].clear();
    }
    st.push_back(u);
    for (int i = head[u]; ~i; i = e[i].nxt) {
        const int v = e[i].to;
        if (v == fa) continue;
        dfs(v, u);
    }
    st.pop_back();
}

int n, m;
int main() {
    fast;
    cin >> n >> m;
    memset(head, -1, sizeof head);
    for (int i = 1; i <= n; ++i) cin >> val[i];
    for (int i = 0, x, y; i < n - 1; ++i) {
        cin >> x >> y; add(x, y); add(y, x);
    }
    int cnt = 0;
    for (int i = 0, op, x, y; i < m; ++i) {
        cin >> op;
        if (op == 1) {
            cin >> y; q[y].push_back(i); cnt++;
        } else {
            cin >> x >> y;
            if (cnt) dfs(1, 0);
            val[x] = y;
            cnt = 0;
            ans[i] = -2;
        }
    }
    if (cnt) dfs(1, 0);
    for (int i = 0; i < m; ++i)
        if (ans[i] != -2) cout << ans[i] << '\n';
    return 0;
}