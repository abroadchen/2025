//
// Created by Psy.C on 2026/4/15.
//
/**
x, y：坐标点
v：权值（+1表示矩形开始，-1表示矩形结束）
重载<运算符：按x坐标排序

n, K：输入参数（n个矩形，边长为K）
b：离散化的y坐标数组
cnt：离散化后坐标数量
ls[j]：第j段上次计算面积的时间（x坐标）
cn[j]：第j段当前覆盖的矩形数量
rs[i]：第i个矩形贡献的面积
创建事件：每个矩形产生两个事件：开始事件(x-K, y, +1)和结束事件(x, y, -1)
离散化准备：收集所有需要的y坐标值
排序和去重：对y坐标进行排序并去除重复值
事件排序：按x坐标对所有事件排序
定位区间：找到当前事件影响的y坐标区间[l, r]
面积计算：对每个y段计算新增面积 = 宽度 × 高度
更新状态：更新该段的最后处理时间和覆盖数量
时间复杂度为O(n log n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5;

struct node {
    int x, y, v;
    char operator<(const node &o) const {
        return x < o.x;
    }
} a[N];

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

template<typename T,typename... Args>
void rd(T& t,Args&... args) {
    rd(t); rd(args...);
}

int n, K, b[N], cnt, ls[N], cn[N];
ll rs[N];
int main() {
    fast;
    rd(n, K);
    for (int i = 1, x, y; i <= n; ++i) {
        rd(x, y);
        a[i] = {x - K, y, 1}; a[i+n] = {x, y, -1};
        b[++cnt] = y; b[++cnt] = y - K;
    }
    sort(b + 1, b + cnt + 1);
    cnt = unique(b + 1, b + cnt + 1) - b - 1;
    sort(a + 1, a + n + n + 1);
    for (int i = 1; i <= n+n; ++i) {
        int l = lower_bound(b + 1, b + cnt + 1, a[i].y-K) - b,
        r = lower_bound(b + 1, b + cnt + 1, a[i].y) - b;
        for (int j = l+1; j <= r; ++j) {
            rs[cn[j]] += 1ll*(b[j]-b[j-1])*(a[i].x-ls[j]);
            ls[j] = a[i].x, cn[j] += a[i].v;
        }
    }
    for (int i = 1; i <= n; ++i)
        cout << rs[i] << " \n"[i==n];
    return 0;
}