//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
路径共有 (n-1)+(m-1) = n+m-2 步。

折半点选在过半的位置：使前一段和后一段步数相近。代码取：
因为从 (1,1) 出发，走完后 x+y 从 2 递增到 n+m。令 mid = (n+m+2)/2，当 x+y == mid 时，正好"走了大约一半的格子数"，作为前后两段的交界对角线
mp[x][y][d]：unordered_map，记录在交界对角线上的格子 (x,y) 处，累积异或值 = d 的路径条数
d = d^a[x][y]：进入格子 (x,y)，把它的值 XOR 进当前累积值 d。这里没有用临时变量而是在进入时立即异或，因为每一层递归的 d 是值传递（参数传值），向下递归不影响本层，返回后本层 d 保持为"已含本格子的值"，可以直接用于右/下分支，逻辑正确。
到达 x+y == mid：这正是交界对角线上的格子，说明第一段路径在此终结。此时 (x,y) 的坐标不同则 (x,y) 所在对角线位置存储到自己的 map 里：mp[x][y][d]++，统计"从起点到这格、异或累积 = d"的路径数。
if (x<n) dfs(x+1,y,d); 和 if (y<m) dfs(x,y+1,d);：继续向右/向下扩展。只要 x+y 还不到 mid 就继续加格子走
这次从 (n,m) 出发反向走（只能向上/向左），走到交界对角线为止。

关键差异：这里 d = d^a[x][y] 放在判断之后。原因：dfs2(n,m,k) 一开始 d=k 是整条路径的目标异或值。反向走时，我们希望"后半段已走过的格子异或值"为 d，而交界格子是前后两段共享的，不能重复异或。

具体衔接逻辑：

前半段（dfs）已经把交界格子 (x,y) 的值异或进了 d 并存进 mp[x][y][d]。
后半段反向走到 (x,y) 时，不应再异或这个交界格的值，否则等于把共享格异或了两次。
所以 dfs2 在判断到达交界之前，还没处理当前格（当前格就是交界格），此时 d 恰好是"后半段（终点到交界，不含交界格）已走的格子异或值"。用它去匹配 mp[x][y][d] 正好互补。
ans += mp[x][y][d]：前后两段在格子 (x,y) 相遇，且两段异或值互补成 k（因为前面 dfs 存的与后半段剩余值相等），则这两段可拼成一条总异或为 k 的整路径。累加匹配数
读入 n,m,k 与网格。
dfs(1,1,0)：第一段，初始异或 0。
dfs2(n,m,k)：第二段，初始异或 k（目标值）。
输出 ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; i++)
#define ll long long
using namespace std;

constexpr int N = 21;

int n, m;
ll a[N][N];
unordered_map<ll,ll> mp[N][N];
void dfs(int x, int y, ll d) {
    d = d^a[x][y];
    if (x+y == (n+m+2)/2) {
        mp[x][y][d]++;
        return;
    }
    if (x < n) dfs(x+1, y, d);
    if (y < m) dfs(x, y+1, d);
}

ll ans;
void dfs2(int x, int y, ll d) {
    if (x+y == (n+m+2)/2) {
        ans += mp[x][y][d];
        return;
    }
    d = d^a[x][y];
    if (x > 1) dfs2(x-1, y, d);
    if (y > 1) dfs2(x, y-1, d);
}

ll k;
int main() {
    fast;
    cin >> n >> m >> k;
    rep(i,n) rep(j,m) cin >> a[i][j];
    dfs(1, 1, 0); dfs2(n, m, k);
    cout << ans;
    return 0;
}