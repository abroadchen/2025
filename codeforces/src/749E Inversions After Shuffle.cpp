//
// Created by Psy.C on 2026/8/27.
//
/**
- double t[N] ： 树状数组 本体，用 double 类型存储累加的权重值（因为涉及浮点数运算）。
- int n ：全局变量，数组长度（树状数组的大小上限）

树状数组的单点更新函数 ，给位置 x 加上增量 k ：
- for (; x <= n; x += lowbit(x)) ：从位置 x 开始，沿着 父节点路径向上 累加，直到超出数组边界。
  - x += lowbit(x) ：跳到下一个管辖 x 的父节点（关键跳跃规则）。
- t[x] += k ：在当前节点处累加增量
树状数组的前缀和查询函数 ，返回位置 1~x 的累加值：
- double ans = 0 ：初始化结果。
- for (; x; x -= lowbit(x)) ：从位置 x 开始，沿着 子节点路径向下 累加，直到 x 变为0。
  - x -= lowbit(x) ：跳回上一个不重叠的管辖区域。
- ans += t[x] ：累加当前节点的值。
- 返回前缀和

- 读入数组长度 n 。
- 读入 n 个整数 存入 a[1..n]
i 当前元素的下标（从1到n）
n-i 当前位置后面还有多少个元素
(n-i+1) 某种计数因子
n*(n+1)/2 总区间数（所有子区间的数量）

- 1.*i*(n-i)*(n-i+1)/(2.*n*(n+1)) 可以理解为 位置 i 对总期望的基础贡献 。
- 2.*n*(n+1) = n*(n+1)*2 是归一化因子（总区间数×2）。
- 累加所有位置得到初始期望值 ans

从后往前遍历，利用树状数组统计 重复的贡献项 并减去。
 核心逻辑
- add(a[i], n-i+1) ：将位置 i 的值 a[i] 及其权重 (n-i+1) 加入树状数组：
  - a[i] ：值作为下标（假设值≤n）。
  - n-i+1 ：位置 i 后面有多少个元素的因子。
- query(a[i]) ：查询树状数组中**值 < a[i]**的位置的累计权重：
  - 因为 query(x) 返回 1~x 的前缀和，所以 query(a[i]) 就是所有值≤ a[i] 的累计权重。
- 减去重复项 ： ans -= query(a[i]) * i * 2 / (n*(n+1)) ：
  - query(a[i]) ：当前值 a[i] 前面（已处理的，因为倒序遍历）所有比它小或等于的值的累计权重。
  - i ：当前位置的因子。
  - 2 / (n*(n+1)) ：归一化系数。
数学意义 ：减去所有 值比当前位置小 的元素带来的 重复区间贡献
用 memset 将树状数组清零，准备下一轮计算。 sizeof t 直接计算整个数组大小（ double 数组，约1.6MB）

第二轮倒序循环，利用树状数组统计 遗漏的贡献项 并加回
- add(a[i], 1) ：每次加入权重1（标记值 a[i] 已出现）。
- query(a[i]) ：当前值 a[i] 前面（已处理的）所有值≤ a[i] 的 个数 。
- ans += query(a[i]) ：将这些 遗漏的区间贡献 加回

cout 的默认精度只有6位
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;
//提取整数 x 的 最低位的1 及其后面的0组成的数
//用于确定数组下标的父子关系和管辖范
int lowbit(int x) { return x & -x; }

double t[N];
int n;
void add(int x, double k) {
    for (; x <= n; x += lowbit(x)) t[x] += k;
}

double query(int x) {
    double ans = 0;
    for (; x; x -= lowbit(x)) ans += t[x];
    return ans;
}

//存储输入的整数数组，下标从 1 到 n
int a[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    double ans = 0;
    for (int i = 1; i <= n; ++i)
        ans += 1.*i*(n-i)*(n-i+1)/(2.*n*(n+1));
    for (int i = n; i >= 1; --i) {
        ans -= query(a[i])*i*2./(1.*n*(n+1));
        add(a[i], n-i+1);
    }
    memset(t, 0, sizeof t);
    for (int i = n; i >= 1; --i) {
        ans += query(a[i]);
        add(a[i], 1);
    }
    printf("%.10lf", ans);
    return 0;
}