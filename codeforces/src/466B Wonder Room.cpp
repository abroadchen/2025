//
// Created by Psy.C on 2026/2/13.
//
/**
mm = n*6：目标面积
x, y：最优解的宽高
ans：最优面积
m = sqrt(mm) + 1：搜索范围的上界

mm/i：mm除以i的商
(mm%i!=0)：如果mm不能被i整除，结果为1；否则为0
这实际上是在计算向上取整：⌈mm/i⌉
逻辑：
枚举宽度i从a到sqrt(mm)
计算高度yy = ⌈mm/i⌉（确保i*yy >= mm）
检查高度是否满足yy >= b
更新最优解
枚举高度i从b到sqrt(mm)
计算宽度xx = ⌈mm/i⌉
检查宽度是否满足xx >= a
更新最优解

检查原矩形是否满足要求
否则在[a, √(n*6)]范围内搜索最优宽度
在[b, √(n*6)]范围内搜索最优高度
由于面积函数的对称性，只需搜索到√mm即可
时间复杂度约为O(√n)，效率较高

 */
#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, a, b;

int main() {
    fast;
    cin >> n >> a >> b;
    if (n*6 <= a*b) cout << a*b << '\n' << a << ' ' << b << '\n';
    else {
        const ll mm = n*6;
        ll x = a, y = b, ans = 0;
        const ll m = 1ll * sqrt(mm) + 1;
        for (ll i = a; i <= m; ++i) {
            if (const ll yy = mm/i + (mm%i!=0); yy*i >= mm && yy >= b) {
                if (!ans) ans = i*yy, x = i, y = yy;
                else if (yy*i < ans) ans = yy*i, x = i, y = yy;
            }
        }
        for (ll i = b; i <= m; ++i) {
            if (const ll xx = mm/i + (mm%i!=0); xx*i >= mm && xx >= a) {
                if (!ans) ans = i*xx, y = i, x = xx;
                else if (xx*i < ans) ans = xx*i, y = i, x = xx;
            }
        }
        cout << ans << '\n' << x << ' ' << y << '\n';
    }
    return 0;
}