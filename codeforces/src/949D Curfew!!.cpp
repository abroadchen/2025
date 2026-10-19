//
// Created by Psy.C on 2026/10/18.
//
/**
核心逻辑：左右两个"清扫区间"从两端对称向内推进，每个守卫（共 f 个？）消耗能量 b，靠沿途仓库 a[p] 补给。dis 是到当前位置为止"允许推进的最大距离配额"，若实际推进超配额则失败。

这对应一道经典题：两个塔/守卫从数组两端向中间靠拢，每个守卫按顺序吃沿途数值以获取能量，问最少删掉多少个元素使两端守卫能顺利清扫到中间 —— 二分"要删的个数 f"
对答案 mid（要删/要处理的位置偏移量）做二分，求最小的可行解。每次二分都 memcpy 重置 a 为初始数组，防止 check 里修改了数组影响下次判定
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e5+5;

int d, p0, p1, lm, n, s, b, a[N];
ll dis;
bool check(int f) {
    //初始"可移动距离" = d * f
    dis = 1ll*d*f; p0 = 1; p1 = n;//双指针：左指针, 右指针
    for (int i = f+1; i <= lm; ++i) {
        //距离配额每天/每步增多 d
        dis += d; s = b;//当前枪手能量
        while (a[p0] < s) s -= a[p0++];//用仓库补给，直到够
        a[p0] -= s;//扣除
        if (p0 - i > dis) return 0;//左推进距离超过配额 → 失败
        if (i == lm && (n&1)) break;//奇数长度，中间特殊处理
        s = b;
        while (a[p1] < s) s -= a[p1--];//右指针对称清理
        a[p1] -= s;
        if ((n-i+1) - p1 > dis) return 0;//右推进距离超过配额 → 失败
    }
    return 1;
}
inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int c[N], l, r, ans;
int main() {
    fast;
    n = rd(), d = rd(), b = rd(); lm = (n+1) >> 1;
    for (int i = 1; i <= n; ++i) c[i] = a[i] = rd();
    l = 0, r = n + 1;
    while (l <= r) {
        int mid = (l+r)>>1;
        memcpy(a, c, sizeof(c));//每次二分前恢复原数组
        if (check(mid)) ans = mid, r = mid-1;
        else l = mid+1;
    }
    cout << ans << '\n';
    return 0;
}