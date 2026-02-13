//
// Created by Psy.C on 2026/2/13.
//
/**
dfn[x]：节点x的时间戳
low[x]：节点x能到达的最小时间戳
col[x]：节点x所属的强连通分量编号
vis[x]：节点x是否在栈中

i表示选择某种状态，i+n表示选择另一种状态
如果不存在A-a[i]，添加边i -> i+n（选择i必须选择i+n，矛盾）
如果存在A-a[i]，添加边i -> pos[A-a[i]]和pos[A-a[i]]+n -> i+n

时间复杂度：O(n+m)，其中m是边数
unordered_map: O(1) 平均查找时间
vector + find: O(n) 查找时间
sorted vector + binary search: O(log n) 查找时间
array: O(1) 但可能浪费空间或超出范围
 */
#include <iostream>
#include <stack>
#include <unordered_map>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 200010
using namespace std;

struct edge { int nxt, to; } e[N<<1];

int tot, head[N];//边编号 邻接表头指针
void add(const int from, const int to) {
    e[++tot].to = to; e[tot].nxt = head[from]; head[from] = tot;
}

int dfn[N], low[N], cnt, col[N];
bool vis[N];
stack<int> st;
void tarjan(const int x) {
    dfn[x] = low[x] = ++tot; vis[x] = 1;
    st.push(x);
    for (int i = head[x]; ~i; i = e[i].nxt) {
        if (const int v = e[i].to; !dfn[v]) {
            tarjan(v);
            low[x] = min(low[x], low[v]);
        }
        else if (vis[v])
            low[x] = min(low[x], dfn[v]);
    }
    if (dfn[x] == low[x]) {
        cnt++;
        int y;
        do {
            y = st.top(); st.pop();
            col[y] = cnt;
            vis[y] = 0;
        } while (y != x);
    }
}

int n, A, B, a[N];
unordered_map<int, int> pos;
bool flag;

int main() {
    fast;
    memset(head, -1, sizeof(head));
    cin >> n >> A >> B;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pos[a[i]] = i;//每个值对应的位置
    }
    for (int i = 1; i <= n; ++i) {
        if (!pos.contains(A - a[i])) add(i, i+n);
        else add(i, pos[A-a[i]]), add(pos[A-a[i]]+n, i+n);
        if (!pos.contains(B - a[i])) add(i+n, i);
        else add(i+n, pos[B-a[i]]+n), add(pos[B-a[i]], i);
    }
    tot = 0; flag = 1;
    for (int i = 1; i <= 2*n; ++i) if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= n; ++i)
        if (col[i] == col[i+n]) { flag = 0; break; }
    if (flag) cout << "YES\n";
    else return cout << "NO\n", 0;
    for (int i = 1; i <= n; ++i)
        cout << (col[i] > col[i+n]) << ' ';
    return 0;
}