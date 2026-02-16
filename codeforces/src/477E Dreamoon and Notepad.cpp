//
// Created by Psy.C on 2026/2/16.
//
///时间复杂度：O(n log n + q log n)
#include <bits/stdc++.h>
#include <cmath>
using namespace std;

template<typename T> void mn(T& a, const T& b) { a > b && (a = b); }

constexpr int N = 4e5+5, M = 21, mod = 1e9+7;

struct node { int r1, c1, r2, c2, id; } q1[N], q2[N];

int n;
struct ST {
    int f[N][M];
    void build() {//区间最小值
        for (int j = 1; j < M; ++j)
            for (int i = 1; i + (1<<j) - 1 <= n; ++i)
                f[i][j] = min(f[i][j-1], f[i+(1<<(j-1))][j-1]);
    }
    [[nodiscard]] int query(const int l, const int r) const {//this指针为const
        const int j = log2(r - l + 1);//覆盖区间需要的最小2的幂次
        return min(f[l][j], f[r-(1<<j)+1][j]);//两个覆盖子区间的最小值
    }
} st1, st2, st3;

int a[N];
void build() {
    for (int i = 1; i <= n; ++i) {
        st1.f[i][0] = a[i];
        st2.f[i][0] = a[i] - 2*i;
        st3.f[i][0] = a[i] + 2*i;
    }
    st1.build(); st2.build(); st3.build();//为三种不同变换的数组构建ST表
}

int get(const int r1, const int c1, const int r2, const int c2) {
    int res = mod, l, r, mid;
    int r0 = 0;
    const int c0 = min(c1, st1.query(r1, r2));//c1和[r1,r2]区间最小值的较小者
    mn(res, r2 - r1 + abs(c2 - c0));
    mn(res, r2 - r1 + c2 + 1);
    l = r1, r = r2;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (st1.query(mid, r2) >= c2) r = mid-1, r0 = mid;
        else l = mid+1;
    }
    mn(res, r2 - r1 + st1.query(r0, r2) - c2 + 1);
    if (--r0 >= r1) mn(res, r2 - r1 + c2 - a[r0] + 1);
    if (c0 > c2) {
        l = 1, r = r1;
        while (l <= r) {
            mid = (l + r) >> 1;
            if (st1.query(mid, r1) >= c2) r = mid-1, r0 = mid;
            else l = mid+1;
        }
        mn(res, r1 + r2 - c2 + st2.query(r0, r1));
        if (--r0 >= 1) mn(res, r1 + r2 + c2 - 2*r0 - a[r0]);
    }
    if (st1.query(r1, r2) >= c2) {
        l = 1, r = r1;
        while (l <= r) {
            mid = (l + r) >> 1;
            if (st1.query(mid, r2) >= c2) r = mid-1, r0 = mid;
            else l = mid+1;
        }
        mn(res, r1 + r2 - c2 + st2.query(r0, r1) + 1);
        if (--r0 >= 1) mn(res, r1 + r2 + c2 - 2*r0 - a[r0] + 1);
    }
    if (c0 > c2) {
        l = r2, r = n;
        while (l <= r) {
            mid = (l + r) >> 1;
            if (st1.query(r2, mid) >= c2) l = mid+1, r0 = mid;
            else r = mid-1;
        }
        mn(res, st3.query(r2, r0) - (r1 + r2 + c2));
        if (++r0 <= n) mn(res, c2 - r1 - r2 + 2*r0 - a[r0]);
    }
    l = r2, r = n;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (st1.query(r2, mid) >= c2) l = mid+1, r0 = mid;
        else r = mid-1;
    }
    mn(res, st3.query(r2, r0) - (r1 + r2 + c2) + 1);
    if (++r0 <= n) mn(res, 2*r0 - r1 - r2 + c2 - a[r0] + 1);
    return res;
}

void read(int& x) {
    x = 0;
    int f = 1;
    char ch = getchar();
    while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
    while (isdigit(ch)) x = (x<<3)+(x<<1)+(ch&15), ch = getchar();
    x = x*f;
}

int q, cnt1, cnt2, ans[N];
int main() {
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]);
    read(q);
    for (int i = 1, r1, c1, r2, c2; i <= q; ++i) {
        read(r1), read(c1), read(r2), read(c2);
        if (r1 <= r2) q1[++cnt1] = {r1, c1, r2, c2, i};
        else q2[++cnt2] = {n-r1+1, c1, n-r2+1, c2, i};
    }
    build();
    for (int i = 1; i <= cnt1; ++i) {
        auto [r1, c1, r2, c2, id] = q1[i];
        const int res = get(r1, c1, r2, c2);
        ans[id] = res;
    }
    reverse(a + 1, a + n + 1); build();
    for (int i = 1; i <= cnt2; ++i) {
        auto [r1, c1, r2, c2, id] = q2[i];
        const int res = get(r1, c1, r2, c2);
        ans[id] = res;
    }
    for (int i = 1; i <= q; ++i) printf("%d\n", ans[i]);
    return 0;
}