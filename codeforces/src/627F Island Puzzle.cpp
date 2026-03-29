//
// Created by Psy.C on 2026/3/28.
//
/**
检查所有不匹配位置是否都在同一条路径上
dif: 不匹配的数量
bc[]: 不匹配位置数组
lu, lv: 路径两端
lt: 路径LCA（最低公共祖先）
以值为0的节点为根（在b数组中找0）
将a数组中值为0的节点移到根部
统计所需交换次数
如果已经匹配，直接输出结果
找到所有不匹配位置并按深度排序
构建从lu到lt再到lv的路径环
cyc[]: 存储环路上的节点
in[]: 节点在环中的索引
将路径上的节点移动到根部附近
提取环路上的值
计算旋转偏移量


to[++cnt] = v: 新边指向v节点
nxt[cnt] = head[u]: 新边的next指向前一条边
head[u] = cnt: 更新u节点的首边为新边
p[]: 存储每个节点的父节点
dep[]: 存储每个节点的深度（从根开始）
for (int i = head[x], y; i; i = nxt[i]): 遍历节点x的所有邻接节点
(y=to[i]) != p[x]: 确保不回到父节点（避免走回头路）
p[y] = x: 设置y的父节点为x
dep[y] = dep[x] + 1: y的深度比x深一层
dfs(y): 递归处理子节点
当x≠y时，让深度更深的节点向上跳一步
dep[x] < dep[y] ? y = p[y] : x = p[x]: 始终让更深的节点向上移动
最终x和y会在它们的LCA处相遇
检查所有不匹配位置是否在一条路径上
for (i = 1; i < dif && p[bc[i]] == bc[i-1]; ++i) {}: 检查是否形成简单路径
if (i == dif): 如果所有节点都连续，设置路径端点
lt = lu = p[*bc], lv = bc[dif-1]: 设置LCA为第一个节点的父节点，右端点为最后一个节点
否则，将不匹配节点分成两个分支进行处理
如果发现不在路径上的节点，返回false
n: 节点数量
a[], b[]: 初始和目标数组
u, v: 临时变量
rt: 根节点
cyc[]: 环路节点数组
len: 环路长度
in[]: 节点在环中的索引
w, z: LCA相关变量
j: 循环变量
A[], B[]: 环路值的副本
ofs: 偏移量
D: 最终距离
find(b + 1, b + n + 1, 0) - b: 在b数组中找到值为0的元素位置，作为根节点
u = v = find(a + 1, a + n + 1, 0) - a: 找到a数组中值为0的元素位置
通过交换操作将a中0移到根节点位置，统计移动步数
!memcmp(a + 1, b + 1, n<<2): 比较两个数组是否完全相同（n<<2 = n*4字节）
如果相同，输出0和步数并退出
找出所有a[i]≠b[i]的位置
按深度排序，以便后续处理
如果不匹配位置不在同一条路径上，输出-1
确保lu<lv
构建从lu经lt到lv的路径
反转前半段以正确排序
建立节点到环索引的映射
计算关键的LCA值
将路径从lt到root的节点收集到bc数组
将这些节点的值向上移动
提取环上值到A和B数组
计算旋转偏移量
验证是否可以通过旋转匹配
根据LCA关系选择不同的计算公式
输出起始位置和总距离

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5;

int to[N<<1], nxt[N<<1], head[N], cnt;
void add(int u, int v) {
    to[++cnt] = v, nxt[cnt] = head[u], head[u] = cnt;
    to[++cnt] = u, nxt[cnt] = head[v], head[v] = cnt;
}

int p[N], dep[N];
void dfs(int x) {//建立父子关系和深度信息
    for (int i = head[x], y; i; i = nxt[i]) {
        if ((y=to[i]) != p[x])
            p[y] = x, dep[y] = dep[x] + 1, dfs(y);
    }
}
int LCA(int x, int y) {//通过向上跳跃找到最近公共祖先
    for (; x != y; dep[x] < dep[y] ? y = p[y] : x = p[x]) {}
    return x;
}

int dif, bc[N], lu, lv, lt;
bool get() {
    int i;
    for (i = 1; i < dif && p[bc[i]] == bc[i-1]; ++i) {}
    if (i == dif) return lt = lu = p[*bc], lv = bc[dif-1], true;
    lu = lv = lt = p[*bc];
    for (i = 0; i < dif; ++i) {
        if (p[bc[i]] == lu) lu = bc[i];
        else if (p[bc[i]] == lv) lv = bc[i];
        else return false;
    }
    return true;
}

int dmx(const int x, const int y) {//返回深度更大的节点
    return dep[x] < dep[y] ? y : x;
}

int n, i, a[N], b[N], u, v, rt, cyc[N], len, in[N], w, z, j, A[N], B[N], ofs;
ll D;
int main() {
    fast;
    cin >> n;
    for (i = 1; i <= n; ++i) cin >> a[i];
    for (i = 1; i <= n; ++i) cin >> b[i];
    for (i = 1; i < n; ++i) {
        cin >> u >> v; add(u, v);
    }
    dfs(rt = find(b + 1, b + n + 1, 0) - b);
    u = v = find(a + 1, a + n + 1, 0) - a;
    for (i = 0; u != rt; ++i) swap(a[u], a[p[u]]), u = p[u];
    if (!memcmp(a + 1, b + 1, n<<2))
        return printf("0 %d\n", i), 0;
    for (i = 1; i <= n; ++i)
        if (a[i] != b[i]) bc[dif++] = i;
    sort(bc, bc + dif, [](const int x, const int y) {
        return dep[x] < dep[y];
    });
    if (!get()) return puts("-1"), 0;
    if (lu > lv) swap(lu, lv);
    cyc[len++] = lt;
    for (i = lu; i != lt; i = p[i]) cyc[len++] = i;
    reverse(cyc + 1, cyc + len);
    for (i = lv; i != lt; i = p[i]) cyc[len++] = i;
    for (i = 0; i < len; ++i) in[cyc[i]] = i;
    assert(len > 2);
    w = LCA(v, lt);
    if (w == lt) z = dmx(LCA(v, lu), LCA(v, lv));
#define proc() \
    for (j = 0, i = lt; i != rt; i = p[i]) bc[j++] = i; \
    for (; j--; swap(a[bc[j]], a[p[bc[j]]]), swap(b[bc[j]], b[p[bc[j]]])) {} \
    for (i = 0; i < len; ++i) A[i] = a[cyc[i]], B[i] = b[cyc[i]]; \
    assert(!(*A || *B)); \
    ofs = find(A + 1, A + len, B[1]) - A; \
    if (ofs >= len || memcmp(A + 1, B + len - ofs + 1, (ofs - 1)<<2) \
                   || memcmp(A + ofs, B + 1, (len - ofs)<<2)) return puts("-1"), 0;
    if (w == lt && w != z) {
        if ((in[z] + 1) % len != in[p[z]])
            for (reverse(cyc + 1, cyc + len), i = 0; i < len; ++i)
                in[cyc[i]] = i;
        assert((in[z] + 1) % len == in[p[z]]);
        proc();
        D = dep[v] + min(len*(ofs-1ll), (ll)len*(len-ofs)-2*(dep[z]-dep[w]));
    } else {
        proc();
        D = dep[v] + 2*(dep[lt] - dep[w]) + (ll)len*min(ofs-1, len-ofs);
    }
    printf("%d %d %lld\n", lu, lv, D);
    return 0;
}