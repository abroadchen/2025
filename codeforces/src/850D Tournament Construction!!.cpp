//
// Created by Psy.C on 2026/9/29.
//
/**
dp[i][j][k] 的含义：

i：当前考虑到了第 i 个"槽位"（候选节点位）
j：目前已经用掉了 j 个输入数 a（即已确定前 j 个度数值）
k：前 i 个节点之间的总边数
转移只有两种（第 i 个槽位不新增度数，或新增一个度数 a[j]）
f 记录前驱三元组（回溯链）。k 的范围下限 max(a[j], i(i-1)/2) 是剪枝：边数不能小于完全图的三角数。

关键目标：找到最小的 i 使得 dp[i][n][i(i-1)/2] = true——也就是恰好 i 个节点、正好配完 n 个度数、总边数 = 完全图边数 i(i-1)/2（Landau/可行度序列条件）。找到即记下 x=i, y=n, z=i(i-1)/2 并跳出。

找到 → 进入构造
x == -1 没找到 → 无解输出 =(
从终点状态 (x,y,z) 沿着 f 记录的前驱一路回退到 (0,0,0)。

每走一步从 z 回退到 k，这一步新增产生的边数就是 z - k，存到 o[cnt].x，并给节点编号 id。
于是得到 cnt 个节点，o[i].x = 该节点需要的边数（出度/度数）
每轮取出当前需求最大的节点（排最后 o[i]），让它指向需求量最小的 o[i].x 个点，其余点反向指向它并各自需求减一——这是标准的 Havel–Hakimi 贪心，保证度数恰好被配齐。

id 用于回填真实的邻接矩阵行号/列号，最后按编号输出 cnt×cnt 的 0/1 矩阵。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 35;

struct node { int a, b, c; } f[N<<1][N][N*N*2];
struct node2 {
    int x, id;
    bool operator<(const node2 & o) const {
        return x < o.x;
    }
} o[N<<1];

int cnt;
static void dfs(int x, int y, int z) {
    if (!x && !y && !z) return;
    int i = f[x][y][z].a, j = f[x][y][z].b, k = f[x][y][z].c;
    ++cnt, o[cnt] = {.x = z-k, .id = cnt}, dfs(i, j, k);
}


int a[N];
bool dp[N<<1][N][N*N*2], t[N<<1][N<<1];
signed main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a+1, a+n+1); dp[0][0][0] = 1;
    int x = -1, y = 0, z = 0;
    for (int i = 1; i <= 61; ++i) {
        for (int j = 1; j <= n; ++j)
            for (int k = max(a[j], i*(i-1)/2); k <= 1860; ++k) {
                if (dp[i-1][j][k-a[j]])
                    dp[i][j][k] = 1, f[i][j][k] = {.a = i-1, .b = j, .c = k-a[j]};
                if (dp[i-1][j-1][k-a[j]])
                    dp[i][j][k] = 1, f[i][j][k] = {.a = i-1, .b = j-1, .c = k-a[j]};
            }
        if (dp[i][n][i*(i-1)/2]) {
            x = i, y = n, z = i*(i-1)/2;
            break;
        }
    }
    if (x == -1) { cout << "=(\n"; return 0; }
    dfs(x, y, z); cout << cnt << '\n';
    for (int i = cnt; i >= 1; --i) {
        sort(o+1, o+i+1);//每次按剩余需求量 x 从小到大排
        for (int j = 1; j <= o[i].x; ++j)
            t[o[i].id][o[j].id] = 1;//当前最大需求节点 → 指向前 o[i].x 个点
        for (int j = o[i].x+1; j < i; ++j)
            t[o[j].id][o[i].id] = 1, --o[j].x;//其余点反过来指向它，并扣减它们的需
    }
    for (int i = 1; i <= cnt; ++i) {
        for (int j = 1; j <= cnt; ++j) cout << t[i][j];
        cout << '\n';
    }
    return 0;
}