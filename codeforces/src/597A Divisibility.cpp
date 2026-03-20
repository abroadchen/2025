//
// Created by Psy.C on 2026/3/20.
//
/**
k：除数
a, b：区间[a,b]的左右端点
ans：结果（区间内能被k整除的数的个数）

b/k - a/k：这是计算区间[0,b]和[0,a)内能被k整除的数的差
if (a%k == 0) ans++;：如果a本身能被k整除，需要额外加1（因为a/k会排除a）
a = -a; b = -b;：将区间翻转到正半轴
由于区间[a,b]（a≤b≤0）翻转后变成[-b,-a]（0≤-b≤-a）
翻转后区间内能被k整除的数的个数不变
然后用情况1的方法计算
a < 0, b > 0：区间包含0点
-a/k：区间[a,0)内能被k整除的数的个数（通过翻转到正半轴计算）
b/k：区间(0,b]内能被k整除的数的个数
+1：加上数字0（0能被任何非零数整除）

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

int k, a, b, ans;
signed main() {
    fast;
    cin >> k >> a >> b;
    if (a >= 0) {
        ans = b/k - a/k;
        if (a%k == 0) ans++;
    } else if (b <= 0) {
        a = -a; b = -b;
        ans = a/k - b/k;
        if (b%k == 0) ans++;
    } else ans = -a/k + b/k + 1;
    cout << ans << '\n';
    return 0;
}