//
// Created by Psy.C on 2026/9/20.
//
/**
b[i] 记录：val（当前分配值）、pos（原数组下标）、cm（排序关键字，这里存的是 a[i] 原值）。
cmp 按 cm（即 a[i]）‍从大到小排序。这意味着优先处理最大的数字

若通过贪心能让总 sum 恰好等于 m，则按原下标顺序输出每个分配值 ans[i]。
否则输出 -1（无解）。
ans[i] 在上一轮按 pos（原下标）写回，保证输出顺序恢复成输入顺序
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 15e5;
struct node { ll val, pos, cm; } b[N];
int cmp(node a, node b) { return a.cm > b.cm; }

ll n, m, a[N], ans[N];
int main() {
    fast;
    while (cin >> n >> m) {
        ll sum = 0;
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < n; ++i) {
            //下限 = a/2（下取整）
            b[i].val = a[i]/2; b[i].cm = a[i];
            if (a[i]%2 == 1) b[i].val++;//奇数则 +1，变成上取整 (a+1)/2
            b[i].pos = i;
            sum += b[i].val;//累加所有下限
        }
        sort(b, b + n, cmp);
        for (int i = 0; i < n; ++i) {
            while (sum < m && b[i].val < a[b[i].pos]) {//还有余量且当前 val 还能加
                sum++;
                b[i].val++;
            }
            ans[b[i].pos] = b[i].val;
        }
        if (sum == m) {
            for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
            cout << '\n';
        } else cout << "-1\n";
    }
    return 0;
}