//
// Created by Psy.C on 2026/4/21.
//
/**
u：起点
v：终点
nxt：邻接表中的下一个边索引
id：原始边ID
w：权重
flag：标志位（权重为0时为0，否则为1）
n：节点数量
m：边的数量
L：目标距离
T：终点
au, av, aw：分别存储边的起点、终点和权值
mp：映射，用于记录已修改的边
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 10007, M = 4e5+7;

struct node { ll u, v, nxt, id, w, flag; } e[M];

ll head[N], cnt;
void add(ll u, ll v, ll w, ll id) {
    e[cnt].id = id; e[cnt].u = u; e[cnt].v = v; e[cnt].w = w;
    if (w == 0) e[cnt].flag = 0; else e[cnt].flag = 1;
    e[cnt].nxt = head[u]; head[u] = cnt++;
}
void init() {
    memset(head, -1, sizeof(head));
    cnt = 0;
}

ll f[N], vis[N], dis[N], S;
queue<ll> q;
void spfa(ll flag) {
    memset(f, -1, sizeof(f));//父节点数组
    memset(vis, 0, sizeof(vis));//访问标记数组
    memset(dis, 0x3f, sizeof(dis));//距离数组
    dis[S] = 0; vis[S] = 1;
    while (!q.empty()) q.pop(); q.push(S);//清空队列，加入起点
    while (!q.empty()) {
        ll u = q.front(); q.pop();
        for (ll i = head[u]; ~i; i = e[i].nxt) {//遍历u的所有邻接边
            ll v = e[i].v, w = e[i].w;
            if (flag && !w) continue;//flag为1且边权为0，则跳过该边
            if (dis[v] <= dis[u] + w) continue;//新路径不更优则跳过
            dis[v] = dis[u] + w;//更新最短距离
            if (!flag) f[v] = i;//flag为0，记录路径（用于回溯）
            if (vis[v]) continue;//已在队列中则跳过
            vis[v] = 1;//标记为在队列中
            q.push(v);//加入队列
        }
        vis[u] = 0;//标记为未在队列中
    }
}

ll n, m, L, T, au[N], av[N], aw[N];
map<ll, ll> mp;
int main() {
    fast; init();
    cin >> n >> m >> L >> S >> T;
    for (ll i = 0; i < m; ++i) {
        cin >> au[i] >> av[i] >> aw[i];
        add(au[i], av[i], aw[i], i);
        add(av[i], au[i], aw[i], i);
    }
    spfa(1);//跳过权值为0的边
    if (dis[T] < L) {
        cout << "NO\n";
        return 0;
    }
    if (dis[T] == L) {
        cout << "YES\n";
        for (ll i = 0; i < m; ++i)
            cout << au[i] << ' ' << av[i] << ' ' << (aw[i]==0?L+10:aw[i]) << '\n';
        return 0;
    }
    for (int i = 0; i < cnt; ++i)//将所有权值为0的边权值改为1
        if (!e[i].flag) aw[e[i].id] = e[i].w = 1;
    while (true) {
        spfa(0);//不跳过任何边，记录路径
        if (dis[T] > L) {
            cout << "NO\n";
            return 0;
        }
        if (dis[T] == L) {
            cout << "YES\n";
            for (ll i = 0; i < m; ++i)
                cout << au[i] << ' ' << av[i] << ' ' << aw[i] << '\n';
            return 0;
        }
        //调整路径上的0权边
        ll u = T; mp.clear();
        ll sum = L - dis[T];//需要增加的距离
        while (u != S) {//从终点回溯到起点
            if (!e[f[u]].flag) {//这条边原来是0权边
                aw[e[f[u]].id] = e[f[u]].w = e[f[u]].w+sum;//增加权值
                sum = 0;//增加量清零
                mp[e[f[u]].id] = 1;//标记这条边已修改
            }
            u = e[f[u]].u;//回溯到父节点
        }
        //将其他0权边设置为较大值
        for (int i = 0; i < cnt; ++i)
            if (!e[i].flag && !mp[e[i].id])//0权边且未被修改
                aw[e[i].id] = e[i].w = L + 10;//设置为较大值
    }
}
