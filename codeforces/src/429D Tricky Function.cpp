//
// Created by Psy.C on 2026/2/5.
//
/**
 *
 *b数组存储原始点，c数组用于分治过程中的临时存储
 *
*如果区间为空或只有一个点，返回无穷大
如果只有两个点，直接返回它们的距离平方
*找到中点mid
递归计算左半部分和右半部分的最近距离
取两者的最小值作为当前最优解
*从左半部分选取到中线距离平方小于当前最优解的点
从右半部分选取到中线距离平方小于当前最优解的点
只有这些点才可能构成更近的点对
*如果y坐标差的平方已经超过当前最优解，就没必要继续
更新最小距离
 *
 *构建点集：横坐标为位置i，纵坐标为前缀和sum[i]
 *时间复杂度O(n log n)
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100100
using namespace std;

constexpr ll inf = 8e18+1;

struct node { ll x, y; } b[N], c[N];
ll sqr(const ll x) { return x * x; }
ll dis(const node a, const node b1) {
    ll t = 0;
    t += sqr(a.x - b1.x);
    t += sqr(a.y - b1.y);
    return t;
}

ll dfs(const int l, const int r) {
    ll ret = inf;
    if (l >= r) return ret;
    if (l + 1 == r) return dis(b[l], b[r]);
    const int mid = (l + r) >> 1;
    int k = 0;
    const ll t1 = dfs(l, mid), t2 = dfs(mid + 1, r); ll t;
    ret = min(t1, t2);
    for (int i = mid; i >= l; --i) {
        t = sqr(b[i].x - b[mid].x);
        if (t > ret) break;
        c[++k] = b[i];
    }
    for (int i = mid + 1; i <= r; ++i) {
        t = sqr(b[i].x - b[mid].x);
        if (t > ret) break;
        c[++k] = b[i];
    }
    sort(c + 1, c + k + 1, [](const node a, const node b1) {
        return a.y < b1.y;
    });
    for (int i = 1; i <= k; ++i) for (int j = i + 1; j <= k; ++j) {
        t = sqr(c[j].y - c[i].y);
        if (t > ret) break;
        ret = min(ret, dis(c[i], c[j]));
    }
    return ret;
}

int main() {
    fast;
    int n; cin >> n;
    ll a[N]{}, sum[N]{};
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i];
    for (int i = 1; i <= n; ++i) b[i].x = i, b[i].y = sum[i];
    sort(b + 1, b + n + 1, [](const node a1, const node b1) {
        return a1.x < b1.x;
    });
    cout << dfs(1, n) << '\n';
    return 0;
}