//
// Created by Psy.C on 2026/5/26.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int s, x1, x2, t1, t2, p, d;
int main() {
    fast;
    cin >> s >> x1 >> x2 >> t1 >> t2 >> p >> d;
    int t = (x2-x1)*t2;//步行所用的时间
    if (t < 0) t = -t;
    int tim = 0, cur = p, f = 0;
    while (true) {
        if (cur == s || cur == 0) d = -d;//车到了两端换向
        if (cur == x1) f = 1;//只有经过起点才能让人上车
        if (cur == x2 && f == 1) break;//经过终点人下车
        cur += d;//向当前方向走
        tim += t1;//加上车这一秒的用时
    }
    cout << (t < tim ? t : tim) << '\n';//取时间最短的输出
    return 0;
}