//
// Created by Psy.C on 2026/3/17.
//
/**
n：元素总数
v[N]：某种价值或强度
d[N]：某种衰减或增量
p[N]：某种权值或阈值
ans[N]：结果数组，存储被选中的元素索引
cnt：选中的元素个数
vis[N]：标记数组，记录元素是否被选中

外层循环：
遍历每个未被访问的元素i
如果已被访问(vis[i])，跳过
选中元素：
将当前元素i加入结果(ans[++cnt] = i)
设置初始权重w = v[i]
第一个内层循环（影响后续元素）：
从i+1开始遍历到n
对于每个未访问的元素j：p[j] -= w，w--
权重w每次递减，影响逐渐减弱
当w <= 0时停止影响后续元素
第二个内层循环（激活其他元素）：
重置w = 0
再次遍历i+1到n
对未访问元素j：p[j] -= w
如果p[j] < 0且未被访问，则激活该元素：
w += d[j]：增加累积效应
vis[j] = 1：标记为已访问

时间复杂度：
O(n²)，双重循环
空间复杂度：
O(n)，主要是存储各个数组
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 4e3+5;
ll n, v[N], d[N], p[N], ans[N], cnt;
bool vis[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> v[i] >> d[i] >> p[i];
    for (int i = 1; i <= n; ++i) {
        if (vis[i]) continue;
        ans[++cnt] = i;
        ll w = v[i];
        for (int j = i + 1; j <= n; ++j) {
            if (vis[j]) continue;
            p[j] -= w; w--;
            if (w <= 0) break;
        }
        w = 0;
        for (int j = i + 1; j <= n; ++j) {
            if (vis[j]) continue;
            p[j] -= w;
            if (p[j] < 0 && !vis[j]) {
                w += d[j];
                vis[j] = 1;
            }
        }
    }
    cout << cnt << '\n';
    for (int i = 1; i <= cnt; ++i) cout << ans[i] << ' ';
    return 0;
}