//
// Created by Psy.C on 2026/2/5.
//
/**
* to[]: 存储边指向的节点
nxt[]: 链式前向星的next指针
head[]: 每个节点的第一条边的索引
tot=1: 边的编号计数器，从1开始
*++tot：边编号自增
to[tot] = v：第tot条边指向v节点
nxt[tot] = head[u]：新边的next指向u节点原来的首边
head[u] = tot：更新u节点的首边为新添加的边
 *
*vis[]: 访问标记数组
now[]: 当前处理的边的索引
dir[]: 方向标记数组
*vis[x] = 1：标记节点x已访问
for (int& e = now[x]; e; e = nxt[e])：遍历从x出发的所有边
if (!~dir[e>>1])：如果这条边还没有被访问过（!~表示逻辑非和按位非）
dir[e>>1] = e&1, dfs(to[e])：设置边的方向，然后递归访问目标节点
e>>1：边的逻辑编号（每对边作为一个逻辑边）
编号为奇数的边 (e&1=1) → 表示正向边
编号为偶数的边 (e&1=0) → 表示反向边
 *
*l[], r[]: 存储区间的左右端点
key[]: 用于离散化的端点值数组
cnt: 端点计数器
*++r[i]：将闭区间转换为半开区间[l[i], r[i]+1)
key[++cnt] = l[i], key[++cnt] = r[i]：收集所有端点值
 *
*u[]: 去重后的端点值
num: 离散化后端点数量
d[]: 差分数组
*key[i]^key[i-1]：异或判断是否相等（相等时异或结果为0）
只保存不同的端点值
*lower_bound(...) - u：二分查找得到离散化后的索引
d[l[i]]++; d[r[i]]--;：在差分数组中标记区间
add(...)：添加双向边，构建图结构
*d[i] += d[i-1]：计算前缀和，得到覆盖第i段的区间数
if (d[i]&1)：如果是奇数个区间，添加虚拟边确保欧拉回路存在
 *
 *复制head数组到now数组
 *对每个未访问的节点执行DFS
 */
#include <algorithm>
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100000
using namespace std;

int to[N*6+5], nxt[N*6+5], head[(N<<1)+5], tot=1;
void add(const int u, const int v) {
    to[++tot] = v; nxt[tot] = head[u]; head[u] = tot;
}

int vis[(N<<1)+5], now[(N<<1)+5], dir[N*3+5];
void dfs(const int x) {
    vis[x] = 1;
    for (int& e = now[x]; e; e = nxt[e]) if (!~dir[e>>1])
        dir[e>>1] = e&1, dfs(to[e]);
}

int main() {
    fast;
    int n; cin >> n;
    int l[N+5]{}, r[N+5]{}, key[(N<<1)+5]{}, cnt = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> l[i] >> r[i]; ++r[i];
        key[++cnt] = l[i], key[++cnt] = r[i];
    }
    sort(key + 1, key + cnt + 1); key[0] = -1;//设置哨兵值
    int u[(N<<1)+5]{}, num = 0, d[(N<<1)+5]{};
    for (int i = 1; i <= cnt; ++i) if (key[i]^key[i-1]) u[++num] = key[i];
    for (int i = 1; i <= n; ++i) {
        l[i] = static_cast<int>(lower_bound(u + 1, u + num + 1, l[i]) - u);
        r[i] = static_cast<int>(lower_bound(u + 1, u + num + 1, r[i]) - u);
        d[l[i]]++; d[r[i]]--;
        add(l[i], r[i]); add(r[i], l[i]);
    }
    for (int i = 1; i <= num; ++i) {
        d[i] += d[i-1];
        if (d[i]&1) add(i, i + 1), add(i + 1, i);
    }
    memset(dir, -1, sizeof(dir));
    for (int i = 1; i <= num; ++i) now[i] = head[i];
    for (int i = 1; i <= num; ++i) if (!vis[i]) dfs(i);
    for (int i = 1; i <= n; ++i) cout << dir[i] << " \n"[i==n];
    return 0;
}