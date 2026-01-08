//
// Created by Psy.C on 2026/1/8.
//

#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n;
ll get(ll a, ll b, const ll s) {//寻找方程x² - 2n + sx = 0的奇数解
    while (a < b) {
        const ll mid = (a + b) >> 1, t = mid * mid - 2 * n + s * mid;
        if (t == 0) {
            if (mid % 2 == 0) return -1;
            return mid;
        }
        if (t > 0) b = mid; else a = mid + 1;
    }
    if (a * a - 2 * n + s * a == 0 && (a&1)) return a;
    return -1;
}

int main() {
    fast;
    cin >> n;
    ll cur = 2, lst = 0; int flag = 0;//标记是否找到解
    while (true) {
        if (cur - 3 < n * 2) {//条件满足
            ll t = static_cast<ll>(sqrt(static_cast<double>(2 * n) + 0.5));//√(2n+0.5)
            ll p = n * 2 / (cur - 3);
            if (p > 0 && p < t) t = p;//p更小，更新t
            p = get(0, t + 3, cur - 3);
            if (p > 0 && lst != cur / 2 * p) {//找到解且不是重复的
                cout << cur / 2 * p << '\n';
                flag = 1;
                lst = cur / 2 * p;//更新lst防止重复输出
            }
        } else break;
        cur *= 2;//进入下次迭代
    }
    if (!flag) cout << "-1\n";
    return 0;
}