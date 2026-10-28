//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
node：存"数值 num"和"原位置下标 d"。
cmp：按数值降序排序。
a[N]：存后排位置。
ans：最大的 k 个值之和
读入 n 个数，同时记住每个数的原始位置下标 i。
按数值降序排序
取前 k 个（数值最大）位置的原始下标存进 a[1..k]。
求和 ans += 这 k 个最大值。
这 k 个位置就是"段代表"
把选出的 k 个位置按原下标升序排列，保证切分是连续顺序
第一行输出 ans = 前 k 个最大值之和。
段长度计算：按升序位置切分
第 1 段：a[1]（从位置 1 到 a[1]，长度为 a[1] - 0 。）
第 2 段：a[2] - a[1]
…
前 k-1 段分别打印 a[i] - a[i-1]
最后一段：从 a[k-1]+1 到 n，长度为 n - a[k-1]
注意循环是 rep(i,k-1)（i 从 1 到 k-1），打印 a[i]-a[i-1]。这里 a[0] 未初始化（默认 0），因为 a 是全局数组，正好为 0，所以第一段长度 = a[1]-0 = a[1]，语义正确。

每段长度加起来 = a[1] + (a[2]-a[1]) + … + (n-a[k-1]) = n。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 2e3+1;

struct node { int num, d; } s[N];
bool cmp(node a, node b) { return a.num > b.num; }

int n, k, a[N], ans;
int main() {
    fast;
    cin >> n >> k;
    rep(i,n) { cin >> s[i].num; s[i].d = i; }
    sort(s+1, s+1+n, cmp);
    rep(i,k) a[i] = s[i].d, ans += s[i].num;
    sort(a+1, a+1+k);
    cout << ans << '\n';
    rep(i,k-1) cout << a[i]-a[i-1] << ' ';
    cout << n-a[k-1];
    return 0;
}