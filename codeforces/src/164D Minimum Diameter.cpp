//
// Created by Psy.C on 2025/11/27.
//
/*
*n: 点的数量
k: 需要选择的点数
d[N*N]: 存储所有距离值的数组
num: 距离数组的有效元素个数
g[N][N]: 存储点对之间距离的邻接矩阵
vis[N]: 标记数组，记录点是否被选择
 *
*DFS回溯函数：
cnt: 当前处理的点编号
m: 当前已选择的点数
 *如果所有点都已处理完，返回true（找到可行解）
 *如果当前点已经被选择，处理下一个点
*标记所有与当前点冲突的点（即将它们加入已选择集合）
m += !vis[v[cnt][i]]: 如果之前未被选择，则增加计数
vis[v[cnt][i]]++: 标记为已选择
 *如果当前选择的点数不超过k且后续能找到解，则返回true
*回溯：取消标记与当前点冲突的点
恢复之前的m值到t
*如果当前点的冲突点数不为1：
选择当前点（vis[cnt]++）
如果选择后点数不超过k且少于之前的情况
递归处理下一个点
如果成功则返回true，否则回溯（vis[cnt]--）
 *
*检查给定距离阈值是否可行的函数
dis: 距离阈值
 *初始化：清空vis数组和邻接表
*构建冲突图：如果两点间距离大于阈值，则它们冲突
在邻接表中互相添加对方
 *调用DFS检查是否存在可行解
 *
*二分搜索函数，寻找最小的可行距离阈值
l, r: 搜索范围的左右边界
*计算中点mid
如果距离d[mid]可行，则缩小右边界
否则缩小左边界
 */
#include <iostream>
#include <vector>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define sz(x) (static_cast<int>((x).size()))
using namespace std;

constexpr int N = 1015;
int n, k, d[N*N], num, g[N][N], vis[N];
struct node { int x, y; } p[N];//存储所有点的坐标
vector<int> v[N];//v[i]存储与点i冲突（距离过大）的点列表

bool dfs(const int cnt, int m) {
    if (cnt > n) return true;
    if (vis[cnt]) return dfs(cnt + 1, m);
    for (int i = 0; i < sz(v[cnt]); ++i) {
        m += !vis[v[cnt][i]];
        vis[v[cnt][i]]++;
    }
    if (m <= k && dfs(cnt + 1, m)) return true;
    const int t = m;
    for (int i = 0; i < sz(v[cnt]); ++i) {
        vis[v[cnt][i]]--;
        m -= !vis[v[cnt][i]];
    }
    if (sz(v[cnt]) != 1) {
        vis[cnt]++;
        if (m + 1 <= k && m + 1 < t &&
            dfs(cnt + 1, m + 1)) return true;
        vis[cnt]--;
    }
    return false;
}

bool ok(const int dis) {
    for (auto& x : vis) x = false;
    for (int i = 1; i <= n; ++i) v[i].clear();
    for (int i = 1; i <= n; ++i) for (int j = i + 1; j <= n; ++j) {
        if (g[i][j] > dis) { v[i].push_back(j); v[j].push_back(i); }
    }
    return dfs(1, 0);
}

int bs(int l, int r) {
    while (l < r) {
        const int mid = (l + r) >> 1;
        if (ok(d[mid])) r = mid;
        else l = mid + 1;
    }
    return l;
}

int main() {
    fast;
    cin >> n >> k; num = 0; d[0] = 0;
    for (int i = 1; i <= n; ++i) cin >> p[i].x >> p[i].y;
    for (int i = 1; i < n; ++i) for (int j = i + 1; j <= n; ++j) {
        d[++num] = g[i][j] = (p[i].x - p[j].x) * (p[i].x - p[j].x) +
            (p[i].y - p[j].y) * (p[i].y - p[j].y);
    }
    sort(d, d + num + 1);
    num = static_cast<int>(unique(d, d + num + 1) - d - 1);
    const int mx = bs(0, num); ok(d[mx]);//再次调用ok函数确定最终的vis数组状态
    bool f = false;
    for (int i = n; i >= 1; --i) if (vis[i]) {//按降序输出被选择的点（vis[i]为true的点）
        if (f) cout << ' '; cout << i;
        k--;
        f = true;
    }
    for (int i = n; i >= 1 && k > 0; --i) if (!vis[i]) {//如果还需要更多点，则按降序输出未被选择的点
        if (f) cout << ' '; cout << i;
        k--;
        f = true;
    }
    cout << '\n';
    return 0;
}