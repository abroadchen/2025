//
// Created by Psy.C on 2026/3/25.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e6+5;
int n, a[N];//值为1的元素的索引
int main() {
    fast;
    cin >> n;
    int j = 0;//数组a中当前元素的个数
    for (int i = 0, x; i < n; ++i) {
        cin >> x;//当前元素
        if (x == 1) a[++j] += i;//将索引i加入到a[j+1]并增加j
    }
    ll ans = 1;
    if (j == 0) cout << "0\n";
    else {
        for (int i = 1; i < j; ++i)
            ans = ans * (a[i+1] - a[i]);//相邻1之间索引差的乘积
        cout << ans << '\n';
    }
    return 0;
}