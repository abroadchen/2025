//
// Created by Psy.C on 2026/9/18.
//
/**
node {tot, m}：tot 表示纪念品的魅力值（价值）‍，m 表示价格。
两个数组 a1（用 C 货币购买的）和 a2（用 D 货币购买的）。
树状数组维护前缀最大值：
update(k, x)：在位置 k 处与 x 取 max，并向上传染（树状数组只存 max）。
sum(k)：查询前缀 [1..k] 的 max。
注意 update 是向后更新 k += low_bit，sum 是向前累加 k -= low_bit——即下标越大表示价格越贵
读入 n 件纪念品，分类为 C 类（用 c 预算）和 D 类（用 d 预算），只保留价格在自己预算内的。
ans1 记录 C 类里单件最大价值，ans2 记录 D 类单件最大价值。
若两类都至少有一件，ans = ans1 + ans2（表示"各自买一件最贵的"这一可行方案）
遍历每件 a1[i]，用树状数组查询 [1, c-a1[i].m] 这段（即剩余预算 c 减去当前这件的价格内）历史出现过的最大的单件价值 s。
若 s > 0（之前有一件可配），则可能答案为 s + a1[i].tot（两件合买），更新答案。
处理完当前件后，把它按价格 m 插入树状数组（update(a1[i].m, a1[i].tot)）。
这样，对于每件商品，都能找到"在剩余预算内另一件最贵的"，从而得到同一货币内买两件的最大价值。因为树状数组按价格索引，所以能保证两件加起来不超过 c
与第三步完全对称，换成 D 预算 d 和 a2 数组。
C 类和 D 类各自内部找"两件"的最大组合，取最大值更新 ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;

struct node { int tot, m; } a1[N], a2[N];
int low_bit(int x) { return x & -x; }

int b[N];
void update(int k, int x) { while (k < N) { b[k] = max(b[k], x); k += low_bit(k); } }
int sum(int k) {
    int t = 0;
    while (k > 0) { t = max(t, b[k]); k -= low_bit(k); }
    return t;
}

int cnt, cnt2, ans1 = INT_MIN, ans2 = INT_MIN, ans;
int main() {
    fast;
    int n, c, d; cin >> n >> c >> d;
    while (n--) {
        int x, m;
        char opt; cin >> x >> m >> opt;
        if (opt == 'C') {
            if (m <= c) {
                a1[++cnt].tot = x;
                a1[cnt].m = m;
                ans1 = max(ans1, x);
            }
        } else {
            if (m <= d) {
                a2[++cnt2].tot = x;
                a2[cnt2].m = m;
                ans2 = max(ans2, x);
            }
        }
    }
    if (ans1 != INT_MIN && ans2 != INT_MIN) ans = ans1 + ans2;
    memset(b, 0, sizeof b);
    for (int i = 1; i <= cnt; ++i) {
        int s = sum(c-a1[i].m);
        if (s > 0) ans = max(ans, s+a1[i].tot);
        update(a1[i].m, a1[i].tot);
    }
    memset(b, 0, sizeof b);
    for (int i = 1; i <= cnt2; ++i) {
        int s = sum(d-a2[i].m);
        if (s > 0) ans = max(ans, s+a2[i].tot);
        update(a2[i].m, a2[i].tot);
    }
    cout << ans;
    return 0;
}