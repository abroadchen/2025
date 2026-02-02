//
// Created by Psy.C on 2026/2/2.
//
/**
* n：行数
m：列数
k：最大值（可能的元素种类数）
a[N][N]：输入矩阵
从索引1开始存储，便于处理
 *
*
used[N]：标记每轮中元素是否已被使用 临时使用标记
locked[N]：标记元素是否被锁定（已分配） 永久分配标记
pre[N]：记录元素的前驱行号 元素归属关系
c[N]：记录每行的匹配列号
 *
*按列遍历（j从1到m）
每列开始时重置used和pre数组
*遍历每行i
if (c[i] || !a[i][j]) continue;：如果该行已有匹配或当前位置为0则跳过
*情况1：如果元素a[i][j]已被锁定
将行i匹配到列j
*情况2：如果元素a[i][j]已被使用但未锁定
锁定该元素
将当前行i匹配到列j
将之前的拥有者pre[a[i][j]]也匹配到列j
*情况3：元素a[i][j]未被使用
记录该元素的前驱行号为i
标记该元素为已使用
 *输出每行的匹配列号
 *
*时间复杂度：O(n×m)
空间复杂度：O(n×m)
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 110
using namespace std;


int main() {
    fast;
    int n, m, k, a[N][N], i, j; cin >> n >> m >> k;
    for (i = 1; i <= n; ++i) for (j = 1; j <= m; ++j) {
        cin >> a[i][j];
    }
    bool used[N], locked[N]; int pre[N], c[N];
    for (j = 1; j <= m; ++j) {
        memset(used, 0, sizeof(used));
        memset(pre, 0, sizeof(pre));
        for (i = 1; i <= n; ++i) {
            if (c[i] || !a[i][j]) continue;
            if (locked[a[i][j]]) c[i] = j;
            else if (used[a[i][j]]) {
                locked[a[i][j]] = true;
                c[i] = j;
                c[pre[a[i][j]]] = j;
            } else {
                pre[a[i][j]] = i;
                used[a[i][j]] = true;
            }
        }
    }
    for (i = 1; i <= n; ++i) cout << c[i] << '\n';
    return 0;
}