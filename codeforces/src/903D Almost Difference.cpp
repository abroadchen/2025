//
// Created by Psy.C on 2026/10/11.
//
/**\
① (i-1)*t - sum —— 与前面所有元素的绝对差之和

(i-1)*t = 当前值 t 乘以已有的元素个数。
-sum = 减去前面所有元素的值之和。
合起来 Σ_{前面每个x} (t - x)，即当前元素与前面每个元素的带符号差之和。
注意这是"前减后"还是"后减前"取决于排序，这里直接算 t - x 的累加。
② - num[t-1]

因为当前面某个元素 x = t-1 时，(t - x) = 1，而如果题目要求的是绝对值差 |t-x|，那么对 x = t-1 这一项，带符号差是 +1，但绝对值差应为 1——这里减去 num[t-1] 相当于对差值为 1 的情形做某种修正。
③ + num[t+1]

当前面某个元素 x = t+1 时，带符号差 (t - x) = -1，而绝对值应为 1，所以加上 num[t+1] 来修正（把 -1 补成 +1）。
 */
#include <bits/stdc++.h>
#define rep(i,j,k) for(int i=j; i<=k; ++i)
#define ld long double
#define ll long long
using namespace std;

int main() {
    int n;
    while(cin >> n) {
        ld sum = 0, ans = 0;
        unordered_map<ll, ll> num;
        rep(i,1,n) {
            ll t; cin >> t;
            ans += (i-1)*t - sum - num[t-1] + num[t+1];
            num[t]++;
            sum += t;
        }
        printf("%.0Lf", ans);
    }
    return 0;
}