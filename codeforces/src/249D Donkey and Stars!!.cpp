//
// Created by Psy.C on 2025/12/16.
//
/*
*n：数组大小
s[N]：树状数组存储
lb(x)：定义lowbit函数，计算x的最低位1
clear：初始化函数，清空树状数组
*树状数组修改操作
在位置x处更新最大值t
向上更新所有相关节点
*树状数组查询操作
查询[1,x]范围内最大值
向下累加所有相关节点
 *
*
坐标变换：将原坐标转换为新的坐标系
a = p[i].x * a2.y - a2.x * p[i].y （叉积相关计算）
b = a1.x * p[i].y - p[i].x * a1.y （叉积相关计算）
将变换后的y坐标存储在数组y中用于离散化
*对y坐标进行排序和去重
实现离散化，减少坐标范围
 *将变换后的y坐标映射到离散化后的值
 *
*动态规划计算最长上升子序列
双指针技术：j指向所有x坐标小于当前点的点
将这些点的信息插入树状数组
查询当前位置之前的最优解，更新dp值
 *
*排序：O(n log n)
DP计算：O(n log n)
总体：O(n log n)

减1是为了查询严格小于当前y坐标的所有位置的最大值
表示在之前的最优序列基础上，再加上当前点形成的更长序列

static_cast<int>(p[j].y)：
将点p[j]的y坐标转换为整数
这是树状数组中要修改的位置
dp[p[j].id]：
获取点p[j]的dp值（即以点j结尾的最长上升子序列长度）
t.modify(pos, val)：
在树状数组的位置pos处更新值val
具体来说，是在位置p[j].y维护dp[p[j].id]这个值
 *
*i：当前正在处理的点
j：所有已经处理过但还未加入树状数组的点
 *
 *lower_bound：在已排序数组中查找第一个大于等于目标值的位置
*lower_bound(...) - y
结果：返回找到位置的指针
减去y：将指针转换为相对于数组起始位置的索引（从0开始）
*+ 1
将索引从0-based转换为1-based
 *
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100010
using namespace std;

struct point { ll x, y; int id; } p[N], a1, a2;
struct node {
    int n, s[N];
#define lb(x) ((x)&(-x))
    void clear(const int _n) {
        n = _n;
        memset(s, 0, sizeof(s));
    }
    void modify(int x, const int t) {
        for (; x <= n; x += lb(x)) s[x] = max(s[x], t);
    }
    int query(int x) const {
        int ans = 0;
        for (; x; x -= lb(x)) ans = max(ans, s[x]);
        return ans;
    }
} t;

bool operator<(const point& a, const point& b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;//按x坐标升序，x相同时按y坐标升序
}

int main() {
    fast;
    p[0].x = p[0].y = 0; p[0].id = 0;
    int n; cin>>n; char ch;
    cin >> a1.y >> ch >> a1.x; cin >> a2.y >> ch >> a2.x;
    for (int i = 1; i <= n; ++i) { cin >> p[i].x >> p[i].y; p[i].id = i; }
    int tot = 0; ll y[N] = {};
    for (int i = 0; i <= n; ++i) {
        ll a = p[i].x * a2.y - a2.x * p[i].y,
        b = a1.x * p[i].y - p[i].x * a1.y;
        a *= -1, b *= -1;
        p[i].x = a; p[i].y = b;
        y[tot++] = b;
    }
    sort(y, y + tot);
    tot = static_cast<int>(unique(y, y + tot) - y);
    for (int i = 0; i <= n; ++i) p[i].y = lower_bound(y, y + tot, p[i].y) - y + 1;
    int dp[N] = {};
    sort(p, p + 1 + n); t.clear(n + 1);
    for (int i = 0, j = 0; i <= n; ++i) {
        while (p[j].x < p[i].x)  { t.modify(static_cast<int>(p[j].y), dp[p[j].id]); j++; }
        dp[p[i].id] = t.query(static_cast<int>(p[i].y)-1) + 1;
    }
    cout << dp[0] - 1 << '\n';//减1是因为包含了虚拟的起点
    return 0;
}