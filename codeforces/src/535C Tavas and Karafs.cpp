//
// Created by Psy.C on 2026/3/4.
//
/**
ok(r): 验证从位置l到位置r的总和是否满足条件
使用等差数列求和公式：(首项 + 末项) * 项数 / 2
如果总和大于 m*t（最大容量），返回false

如果第l项的值大于t（起始值就超时），输出-1
否则：
设置二分查找范围：L=1, R=(t-a)/b+1
二分查找满足条件的最大位置
如果ok(mid)为真，说明mid位置可行，向右搜索
否则向左搜索
输出找到的最大可行位置

时间复杂度为O(n log(max_pos))，空间复杂度为O(1)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int a, b;///等差数列的首项和公差
ll get(const int i) {//等差数列第i项的值
    return 1ll*a + 1ll*(i-1)*b;
}
int l, m, t;///起始位置、人数、时间
bool ok(const int r) {
    if ((get(l) + get(r))*(r-l+1)/2 > 1ll*m*t)
        return false;
    return true;
}

int n;
int main() {
    fast;
    cin >> a >> b >> n;
    while (n--) {
        cin >> l >> t >> m;
        if (get(l) > t) cout << "-1\n";
        else {
            int L = 1, R = (t - a) / b + 1, mid = (L+R)>>1;
            while (L <= R) {
                if (ok(mid)) L = mid + 1;
                else R = mid - 1;
                mid = (L+R)>>1;
            }
            cout << mid << '\n';
        }
    }
    return 0;
}