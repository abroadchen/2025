//
// Created by Psy.C on 2026/9/27.
//
/**
2^n 表示 n 个位置中任意选择若干位置（子集）的总数；
减 n 去掉只选 1 个位置的方案；
再减 1 去掉"一个都不选"的方案。
结果是 2^n - n - 1，即从 n 个元素中任选至少 2 个元素的方案数。
循环读入每组数据的行列数和矩阵。
ans 从 n*m 开始，因为每个单独的格子（1×1）本身就是"全同色"合法子段，先全部计入。
遍历每一行，统计该行中数字 1 的个数 n1、数字 0 的个数 n2。
用 get(n1)+get(n2) 把该行中由"连续同色元素"构成的长度 ≥ 2 的子段数量累加入答案（分别对应全 1 段和全 0 段的组合计数
对每一列做同样处理：统计列中 1 的个数 n1、0 的个数 n2，再把 get(n1)+get(n2) 累加入答案。
输出该组数据的答案，继续处理下一组
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll get(int n) { return (1ll<<n) - n - 1; }

int n, m, a[55][55];
int main() {
    fast;
    while (cin >> n >> m) {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) cin >> a[i][j];
        ll ans = n*m;
        for (int i = 1; i <= n; ++i) {
            int n1 = 0, n2 = 0;
            for (int j = 1; j <= m; ++j) {
                if (a[i][j]) n1++;
                else n2++;
            }
            ans += get(n1) + get(n2);
        }
        for (int j = 1; j <= m; ++j) {
            int n1 = 0, n2 = 0;
            for (int i = 1; i <= n; ++i) {
                if (a[i][j]) n1++;
                else n2++;
            }
            ans += get(n1) + get(n2);
        }
        cout << ans << '\n';
    }
    return 0;
}