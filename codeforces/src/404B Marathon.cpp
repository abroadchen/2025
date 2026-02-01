//
// Created by Psy.C on 2026/2/1.
//

#include <iomanip>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    //m（正方形边长）、k（步长系数）、n（查询次数）
    double m, k; int n; cin >> m >> k >> n;
    const double len = m*4;//正方形周长
    double x = 0, y = 0;//初始化坐标
    cout << fixed << setprecision(10);
    for (int i = 1; i <= n; ++i) {
        double s = i * k;//第i步的总路程
        s = fmod(s, len);//确保在一圈内
        int p = 1;//第几条边（p从1到4）1=底边，2=右边，3=顶边，4=左边
        while (s - m > 0) { s -= m; p++; }
        if (p == 1) { x = s; y = 0; }//从(0,0)到(m,0)，坐标为(s,0)
        else if (p == 2) { x = m; y = s; }//从(m,0)到(m,m)，坐标为(m,s)
        else if (p == 3) { x = m - s; y = m; }//从(m,m)到(0,m)，坐标为(m-s,m)
        else if (p == 4) { x = 0; y = m - s; }//从(0,m)到(0,0)，坐标为(0,m-s)
        cout << x << ' ' << y << '\n';
    }
    return 0;
}