//
// Created by Psy.C on 2026/10/25.
//

/**
真正学会的起点..
node：记录 {数组编号 s, 位置 p}。
m：map<int, node>，键为"删除某元素后的剩余和"，值为"产生这个和的数组编号 + 位置"
k：数组个数。
sum：当前数组的总和。
n：当前数组的元素个数。
a[N]：存当前数组元素
对第 i 个数组：

清零 sum，读入元素数 n。
读入每个 a[j] 并累加得到 sum
遍历第 i 个数组的每个位置 j：

计算 x = sum - a[j]，即若删除 a[j]，剩余元素和。
命中判断：m.count(x) 表示之前已有某个数组也得到过相同的剩余和 x，且 m[x].s != i（是不同的数组，防止同一数组内自娱）→ 找到答案：
输出第一个找到的数组 (m[x].s, m[x].p)。
输出当前数组 (i, j)。
return 0 结束。
否则：把当前 (i, j) 记录进 m[x]（若 m[x] 已存在但 s==i，会直接覆盖，即同一数组多个位置产生同一 x 时只保留最后一次——这没问题，因为我们需要的是不同数组的配对）
遍历所有数组结束后仍无配对，输出 NO
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=n; ++i)
using namespace std;

constexpr int N = 2e5+5;

struct node { int s, p; };

int k, i, j, sum, n, a[N];
map<int,node> m;
int main() {
    fast;
    cin >> k;
    rep(i,k) {
        sum = 0; cin >> n;
        rep(j,n) { cin >> a[j]; sum += a[j]; }
        rep(j,n) {
            int x = sum - a[j];
            if (m.contains(x) && m[x].s != i) {
                cout << "YES\n";
                cout << m[x].s << ' ' << m[x].p << '\n';
                cout << i << ' ' << j << '\n';
                return 0;
            } else {
                m[x].s = i; m[x].p = j;
            }
        }
    }
    cout << "NO\n";
    return 0;
}