//
// Created by Psy.C on 2026/2/3.
//
/**
s：读取的操作符
s1：读取的答案（Y/N）
a, b, c, d, e：预定义的字符串常量
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define inf 2000000005
using namespace std;



int main() {
    fast;
    int n; cin >> n;//约束数量
    string s, s1, a, b, c, d, e;
    a = ">=", b = ">", c = "<=", d = "<", e = "Y";
    ll x, l = -inf, r = inf;
    for (int i = 1; i <= n; ++i) {
        cin >> s >> x >> s1;
        if (s == a) {
            if (s1 == e) l = max(l, x);//更新左边界，要求值 ≥ x
            else r = min(r, x - 1);//更新右边界，要求值 ≤ x-1
        }
        if (s == b) {
            if (s1 == e) l = max(l, x + 1);//≥ x+1
            else r = min(r, x);//≤ x
        }
        if (s == c) {
            if (s1 == e) r = min(r, x);//≤ x
            else l = max(l, x + 1);// ≥ x+1
        }
        if (s == d) {
            if (s1 == e) r = min(r, x - 1);//≤ x-1
            else l = max(l, x);//≥ x
        }
    }
    if (l > r) cout << "Impossible\n";
    else {
        if ((l+r)%2==0) cout << (l+r)/2 << '\n';//输出中间值
        else cout << (l+r+1)/2 << '\n';//输出中间值（向上取整）
    }
    return 0;
}