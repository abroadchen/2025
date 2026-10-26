//
// Created by Psy.C on 2026/10/26.
//

/**
真正学会的起点..
若剩余 sum >= k，A 取走 k：sum -= k; a += k。
否则（剩余不足 k），A 取走全部剩余：a += sum; sum = 0
若此时剩余 sum >= 10，B 取走 sum/10（向下取整）：t = sum/10; b += t; sum -= t。
若剩余 < 10，B 取不了（不取，留到下一轮）
若 A 取到的量 ≥ B 取到的量，返回 true
读入总金额 sum。
进行二分：l=1, r=sum。
mid = (l+r)>>1：中点。
若 check(mid, sum) 为真（A 在 k=mid 下能赢），说明当前 k 可行，尝试更小 → r = mid（向左收缩）。
否则 l = mid+1（向右收缩）。
最终输出 l = 最小的可行 k（A 恰好能 ≥ B 的最小每次取走量）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

bool check(ll k, ll sum) {
    ll a = 0, b = 0, t;
    while (sum) {
        if (sum >= k) { sum -= k; a += k; }
        else { a += sum; sum = 0; }
        if (sum >= 10) { t = sum/10; b += t; sum -= t; }
    }
    return a >= b;
}
template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}


int main() {
    fast;
    ll sum; read(sum);
    ll l = 1, r = sum;
    while (l < r) {
        ll mid = (l+r)>>1;
        if (check(mid, sum)) r = mid;
        else l = mid+1;
    }
    cout << l << '\n';
    return 0;
}