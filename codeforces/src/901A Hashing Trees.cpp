//
// Created by Psy.C on 2026/10/10.
//
/**
n：层/序号，main 里读入后 n++（数组从 1 开始，多开一位）。
a[N]：a[i] = 第 i 层的节点个数（读入，a[1]=1 根节点）。
c[i] = 前缀和数组：c[i] = c[i-1] + a[i-1]，即前 i-1 层节点总数，用于给每层节点编号
遍历每一层 i：若第 i 层节点数 ≥ 2 且第 i-1 层节点数 ≥ 2，则输出 ambiguous（存在至少两种不同的合法树结构）；否则输出 perfect（树的构造唯一）。

判断依据：树的唯一性只在一个"分叉点"受影响——当某一层既有多个父节点（a[i-1]≥2）又有多个子节点（a[i]≥2）时，子节点可以"分配"给不同的父节点，从而产生不同父子关系，导致多解；否则每层只有一个方向可接，结构唯一
当判定为 ambiguous 时，调用 solve(i) 输出两种不同的父节点序列 ans 和 res，用于展示两种合法构造
c[i] = c[i-1] + a[i-1]：前缀和，c[i] = 前 i-1 层总节点数，因此第 i-1 层节点的编号范围是 [c[i-1], c[i]-1]（即 c[i-1] + 1 .. c[i-1]+a[i-1]）。于是 c[i-1] = 第 i-1 层第一个节点的编号（若从 0 编号则为该层首节点号）。

遍历每一层 i（从第 2 层起），对该层的每个节点 j（第 i 层节点数 a[i] 个）：

ans[++idx] = c[i-1]：方案 A 中，第 i 层的每个节点都把 c[i-1]（第 i-1 层第一个节点）作为父节点。即方案 A 让所有子节点挂到上一层第一个父节点上。

res[++k] = c[i-1]：方案 B 默认同样先让子节点挂到 c[i-1]。

然后有一个特定位置的改写
当把 B 的某个子节点（第 u 层内某个特定序号）设置父节点为 c[u-1]+a[u-1]-1，即上一层（第 u-1 层）的最后一个节点。这样方案 B 把"至少一个第 u-1 层的最后一个父节点也挂上子"，与方案 A（全挂第一个父节点）不同，从而得到两种不同结构。

这里的 u 是 main 里传入的"既有多父又有多子"的那一层。c[u]+a[u]-1 是第 u 层最后一个节点对应的全局编号（= 前 u-1 层合计 + 第 u 层个数 - 1，对应第 u 层最后一个位置的 k 序号），触发时把方案 B 那个节点改挂到上一层的最后一个父节点编号。

最终依次输出方案 A（ans）和方案 B（res）的父节点序列
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e5+5;

int c[N], ans[N], idx = 1, res[N], k = 1, a[N], n = 1;
void solve(int u) {
    c[1] = 1; ans[idx] = 0; res[k] = 0;
    for (int i = 2; i <= n; ++i) c[i] = c[i-1] + a[i-1];
    for (int i = 2; i <= n; ++i)
        for (int j = 1; j <= a[i]; ++j) {
            ans[++idx] = c[i-1];
            res[++k] = c[i-1];
            if (k == c[u] + a[u] - 1)
                res[k] = c[u-1] + a[u-1] - 1;
        }
}

int main() {
    fast;
    cin >> n; n++;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        if (a[i] >= 2 && a[i-1] >= 2) {
            cout << "ambiguous\n"; solve(i);
            for (int j = 1; j <= idx; ++j) cout << ans[j] << ' ';
            cout << '\n';
            for (int j = 1; j <= k; ++j) cout << res[j] << ' ';
            cout << '\n';
            return 0;
        }
    }
    cout << "perfect\n";
    return 0;
}