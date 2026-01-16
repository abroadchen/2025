//
// Created by Psy.C on 2026/1/15.
//
/**
 *n（输入数的对数）和num（计数器，初始化为0）
 *a，用于存储输入数据
 *sum: 存储所有小数部分的和
 *
*n - i: 实际选择的数量
计算|sum - (n - i)|的最小值，即小数部分和与整数部分差值的最小绝对值
 */
#include <iomanip>
#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 5007
#define eps 1e-6
#define inf 1e11
using namespace std;

//小数部分是否为0
bool ok(const double x) {//x是否接近于0
    if (fabs(x) < eps) return true;
    return false;
}


int main() {
    fast;
    int n, num = 0; cin >> n;
    double a[N], sum = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[(i<<1)-1];//奇数索引
        cin >> a[i<<1];
    }
    for (int i = 1; i <= n<<1; ++i) {
        a[i] -= floor(a[i]);//提取小数部分（减去整数部分）
        if (ok(a[i])) num++;//小数部分接近0，增加计数器num
        sum += a[i];//累加所有小数部分
    }
    double ans = inf;
    for (int i = max(0, num - n); i <= min(num, n); ++i)
        ans = min(ans, fabs(sum - (n - i)));//尽可能接近整数
    cout << fixed << setprecision(3) << ans << '\n';
    return 0;
}