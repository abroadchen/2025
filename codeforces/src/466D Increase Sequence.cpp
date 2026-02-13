//
// Created by Psy.C on 2026/2/13.
//
/**
n：数组长度
h：最大高度
a[N]：调整后的高度数组
b[N]：差分数组

时间复杂度：O(n)
空间复杂度：O(n)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 2002
#define mod 1000000007
using namespace std;

int n, h, a[N], b[N];
void out() {
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        a[i] = h - x;//将原始高度相对于最大高度h进行了翻转
    }
    a[0] = 0; a[n+1] = 0;//边界条件
    for (int i = 1; i <= n + 1; ++i) {
        b[i] = a[i] - a[i-1];//只允许变化为-1, 0, 1（相邻位置高度差不超过1）
        if (b[i] > 1 || b[i] < -1) {//高度变化不合法
            cout << "0\n";
            return;
        }
    }
    ll ans = 1;
    for (int i = 1; i <= n + 1; ++i) {
        if (b[i] == 1) continue;//斜率为1的边不需要额外计算
        //0到a[i]的高度范围内任意放置
        if (b[i] == 0) ans *= a[i] + 1;//水平边，有 a[i] + 1 种放置方式
        //受前一位置限制
        else ans *= a[i-1];//下降边，有 a[i-1] 种放置方式
        ans %= mod;
    }
    cout << ans << "\n";
}

int main() {
    fast;
    cin >> n >> h; out();
    return 0;
}