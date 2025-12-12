//
// Created by Psy.C on 2025/12/12.
//
/*
*idx：当前处理的节点索引
r：剩余红色资源数量
g：剩余绿色资源数量
pre：前一个节点的颜色（0表示红色，1表示绿色）
*边界条件检查，防止数组越界：
如果节点索引idx超出范围(N)则返回无穷大
如果红色资源r或绿色资源g为负数则返回无穷大
如果前一个节点颜色pre不是0或1则返回无穷大
 *防止资源数量r超出数组第二维的范围M
 *
*计算颜色切换代价c：
如果前一个节点也是红色(pre==0)，代价为0
否则代价为当前节点和前一个节点高度的较小值
特殊处理：如果当前是第一个节点(idx<=1)，则与前一个节点的比较值为0
*更新结果：选择涂红色的最小代价
递归计算下一个节点的状态：资源变为(r-h[idx], g)，颜色为红色(0)
加上当前的颜色切换代价c
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 210
#define M 40100
#define inf 0x3f3f3f3f
using namespace std;

int n, f[N][M][2], h[N];
int dfs(const int idx, const int r, const int g, const int pre) {
    if (idx >= N || r < 0 || g < 0 || pre >= 2) return inf;
    if (r >= M) return inf;
    if (idx > n) return 0;//如果处理完所有节点(n个)，返回0表示没有额外代价
    int& ret = f[idx][r][pre];//创建引用ret指向记忆化数组中的当前位置
    if (ret != -1) return ret;
    ret = inf;
    if (r >= h[idx]) {//足够涂当前节点
        const int c = pre == 0 ? 0 : min(h[idx],
            idx > 1 ? h[idx - 1] : 0);
        ret = min(ret, dfs(idx + 1, r - h[idx], g, 0) + c);
    }
    if (g >= h[idx]) {
        const int c = pre == 1 ? 0 : min(h[idx],
            idx > 1 ? h[idx - 1] : 0);
        ret = min(ret, dfs(idx + 1, r, g - h[idx], 1) + c);
    }
    return ret;
}


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    fast;
    int a, b; cin >> n >> a >> b;
    for (int i = 1; i <= n; ++i) cin >> h[i];
    memset(f, -1, sizeof f);
    const int ans = dfs(1, a, b, 0);
    if (ans >= inf) cout << -1 << '\n';
    else cout << ans << '\n';
    return 0;
}