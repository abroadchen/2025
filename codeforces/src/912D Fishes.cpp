//
// Created by Psy.C on 2026/10/12.
//
/**
有一个 n × m 的网格，我们有一个 r × r 的窗口/框。
每个格点 (x,y) 的"价值" = 该点被多少个可能的窗口位置覆盖（即当你把窗口中心放在所有合法位置时，有多少个窗口包含 (x,y)）。
要选择 k 个格点，使得这 k 个点的价值之和最大。
由于价值函数具有"中心最高、向四周递减"的凸/峰状性质，最优的 k 个点一定聚集在中心附近，所以用从中心出发的贪心（每次取当前可扩展点中价值最大的）‍——这近似于取最高的 k 个价值
node：格点(x,y)及其价值 v。operator< 按 v 升序定义，配合 priority_queue（默认大顶堆）实现按 v 从大到小出队。
dx, dy：上下左右四个方向的偏移。
mp：记录某格点是否已被访问（避免重复入堆）。
q：优先队列，动态维护"候选点"，每次弹出价值最大的
计算一个 r×r 窗口左上角/参考点的所有合法位置中，能包含格点 (x,y) 的数量。
窗口参考坐标范围是横向 [1, n-r+1]、纵向 [1, m-r+1]。
能让格点 (x,y) 被窗口覆盖的水平参考位置范围是 [max(1, x-r+1), min(n-r+1, x)]，长度为 min(n-r+1,x) - max(1,x-r+1) + 1。
同理纵向上能得到另一个长度。两者相乘 = 包含该格点的窗口数 = 该格点的价值
读入 n, m, r, k。
初始节点取网格中心 ((n+1)/2, (m+1)/2)（约中心），因为这里价值最大。
标记中心已访问并入队
循环：只要队列非空且已选点数 cnt < k：
弹出价值最大的节点 l，累加其价值到 sum，cnt++（选中它）。
扩展它上下左右四个邻居：若在界内且未访问过，则标记访问并入队。
这本质上是从中心向外做 Best-First Search（最佳优先搜索）‍，保证每次取当前可扩展点中价值最高者，从而近似得到价值最高的 k 个格点
总窗口位置数 = (n-r+1)*(m-r+1)。
输出 sum / 窗口数，保留 9 位小数。这表示"被选中的 k 个点，平均每个窗口覆盖的价值贡献"——即选点带来的期望/平均增益
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define pll pair<ll, ll>
using namespace std;

struct node {
    ll x, y, v;
    bool operator<(const node& rhs) const {
        return v < rhs.v;
    }
};

ll n, m, r;
ll get(ll x, ll y) {
    return (min(n-r+1, x) - max(1ll, x-r+1)+1)*
        (min(m-r+1, y) - max(1ll, y-r+1)+1);
}

ll k, cnt, sum, dx[]={0,0,-1,1}, dy[]={-1,1,0,0};
map<pll, bool> mp;
priority_queue<node> q;
int main() {
    fast;
    cin >> n >> m >> r >> k;
    node l = {.x = (n+1)/2, .y = (m+1)/2, .v = get((n+1)/2, (m+1)/2)};
    mp[{(n+1)/2, (m+1)/2}] = true; q.push(l);
    while (!q.empty() && cnt < k) {
        l = q.top(); q.pop();
        sum += l.v; cnt++;
        for (ll i = 0; i < 4; ++i) {
            ll tx = l.x+dx[i], ty = l.y+dy[i];
            if (tx > 0 && tx <= n && ty > 0 && ty <= m && mp[{tx, ty}] == false) {
                mp[{tx, ty}] = true;
                q.push({.x = tx, .y = ty, .v = get(tx, ty)});
            }
        }
    }
    printf("%.9f\n", (double)sum/(double)((n-r+1)*(m-r+1)));
    return 0;
}