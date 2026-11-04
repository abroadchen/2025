//
// Created by Psy.C on 2026/11/4.
//

/**
真正学会的起点..
读入 a[i] 后立即累加前缀和：a[i] += a[i-1]，所以读完后 a[i] 表示前 i 个元素的和（a[1]=第一个数, a[2]=前两个数之和...）。b 同理
a[n] 是数组 a 的总和，b[m] 是数组 b 的总和。若两数组总和不同，则无法拼合成相等，直接输出 -1 结束
这里用了一个双指针的思想：

外层指针 i 遍历 a 的前缀和；
内层指针 p 遍历 b 的前缀和；
当 b[p] < a[i] 时不断 p++，直到 b[p] 不再小于 a[i]（即追平或超过）；
若此时恰好 b[p] == a[i]，说明两个数组在第 i 个位置的前缀和相同，这是一个可行的"合并分界点"，ans++。
因为两数组总和相等（上一步已保证），所以 b 的前缀和总能追上 a 的前缀和。数一数有多少个双方前缀和相等的公共点，就得到了能完整切分成的段数

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 3e5+5;

int n, m, ans;
ll a[N], b[N];
int main() {
    fast;
    cin >> n;
    rep(i,n) { cin >> a[i]; a[i] += a[i-1]; }
    cin >> m;
    rep(i,m) { cin >> b[i]; b[i] += b[i-1]; }
    if (a[n] != b[m]) { cout << -1; return 0; }
    int p = 0;
    rep(i,n) {
        while (p < m && b[p] < a[i]) p++;
        if (b[p] == a[i]) ans++;
    }
    cout << ans;
    return 0;
}