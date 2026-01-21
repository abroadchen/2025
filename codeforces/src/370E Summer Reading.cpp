//
// Created by Psy.C on 2026/1/21.
//
/**
* l[i]: 第i位的下界，连续出现不超过5次后递增
u[i]: 第i位的上界，连续出现不超过2次后递增
 *
*如果原数组指定了值a[i]，则必须满足 l[i].v ≤ a[i] ≤ u[i].v
更新上下界约束
 *
*从后往前构造答案
vis[val]记录每个值的使用次数
当某个值使用达到5次时，需要递减val（因为连续出现不能超过5次）
 *
 *时间复杂度: O(n)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000005
using namespace std;

struct node {
    int v, t;//当前值 该值的出现次数
    friend bool operator<(const node a, const node b) {
        if (a.v != b.v) return a.v < b.v;
        return a.t < b.t;
    }
} l[N], u[N];

int n, a[N];
void init() {
    l[1] = u[1] = {1, 1};
    for (int i = 2; i <= n; ++i) {
        l[i] = l[i-1], u[i] = u[i-1];
        if (++l[i].t > 5) l[i] = {l[i].v + 1, 1};
        if (++u[i].t > 2) u[i] = {u[i].v + 1, 1};
        if (a[i] != 0) {
            if (l[i].v > a[i] || u[i].v < a[i]) {
                cout << "-1"; exit(0);
            }
            l[i] = max(l[i], {a[i], 1});//确保位置i的值至少为a[i]
            u[i] = min(u[i], {a[i], 5});//确保位置i的值至多为a[i]
        }
        if (l[i].v > u[i].v) { cout << "-1"; exit(0); }
    }
}

int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    if (a[1] > 1) { cout << "-1"; exit(0); }
    init();
    //前一个值 u[n].v - 1 才是完整的约束范围
    int val = u[n].v - (u[n].t == 1), ans[N];
    if (l[n].v > val) { cout << "-1"; exit(0); }
    for (int i = n, vis[N]; i >= 1; --i) {
        val = min(val, u[i].v);
        val -= vis[val] == 5;
        ans[i] = val, vis[val]++;
    }
    if (ans[1] <= 0) { cout << "-1"; exit(0); }
    cout << ans[n] << '\n';
    for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
    return 0;
}