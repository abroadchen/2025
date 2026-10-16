//
// Created by Psy.C on 2026/10/15.
//
/**
输入给出的是每个节点 i 的父亲 a（节点 2..n，每个输入一个父节点编号）。所以这是"给定一棵以 1 为根的树的父亲数组"的标准读入方式。
d[i] = d[a] + 1：因为父节点深度已知，子节点深度 = 父深 + 1。节点 1 是根，d[1] 默认 0（全局变量默认 0），所以根的深度是 0。
sum[d[i]]++：把深度为 d[i] 的节点数累加到 sum[深度]。即 sum[k] = 深度为 k 的节点个数（第 k 层的节点数）。
这样一次遍历就得到了每一层的节点数，没有建邻接表，因为深度可以由父深度直接递推
对每个深度 i（从 1 到 n），如果 sum[i] 是奇数（&1 即 mod 2 = 1），就 ans++。
注意 i 从 1 开始：深度 0 只有根一层（sum[0] 没被统计，因为它只有根节点 1，不会在循环里被累加——实际上根深度 0 的节点数从来没进过 sum，sum[0] 恒为 0）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e5+1;

ll n, a, d[N], sum[N], ans(1);
int main() {
    fast;
    cin >> n;
    for (int i = 2; i <= n; ++i) {
        cin >> a; d[i] = d[a] + 1;
        sum[d[i]]++;
    }
    for (int i = 1; i <= n; ++i) ans += sum[i]&1;
    cout << ans << '\n';
    return 0;
}