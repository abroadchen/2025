//
// Created by Psy.C on 2026/1/12.
//
/**
* r：球体直径
h：圆柱体高度
rr：球体半径（r/2）
x：rr + h，用于计算垂直方向的层数
 *ans：垂直方向能放置的球层数（向下取整）
*sqrt(3)/2 * r：这是球体六边形紧密堆积时的垂直间距
 *
*d = rr * rr + (yy - rr) * (yy - rr)：计算某点到球心的距离平方
4*rr*rr：是两个球直径距离的平方（即 (2*rr)^2）
如果 d > 4*rr*rr，说明还有一个额外的空间可以放置球体
 *
*ans*2：只能放置 ans 层，每层交错排列
ans*2+1：能多放置一层，总共 ans+1 层
 */
#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define eps 1e-9
using namespace std;


int main() {
    fast;
    ll r, h; cin >> r >> h;
    const double rr = static_cast<double>(r) * 1. / 2.,
    x = rr + static_cast<double>(h);
    const ll ans = static_cast<ll>(x) / r;
    const double y = sqrt(3) / 2. *
        static_cast<double>(r) + static_cast<double>(h) -
            static_cast<double>(ans) * static_cast<double>(r);
    double yy = sqrt(3) / 2. * static_cast<double>(r) - y;
    yy -= rr;
    if (const double d = rr * rr + (yy - rr) * (yy - rr);
        d - 4*rr*rr > eps) cout << ans*2+1 << '\n';
    else cout << ans*2 << '\n';
    return 0;
}