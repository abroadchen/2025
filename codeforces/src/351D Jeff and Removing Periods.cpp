//
// Created by Psy.C on 2026/1/16.
//
/**
* sum: 线段树数组，大小为4*N
K: 用于位运算的掩码 表示线段树的大小
*build函数：找到大于等于n的最小2的幂次
用于线段树的位运算索引
*add函数：在位置k处增加x
k += K: 转换到线段树的实际索引
向上更新所有父节点
*query函数：查询区间[l,r]的和
使用位运算实现的区间查询
~l&1: 检查l是否为偶数
r&1: 检查r是否为奇数
l^r^1: 当l和r相邻时终止循环
如果是偶数l，l^1=l+1；如果是奇数l，l^1=l-1
如果是奇数r，r^1=r-1；如果是偶数r，r^1=r+1

声明tr1和tr2两个线段树实例
 *
*fa[i]: 元素i的上一次出现位置
pre[i]: 用于追踪等差子序列的辅助数组
lst[x]: 值x最后出现的位置
 *
*fa[i] = lst[x]: 记录x上一次出现的位置
lst[x] = i: 更新x最后出现的位置
pre[i]: 如果当前位置、上次位置、上上次位置形成等差数列，继承pre值；否则设为上上次位置
 *
*离线处理查询
cur: 当前处理到的位置
当cur < r时，逐步扩展到r
更新线段树：
tr1: 维护fa关系的变化
tr2: 维护pre关系的变化
 *
*a ^ a = 0 （任何数与自己异或为0）
a ^ 0 = a （任何数与0异或为自己）
a ^ 1 等价于 a 的最低位取反
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;

int n;
struct node {
    int sum[N<<2], K;
    void build() { for (K = 1; K <= n; K <<= 1) {} }
    void add(int k, const int x) {
        if (!k) return;
        for (k += K; k; k >>= 1) sum[k] += x;
    }
    [[nodiscard]] int query(int l, int r) const {
        int ans = 0;
        for (l += K - 1, r += K + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
            if (~l&1) ans += sum[l^1];
            if (r&1) ans += sum[r^1];
        }
        return ans;
    }
} tr1, tr2;

struct node2 {
    int l, r, id;
    friend bool operator<(const node2 o1, const node2 o2) {
        return o1.r < o2.r;
    }
} q[N];

int main() {
    fast;
    cin >> n; tr1.build(); tr2.build();
    int fa[N], pre[N], lst[N];
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        fa[i] = lst[x]; lst[x] = i;
        pre[i] = fa[i] - fa[fa[i]] == i - fa[i] ? pre[fa[i]] : fa[fa[i]];
    }
    int x, ans[N]; cin >> x;
    for (int i = 1; i <= x; ++i) {
        cin >> q[i].l >> q[i].r; q[i].id = i;
    }
    sort(q + 1, q + x + 1);
    for (int i = 1, cur = 0; i <= x; ++i) {
        const int l = q[i].l, r = q[i].r;
        while (cur < r) {
            cur++;
            tr1.add(fa[cur], -1);
            tr1.add(cur, 1);
            tr2.add(pre[fa[cur]], -1);
            tr2.add(pre[cur], 1);
        }
        const int t1 = tr1.query(l, r), t2 = tr2.query(l, r);
        ans[q[i].id] = t1 + (t1 == t2);
    }
    for (int i = 1; i <= x; ++i) cout << ans[i] << '\n';
    return 0;
}