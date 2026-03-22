//
// Created by Psy.C on 2026/3/22.
//
/**
定义矩形结构体，包含四个坐标和ID
重载小于运算符，优先按b排序，相同时按id排序
s[]: 树状数组，每个位置存储一个set

从树状数组中获取满足条件的节点
遍历所有未访问且满足条件的节点
更新距离和前驱，并加入队列

初始化BFS，从原点(0,0)开始
如果目标节点本身就是原点附近，特殊处理
BFS遍历，直到到达目标节点
每次扩展时更新当前位置并继续搜索

读入矩形数据，同时收集所有坐标值用于离散化
添加0点并排序去重，完成离散化
将每个矩形按离散化后的坐标加入树状数组
执行BFS搜索
如果无法到达目标，输出-1
否则输出最短路径长度和具体路径（通过栈逆序输出路径）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5e5+5, M = 1e5, inf = 1e8;

struct node {
    int a, b, c, d, id;
    bool operator<(const node &o) const {
        if (b != o.b) return b < o.b;
        return id < o.id;
    }
} tr[M+5];

int low_bit(int x) { return x & -x; }

set<node> s[(M<<2)+5];
void add(int x, int id) {
    while (x <= (M<<2)+2) {
        s[x].insert(tr[id]);
        x += low_bit(x);
    }
}
int vis[M+5], dis[M+5], pre[M+5];
queue<int> q;
void get(int x, int y, int dist, int pid) {
    while (x >= 1) {
        auto it = s[x].begin();
        while (it != s[x].end() && it->b <= y) {
            int tid = it->id;
            if (vis[tid] == 1) s[x].erase(it++);
            else {
                vis[tid] = 1;
                dis[tid] = dist + 1;
                pre[tid] = pid; q.push(tid);
                s[x].erase(it++);
            }
        }
        x -= low_bit(x);
    }
}

int a[N], cnt, n;
void bfs() {
    int x = 0, y = 0;
    while (!q.empty()) q.pop();
    int tx = lower_bound(a, a + cnt, x) - a;
    get(tx + 1, y, 0, -1);
    if (tr[n-1].a == 0 && tr[n-1].b == 0) {
        dis[n-1] = 1; return;
    }
    while (!q.empty()) {
        int tid = q.front(); q.pop();
        if (tr[tid].c <= x && tr[tid].d <= y) continue;
        if (tr[tid].c >= tr[n-1].a && tr[tid].d >= tr[n-1].b) {
            dis[n-1] = dis[tid] + 1;
            pre[n-1] = tid; return;
        }
        x = tr[tid].c; y = tr[tid].d;
        tx = lower_bound(a, a + cnt, x) - a;
        get(tx + 1, y, dis[tid], tid);
    }
}

int main() {
    fast;
    cin >> n; cnt = 0;
    for (int i = 0; i <= (M<<2)+2; ++i) s[i].clear();
    for (int i = 0; i < n; ++i) {
        pre[i] = -1; dis[i] = inf;
        cin >> tr[i].a >> tr[i].b >> tr[i].c >> tr[i].d;
        tr[i].id = i;
        a[cnt++] = tr[i].a; a[cnt++] = tr[i].b;
        a[cnt++] = tr[i].c; a[cnt++] = tr[i].d;
    }
    a[cnt++] = 0; sort(a, a + cnt);
    cnt = unique(a, a + cnt) - a;
    for (int i = 0; i < n; ++i) {
        int tx = lower_bound(a, a + cnt, tr[i].a) - a;
        add(tx + 1, i);
    }
    bfs();
    if (dis[n-1] == inf) cout << "-1\n";
    else {
        cout << dis[n-1] << '\n';
        stack<int> ans;
        int tp = n - 1;
        while (tp != -1) { ans.push(tp); tp = pre[tp]; }
        while (!ans.empty()) {
            cout << ans.top() + 1 << ' ';
            ans.pop();
        }
        cout << '\n';
    }
    return 0;
}