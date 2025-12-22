//
// Created by Psy.C on 2025/12/21.
//
/*
 *h:高度, p:水平坐标位置, id:标识符
 *标志位：false表示右端点，true表示左端点
 *e，用于存储所有的端点事件
 *l[i]和r[i]分别表示第i个区间的左端点和右端点
 *
 *
*g[x]存储节点x的邻接节点
c[x]存储对应的边容量（区间重叠长度）
 *
*排序：O(n log n)
扫描线处理：O(n log n)
DFS计算：O(n)
总体：O(n log n)
 */
#include <iostream>
#include <set>
#include <vector>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr ll N = 100005, inf = 2e9;
struct node { ll h, p, id; bool flag; } sl, sr;
vector<node> e;

ll l[N], r[N];//存储区间左右端点
int calc(const int a, const int b) {//两个区间的重叠长度
    return static_cast<int>(min(r[a], r[b]) - max(l[a], l[b]));
}

ll ans[N];
vector<ll> g[N], c[N];
ll dfs(const int x) {//从节点x到汇点的最大流/容量
    if (ans[x] != -1) return ans[x];
    if (x == 1) return inf;//到达终点
    ans[x] = 0;//初始化当前节点答案
    for (int i = 0; i < g[x].size(); ++i)//遍历所有相邻节点，计算最大可行流量
        ans[x] = max(ans[x], min(c[x][i], dfs(
            static_cast<int>(g[x][i]))));//递归计算邻接节点的最大流
    return ans[x];
}

int main() {
    fast;
    ll n, t; cin >> n >> t; n += 2;//扩展n 添加源点和汇点
    for (int i = 2, h; i < n; ++i) {//0和1预留为特殊节点
        cin >> h >> l[i] >> r[i];
        sr.h = h; sr.p = r[i]; sr.flag = false; sr.id = i;
        sl.h = h; sl.p = l[i]; sl.flag = true; sl.id = i;
        e.push_back(sr); e.push_back(sl);
    }
    sort(e.begin(), e.end(), [](const node& a, const node& b) {
        if (a.p != b.p) return a.p < b.p;//首先按位置坐标p升序排序
        if (a.flag != b.flag) return a.flag < b.flag;//位置相同时按标志位排序
        return a.id < b.id;//标志位也相同时按ID升序排序
    });
    //第一个元素是高度，第二个是节点ID
    set<pair<ll, ll>> s; s.clear();//维护扫描线状态
    s.insert({t, 0}); s.insert({0, 1});//插入源点(高度t，ID 0) 插入汇点(高度0，ID 1)
    l[0] = l[1] = -(1<<30); r[0] = r[1] = 1<<30;//设置源点和汇点的区间范围
    for (auto& i : e) {//扫描线算法处理所有事件
        if (!i.flag) s.erase({i.h, i.id});//如果是右端点，从集合中移除
        else {
            auto it = s.insert({i.h, i.id}).first;
            const int d = static_cast<int>((--it)->second); ++it;//查找前驱节点(在当前高度下方最近的区间)
            const int u = static_cast<int>((++it)->second);//查找后继节点(在当前高度上方最近的区间)
            //删除u的最后一个邻接节点 删除对应的容量值
            if (!g[u].empty() && g[u].back() == d) { g[u].pop_back(); c[u].pop_back(); }//如果u已经有连向d的边，则删除这条边避免重复边
            g[u].push_back(i.id);//从u向当前节点建立连接
            c[u].push_back(calc(
                static_cast<int>(i.id), u));//计算边的容量(重叠长度)
            g[i.id].push_back(d);//从当前节点向d建立连接
            c[i.id].push_back(calc(
                static_cast<int>(i.id), d));
        }
    }
    memset(ans, -1, sizeof(ans));
    cout << dfs(0) << '\n';
    return 0;
}