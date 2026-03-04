//
// Created by Psy.C on 2026/3/4.
//
/**
遍历每个节点：
- 如果节点被标记为被支配（ v[i] 为1）或者 ok(p[i], p[s[t]]) > 0 ，则跳过。
- 否则，维护一个栈结构，确保栈中节点满足某种最优条件：
  - 当栈大小大于1，且当前节点与栈顶节点的 ok 值小于栈顶两个节点的 ok 值时，弹出栈顶节点。
  - 将当前节点入栈。
遍历栈中的每个节点：
- 标记其原始编号为答案（ ans[p[s[i]].id] = 1 ）。
- 同时标记所有与该节点 a 和 b 值相同的后续节点（可能是重复的最优解）
遍历所有节点，输出被标记为答案的节点的原始编号
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ld long double
using namespace std;

inline ll read() {
    int f = 0, ch = 0; ll x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
constexpr int N = 3e5+1;
struct node { ll a, b, id; } p[N];
ld ok(const node &a, const node &b) {
    return 1.*a.a*b.a*(b.b-a.b)/(b.a-a.a)/b.b/a.b;
}

ll n, s[N], t, v[N], ans[N];
int main() {
    fast;
    n = read();
    for (int i = 1; i <= n; ++i)
        p[i].a = read(), p[i].b = read(), p[i].id = i;
    sort(p + 1, p + n + 1, [](const node &a, const node &b) {
        if (a.a == b.a) return a.b > b.b;
        return a.a > b.a;
    });
    s[1] = 1, t = 1;//将第一个节点（排序后的）入栈，栈大小 t 为1
    ll mx = p[1].b;
    for (int i = 2; i <= n; ++i) {
        if (p[i].b <= mx) v[i] = 1;
        else mx = p[i].b;
    }
    for (int i = 2; i <= n; ++i) {
        if (v[i] || ok(p[i], p[s[t]]) > 0) continue;
        while (t > 1 && ok(p[i], p[s[t]]) < ok(p[s[t-1]], p[s[t]]))
            t--;
        s[++t] = i;
    }
    for (int i = 1; i <= t; ++i) {
        ans[p[s[i]].id] = 1;
        for (ll j = s[i]+1; j <= n && p[s[i]].a == p[j].a && p[s[i]].b == p[j].b; ++j)
            ans[p[j].id] = 1;
    }
    for (int i = 1; i <= n; ++i)
        if (ans[i]) cout << i << ' ';
    return 0;
}