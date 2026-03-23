//
// Created by Psy.C on 2026/3/23.
//
/**
tot记录当前边的数量
e[N]存储边数组
add函数添加一条边，使用minmax确保较小值在前
ok函数检查是否已经有n-1条边
out函数排序并输出所有边
存储10的幂值
计算x的"位数等级"，即找到最大的i使得10^i < x
A: 某种掩码值
w[M]: 各位数区间剩余数量
l: 位数等级
cnt[M][M]: 统计不同长度字符串之间的连接数

实现霍尔定理的验证，检查是否存在完美匹配
枚举所有可能的子集S
s: 当前子集中包含的元素数量总和
t: 当前子集内部及与外部的边数总和
如果t<s则违反霍尔条件
s1,s2: 临时存储输入的字符串
mv[M]: 记录各区间当前使用的编号
flag: 标记位

输入n，计算位数等级l，计算掩码A
读入n-1条边，统计不同长度字符串之间的连接数
初始化每个长度区间的数字总数
处理自环（相同长度的字符串之间的连接）
将自环转换为连续数字之间的边
如果某个区间的剩余数量小于等于0，则无解
验证初始状态是否满足霍尔条件
复制pw10数组到mv数组

逐步构建解决方案
减少第一个区间的数量，增加起始编号
在不违反霍尔条件的前提下添加边
如果添加某条边后仍满足霍尔条件，则保留该边



for (S = 1; S < A; ++S)：S作为位掩码，遍历从1到A-1的所有子集
for (u = S; u; u &= u-1)：Brian Kernighan算法，遍历S中的每一位1
u &= u-1：清除u的最低位的1
ctz(u)：找到当前最低位1的位置
s += w[ctz(u)]：累加子集中各位置的权重
if ((S>>u|S>>v)&1)：检查u或v是否在子集S中
霍尔定理：对于任意子集，其邻居集合的大小应不小于子集本身大小

-2的二进制是...11110
(-2<<l)将-2左移l位
~按位取反得到掩码
w[i] = pw10[i+1] - pw10[i]：长度为i+1的数字个数
w[i] = n - pw10[i] + 1：最后一个区间特殊处理
for (j = cnt[i][i]/2; j; --j, --w[i])：每条自环对应一条边
O::add(...)：添加连续编号的边
if (cnt[i][i] = 0, w[i] <= 0)：同时赋值cnt[i][i]=0并检查w[i]
(l+1)<<2：相当于(l+1)*4，因为int占4字节
--*w, ++*mv：减少第一个区间的可用数量，增加起始编号
for (v = flag; v; v &= v-1)：遍历flag标记的位置
i = ctz(v)：获取当前处理的位置
if (cnt[i][j] && w[j])：检查是否有边且j区有资源
尝试移除边并检查霍尔条件
满足条件则添加边并更新标志
不满足则恢复原状态

每条边被计算了两次，则除以2来修正

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
#define ctz __builtin_ctz///二进制表示中末尾0的个数
using namespace std;
constexpr int N = 2e5+5, M = 6;

int n;
namespace O {
    int tot = 0;
    ii e[N];
    void add(int x, int y) { e[tot++] = minmax(x, y); }
    bool ok() { return tot == n - 1; }
    int out() {
        sort(e, e + tot);
        for (int i = 0; i < tot; ++i)
            cout << e[i].first << ' ' << e[i].second << '\n';
        return 0;
    }
}

int pw10[] = {1, 10, 100, 1000, 10000, 100000};
inline int Log(const int x) {
    return upper_bound(pw10, pw10 + M, x) - pw10 - 1;
}

int A, w[M], l, cnt[M][M];
inline bool Hall() {
    int u, v, S, s, t;
    for (S = 1; S < A; ++S) {//遍历所有非空子集
        s = t = 0;//初始化子集大小和边数
        for (u = S; u; u &= u-1) s += w[ctz(u)];//子集中元素的权重和
        for (u = 0; u < l; ++u)//子集内部和连接的边数
            for (v = u + 1; v <= l; ++v)
                if ((S>>u|S>>v)&1) t += cnt[u][v];//u或v在子集中
        if (t < s) return false;
    }
    return true;
}

char s1[8], s2[8];
int mv[M], flag = 1;
int main() {
    fast;
    cin >> n; l = Log(n), A = ~(-2<<l);
    int i, j, u, v;
    for (i = 1; i < n; ++i) {
        cin >> s1 >> s2; u = strlen(s1) - 1; v = strlen(s2) - 1;
        ++cnt[u][v], ++cnt[v][u];
    }
    for (i = 0; i < l; ++i) w[i] = pw10[i+1] - pw10[i];
    w[i] = n - pw10[i] + 1;
    for (i = 0; i <= l; ++i) {
        for (j = cnt[i][i]/2; j; --j, --w[i])
            O::add(pw10[i] + w[i] - 2, pw10[i] + w[i] - 1);
        if (cnt[i][i] = 0, w[i] <= 0)
            return puts("-1"), 0;
    }
    if (!Hall()) return puts("-1"), 0;
    memcpy(mv, pw10, (l+1)<<2);
    for (--*w, ++*mv; !O::ok(); )
        for (v = flag; v; v &= v-1)
            for (i = ctz(v), j = 0; j <= l; ++j) if (cnt[i][j] && w[j]) {
                --cnt[i][j], --cnt[j][i], --w[j];
                if (Hall()) {
                    O::add(pw10[i], mv[j]++);
                    flag |= 1<<j;
                    continue;
                }
                ++cnt[i][j], ++cnt[j][i], ++w[j];
            }
    return O::out(), 0;
}