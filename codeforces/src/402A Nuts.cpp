//
// Created by Psy.C on 2026/1/31.
//
//k-1 < k < k+1
///k-1 是一个"刚刚好"的门槛
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int k, a, b, v;//k（阈值）、a（目标值）、b（初始值）、v（单位价值）
bool ok(int x) {
    int t = b, sum = 0, i;
    for (i = 0; i < x; ++i) {
        //是否有足够的资源 消耗k-1的资源，获得k*v的价值
        if (t >= k - 1) { t -= k - 1; sum += k * v; }
        else break;
    }
    //完成了x次完整操作，检查总价值是否达到目标a
    if (i == x) return sum >= a;
    //更新剩余需要的操作次数 用剩余资源t+1进行一次操作
    x -= i; sum += (t + 1) * v;
    if (--x == 0) return sum > a;//只剩下一次操作，检查是否超过a
    return sum + x*v >= a;//剩余x次操作每次都产生v的价值
}


int main() {
    fast;
    cin >> k >> a >> b >> v;
    int l = 0, r = 1500;
    while (r - l > 1) {
        if (const int mid = (l + r) >> 1; ok(mid)) r = mid;//mid可行，缩小右边界
        else l = mid;
    }
    cout << r << '\n';
    return 0;
}