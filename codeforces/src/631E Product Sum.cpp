//
// Created by Psy.C on 2026/3/29.
//
/**
X(i) = i：横坐标是索引
Y(i) = b[i]：纵坐标是前缀和
fz(x,y)：两点间的纵坐标差
fm(x,y)：两点间的横坐标差
维护一个下凸包（斜率单调递增）
fz(q[ed], q[ed-1])/fm(q[ed], q[ed-1]) 是相邻两点间斜率
二分查找最优决策点
寻找斜率小于等于val的最远点
val是当前查询的斜率（即a[i]）
对于每个位置i，找到最优的j使得(j-i)*a[i]+b[i]-b[j]最大

凸包构建：O(n)
查询：O(n log n)（每次查询log n）
总体：O(n log n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

template<typename T>
void mxx(T &x, T y) { (x < y) && ((x = y)); }

constexpr int N = 2e5+5;

ll X(int x) { return x; }
ll b[N];
ll Y(int x) { return b[x]; }
ll fz(int x, int y) { return Y(x) - Y(y); }
ll fm(int x, int y) { return X(x) - X(y); }

int ed = 1, q[N];
int get(ll val) {
    int l = 2, r = ed, cur = 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (fz(q[mid], q[mid-1]) <= val*fm(q[mid], q[mid-1]))
            l = mid + 1, cur = mid;
        else r = mid - 1;
    }
    return q[cur];
}

ll n, a[N], ans, ret;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        b[i] = b[i-1] + a[i];
        ans = ans + i * a[i];
    }
    for (int i = 1; i <= n; ++i) {
        while (ed > 1 && fz(q[ed], q[ed-1])*fm(i, q[ed]) >=
            fz(i, q[ed])*fm(q[ed], q[ed-1])) ed--;
        q[++ed] = i;
    }
    for (int i = 1; i <= n; ++i) {
        int j = get(a[i]);
        mxx(ret, (j-i)*a[i]+b[i]-b[j]);
    }
    cout << ans+ret << '\n';
    return 0;
}