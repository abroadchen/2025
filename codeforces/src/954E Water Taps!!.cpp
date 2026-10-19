//
// Created by Psy.C on 2026/10/19.
//
/**
读入 n、T；每个元素读入 second（数量）累加到 t2，再读入 first（属性值）累加 A·num 到 t1。

整理：

t1 / t2 = 加权平均属性值。
T 是一个目标比值
把元素按属性值 A 降序排列。若整体加权平均 < T，则翻转符号（把 T 取负、A 取负、t1 取负、顺序翻转），使问题统一成"平均基础上往下删"。

这一大步是为了保证：总是从属性最低/最高端开始删，能让比值最优化
从属性最高的那端开始删除，只要当前 t1 > T*t2（即平均 > T）就一直删当前最大属性元素，把它的 A·num 和 num 从总和扣掉。删到平均降到 ≤ T 停止，并且 --i 回退一格（因为最后一个被删的可能删过头，需要部分保留）
最后一个下标 i 的元素可以只删一部分（数量用实数）。对它做二分，求出能保留/删除多少使得比值恰好满足条件，找到临界值 res。

t1, t2 是已删除完成（下标 >i 的都已删）后的剩余总和。
对第 i 个元素再删 mid 个，剩余总和为 t1 + mid*A[i]，个数 t2+mid。
条件 (t1+mid·A[i])/(t2+mid) ≤ T → 二分逼近临界 mid。
res 记录满足条件的最大 mid
最终剩余个数 = 已保留的整数部分 t2 + 第 i 个元素保留的分数部分 res。输出保留个数的最大值（10 位小数）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
#define ll long long
#define ii pair<int, int>
using namespace std;

constexpr int N = 2e5+1;


int n, T;
ii a[N];
ll t1, t2;
int main() {
    fast;
    cin >> n >> T;
    rep(i,n) cin >> a[i].second, t2 += a[i].second;
    rep(i,n) cin >> a[i].first, t1 += 1ll*a[i].first*a[i].second;
    sort(a, a+n); reverse(a, a+n);
    if (t1 < T*t2) {
        T *= -1;
        rep(i,n) a[i].first *= -1;
        reverse(a, a+n);
        t1 *= -1;
    }
    int i = 0;
    while (i < n && t1 > T*t2)
        t1 -= 1ll*a[i].first*a[i].second, t2 -= a[i].second, ++i;
    --i;
    double l = 0, r = a[i].second, mid, res = 0;
    rep(j,100) {
        mid = (l+r)/2;
        if (1ll*mid*a[i].first+t1 <= 1ll*T*(mid+t2)) res = l = mid;
        else r = mid;
    }
    printf("%.10lf\n", t2+res);
    return 0;
}