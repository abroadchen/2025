//
// Created by Psy.C on 2026/9/19.
//
/**
v1[i]：给每种颜色的需求集合——v1[i] 存的是第 i 个"约束"里要求的元素/位置集合。
v2[i]：树的邻接表（n 个节点的树）。
s[x]：给每个元素 x 分配的颜色编号。
mp：标记某条约束内已用的颜色
对节点 x 代表的约束 v1[x]：
先收集该约束内已分配颜色的元素所用的颜色，存入 mp。
对约束内尚未着色的元素，从小到大分配约束内尚未使用的最小颜色编号（贪心，保证互异且编号尽量小）。
递归进入树的子节点（避开父节点 pre）

读入 n 条约束和 m 个元素。
ans = 所有约束元素数的最大值，即理论最少颜色数（每条约束内元素互异，因此至少需要 max 种颜色；构造成树后恰好能实现这么多）。
建树、DFS 染色。
输出 ans 和每个元素的颜色（未约束的元素默认颜色 1）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e5+10;
map<int, int> mp;
vector<int> v1[N], v2[N];
int s[N];
void dfs(int x, int pre) {
    mp.clear();
    for (int i : v1[x])
        if (s[i]) mp[s[i]] = 1;//标记约束内已用颜色
    int cnt = 0;
    for (int i : v1[x]) {
        if (s[i]) continue;//已有颜色则跳过
        while (mp[++cnt]) {}//找第一个未用颜色
        s[i] = cnt;//分配最小可用颜色
    }
    for (int i = 0; i < v2[x].size(); ++i)
        if (v2[x][i] != pre) dfs(v2[x][i], x);
}

int main() {
    fast;
    int n, m; cin >> n >> m;
    int ans = 1;
    for (int i = 1, k, x; i <= n; ++i) {
        cin >> k;
        if (ans < k) ans = k;
        while (k--) {
            cin >> x;
            v1[i].push_back(x);
        }
    }
    for (int i = 1, x, y; i < n; ++i) {
        cin >> x >> y;
        v2[x].push_back(y); v2[y].push_back(x);
    }
    dfs(1, -1);
    cout << ans << '\n';
    for (int i = 1; i <= m; ++i) {
        if (s[i]) cout << s[i] << ' ';
        else cout << "1 ";
    }
    cout << '\n';
    return 0;
}