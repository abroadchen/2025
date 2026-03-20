//
// Created by Psy.C on 2026/3/20.
//
/**
n：第一个数组的长度
m：第二个数组的长度
cnt[N]：统计第一个数组中每个值出现的次数
a[N]：记录第一个数组中每个值第一次出现的位置 覆盖，实际上记录最后一次出现的位置
b[N]：第二个数组
检查第二个数组中的每个元素是否在第一个数组中存在
如果某个元素在第一个数组中出现多次
输出第二个数组中每个元素在第一个数组中的位置
时间复杂度：O(n + m) 空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
int n, m, cnt[N], a[N], b[N];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x; cnt[x]++; a[x] = i;
    }
    for (int i = 1; i <= m; ++i) {
        cin >> b[i];
        if (cnt[b[i]] == 0) {
            cout << "Impossible";
            return 0;
        }
    }
    for (int i = 1; i <= m; ++i) {
        if (cnt[b[i]] > 1) {
            cout << "Ambiguity";
            return 0;
        }
    }
    cout << "Possible\n";
    for (int i = 1; i <= m; ++i) cout << a[b[i]] << ' ';
    return 0;
}