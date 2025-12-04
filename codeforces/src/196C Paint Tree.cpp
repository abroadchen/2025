//
// Created by Psy.C on 2025/12/3.
//
/*
*定义结构体node表示边，包含目标节点to和下一条边的索引nxt
声明边数组e，大小为2*N（因为是无向图，每条边存储两次）
*cnt: 边的计数器
head[N]: 邻接表的头指针数组
 *创建新边：cnt递增，设置目标节点为v，下一条边为head[u]，更新head[u]
*定义结构体point表示点坐标，包含x坐标、y坐标和id
声明点数组p和临时点t
 *数组siz，用于存储每个节点的子树大小
*dfs函数，计算子树大小
参数：x为当前节点，fa为父节点
 *初始化当前节点子树大小为1（包含自身）
 *遍历当前节点的所有邻接点
 *跳过父节点，避免回到父节点
 *递归计算子节点的子树大小，并累加到当前节点
 *
 *数组ans，存储答案（每个点对应的节点编号）
*dfs2函数，进行点匹配
参数：l和r表示点的范围，x为当前树节点，fa为父节点
 *初始化mn为l，表示y坐标最小的点的索引
 *遍历范围内的点
 *寻找y坐标最小的点，如果y相同则选择x坐标较小的点
 *将找到的最下方面点交换到位置l
 *记录该点对应的树节点编号
 *保存当前点作为基准点
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1510
using namespace std;

ll n;
struct node { ll to, nxt; } e[N<<1];
ll cnt, head[N];
inline void add(const ll u, const ll v) {
    e[++cnt].to = v; e[cnt].nxt = head[u]; head[u] = cnt;
}
struct point { ll x, y, id; } p[N], t;

ll siz[N];
void dfs(const ll x, const ll fa) {
    siz[x] = 1;
    for (ll i = head[x]; i; i = e[i].nxt) {
        if (e[i].to == fa) continue;
        dfs(e[i].to, x);
        siz[x] += siz[e[i].to];
    }
}

ll ans[N];
void dfs2(const ll l, const ll r, const ll x, const ll fa) {
    ll mn = l;
    for (ll i = l + 1; i <= r; ++i) {
        if (p[i].y < p[mn].y ||
            p[i].y == p[mn].y && p[i].x < p[mn].x) {
            mn = i;
        }
    }
    swap(p[l], p[mn]);//将找到的最下方面点交换到位置l
    ans[p[l].id] = x;//记录该点对应的树节点编号
    t = p[l];//保存当前点作为基准点
    //对剩余点进行极角排序
    sort(p + l + 1, p + r + 1, [](const point& a, const point& b) {
        const ll ax = a.x - t.x, ay = a.y - t.y, bx = b.x - t.x, by = b.y - t.y;//相对于基准点的向量坐标
        if (ax >= 0 && bx <= 0) return true;//如果a点在右半平面而b点在左半平面，则a排在前面
        if (ax <= 0 && bx >= 0) return false;//如果a点在左半平面而b点在右半平面，则b排在前面
        return ax * by > ay * bx;//a的极角小于b的极角
    });
    ll cur = l + 1;//初始化当前处理位置
    for (ll i = head[x]; i; i = e[i].nxt) {//遍历当前树节点的所有子节点
        if (e[i].to == fa) continue;
        dfs2(cur, cur + siz[e[i].to] - 1,  e[i].to, x);//递归处理子树，分配相应数量的点
        cur += siz[e[i].to];//更新当前处理位置
    }
}

int main() {
    fast;
    cin >> n;
    for (ll i = 1, a, b; i < n; ++i) {
        cin >> a >> b;
        add(a, b); add(b, a);
    }
    for (ll i = 1; i <= n; ++i) {
        cin >> p[i].x >> p[i].y;
        p[i].id = i;
    }
    dfs(1, 1);//从节点1开始计算子树大小
    dfs2(1, n, 1, 1);//从节点1开始进行点匹配
    for (ll i = 1; i < n; ++i) cout << ans[i] << ' ';
    cout << ans[n] << '\n';
    return 0;
}