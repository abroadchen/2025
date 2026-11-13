//
// Created by Psy.C on 2026/11/13.
//

/**
真正学会的起点..
对每个正根 i，验证它是否满足积的条件：i × (d - i) = d。
若满足，输出 Y x y（其中 y = d - x）；否则输出 N
当 d ≠ 0 时，调用 solve(1,-d,d) 解方程 t² - d·t + d = 0，拿到正根集合，再传入第二个 solve 验证输出。
当 d = 0 时特判：x = 0, y = 0 满足 0+0=0 且 0×0=0，直接输出 Y 0 0
*/
#include <bits/stdc++.h>
#define db double
#define vd vector<db>
#define eps 1e-9
using namespace std;

vd solve(db a, db b, db c) {
    vd ret;
    db delta = b*b - a*c*4;//判别式 Δ = b² - 4ac（此处a=1, b=-d, c=d）
    if (delta < 0) return ret;//无实根，返回空向量
    delta = sqrt(delta);//Δ 开方
    db x[2] = {(-b-delta)/2/a, (-b+delta)/2/a};//求根公式
    for (db i : x) if (i > 0) ret.push_back(i);//只保留正根
    return ret;
}
int solve(vd ans, int d) {
    for (auto i : ans)
        if (fabs((d-i)*i-d) < eps)
            return printf("Y %.9lf %.9lf\n", i, d - i);
    return 0*puts("N");
}

int t, d;
int main() {
    for (cin >> t; t; t--) {
        cin >> d;
        if (d != 0) solve(solve(1,-d,d),d);
        else puts("Y 0.000000000 0.000000000");
    }
    return 0;
}