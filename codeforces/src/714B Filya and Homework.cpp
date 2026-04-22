//
// Created by Psy.C on 2026/4/21.
//
/**
b[5];     // 去重后的数组，最多存储3个不同的数值
k = 1;   // 记录去重后不同数值的个数，初始值为1（因为至少有一个元素）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+7;
int n;
ll a[N], b[5], k = 1;
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a, a + n); b[0] = a[0];//将排序后的第一个元素放入b数组
    for (int i = 1; i < n; ++i) {
        if (a[i] != a[i-1]) b[k++] = a[i];//当前元素与前一个不同，加入b数组并增加计数
        if (k > 3) {
            cout << "NO\n";
            return 0;
        }
    }
    if (k == 2 || k == 1) cout << "YES\n";
    else if (k == 3) {
        if (b[1]*2 == b[0] + b[2]) cout << "YES\n";//是否构成等差数列（b[1]是中间项）
        else cout << "NO\n";
    } else cout << "NO\n";
    return 0;
}