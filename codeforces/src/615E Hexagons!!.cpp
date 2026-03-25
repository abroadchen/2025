//
// Created by Psy.C on 2026/3/25.
//
/**
n为输入值，x,y为输出坐标
n=0时坐标为(0,0)

螺旋结构：代码在模拟一个从原点开始向外螺旋扩展的路径
层次划分：get函数找出第n个点所在"圈"的层数t
边界计算：公式3*t*(t+1)可能表示第t层的边界点数量
方向判断：根据剩余步数d和每段长度计算具体方向

3*t*(t+1)：这可能是六边形螺旋路径中第t层包含的总点数
s = d/t：确定在当前层的哪个方向段
d = d-s*t：在该方向段内的偏移量

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr ll inf = 1e9;
ll get(ll l , ll r, ll n) {//找到最大的mid
    ll ans = 0;
    while (r >= l) {
        ll mid = (l + r) >> 1;
        if (3 * (mid + 1) * mid <= n) { ans = mid; l = mid + 1; }
        else r = mid - 1;
    }
    return ans;
}

ll n, x, y;
int main() {
    fast;
    cin >> n;
    if (n == 0) x = 0, y = 0;
    else {
        ll r = inf, t = get(1, r, n), d = n - 3*t*(t+1); t++;
        if (d == 0) x = 2*(t-1), y = 0;//没有剩余
        else {
            ll s = d/t; d = d - s*t;
            if (s == 0) x = 2*t-d, y = 2*d;
            else if (s == 1) x = t-2*d, y = 2*t;
            else if (s == 2) x = -t-d, y = 2*t-2*d;
            else if (s == 3) x = -2*t+d, y = -2*d;
            else if (s == 4) x = -t+2*d, y = -2*t;
            else if (s == 5) x = t+d, y = -2*t+2*d;
            else x = 2*t, y = 0;
        }
    }
    cout << x << ' ' << y << '\n';
    return 0;
}