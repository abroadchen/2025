//
// Created by Psy.C on 2025/11/5.
//
/*
*x[N], t[N]: 存储输入的坐标和时间
v: 速度参数
a[N]: 用于LIS算法的辅助数组
ans1, ans2: 存储两个答案
Node 结构体：表示二维点，重载小于运算符用于排序
按x坐标升序，x相同时按y坐标升序
 *
 *将原始坐标(x[i], t[i])转换为新的二维坐标(s[i].x, s[i].y)
 *对转换后的点按x坐标（然后y坐标）进行排序
 *
*使用二分查找优化的LIS算法计算最长上升子序列
在所有转换后的点中找y坐标最长递增子序列
upper_bound 找到第一个大于 s[i].y 的位置
tot 记录当前LIS长度
 *
*只考虑x≥0且y≥0的第一象限内的点
同样计算这些点中y坐标的最长递增子序列
结果存储在ans2中
 *
 *
*排序：O(n log n)
两次LIS计算：O(n log n)
总体：O(n log n)
 */
#include <algorithm>
#include <cstdio>
#define rep(i,n) for(int i=1;i<=(n);++i)
using namespace std;

typedef long long ll;
const int N = 200010;
ll x[N], t[N], v, a[N];
int ans1, ans2;

struct Node {
    ll x, y;
    friend bool operator<(Node a, Node b) {
        if (a.x == b.x) return a.y < b.y;
        return a.x < b.x;
    }
} s[N];


int main() {
    int n; scanf("%d", &n);
    rep(i,n) scanf("%lld%lld", &x[i], &t[i]);
    scanf("%lld", &v);
    rep(i,n) { s[i].x = x[i] + t[i] * v; s[i].y = -x[i] + t[i] * v; }
    sort(s+1,s+n+1);
    int tot = 0, pos;
    rep(i,n) {
        pos = upper_bound(a + 1, a + tot + 1, s[i].y) - a;
        a[pos] = s[i].y;
        if (pos > tot) tot = pos;
    }
    ans1 = tot; tot = 0;
    rep(i,n) {
        if (s[i].x < 0 || s[i].y < 0) continue;
        pos = upper_bound(a + 1, a + tot + 1, s[i].y) - a;
        a[pos] = s[i].y;
        if (pos > tot) tot = pos;
    }
    ans2 = tot;
    printf("%d\n%d\n", ans2, ans1);
    return 0;
}