//
// Created by Psy.C on 2026/2/17.
//
/**
f[N]: DP数组，存储以每个节点为根的子树方案数
ans: 总答案
v[N]: 邻接表，存储树结构
a[N]: 每个节点的权值
cnt, d, et: 临时变量

f[x] *= f[u] + 1: 当前节点的方案数乘以(子节点方案数+1)
+1 表示不选择子节点的方案

每次DFS：O(n)
总共n次DFS：O(n²)
总时间复杂度：O(n²)
空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2010, mod = 1e9+7;
ll f[N], ans=0;
vector<int> v[N];
int a[N], cnt, d, et;
void dfs(const int x, const int fa) {
    f[x] = 1;//当前节点x的初始方案数为1
    for (const auto u : v[x]) {
        if (u == fa) continue;
        if (a[u] > cnt + d || a[u] < cnt) continue;//权值在[cnt, cnt+d]范围内的节点
        if (a[u] == cnt && u < et) continue;//权值相同时，只考虑编号大于et的节点
        dfs(u, x);
        (f[x] *= f[u] + 1) %= mod;
    }
}

int n;
int main() {
    fast;
    cin >> d >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1, x, y; i <= n-1; ++i) {
        cin >> x >> y;
        v[x].push_back(y); v[y].push_back(x);
    }
    for (int i = 1; i <= n; ++i) {
        //当前节点权值为起始值
        cnt = a[i]; et = i;//当前节点编号
        memset(f, 0, sizeof(f));
        dfs(i, 0);//以节点i为根进行
        (ans += f[i]) %= mod;//累加以i为根的方案数
    }
    cout << ans << '\n';
    return 0;
}