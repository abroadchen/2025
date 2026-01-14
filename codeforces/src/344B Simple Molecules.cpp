//
// Created by Psy.C on 2026/1/13.
//
///O(1)，纯数学计算
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int a, b, c; cin >> a >> b >> c;
    if ((a+b-c)%2==0 && (a+c-b)%2==0 && (b+c-a)%2==0) {//检查计算结果是否为整数
        if (const int x = (a+b-c)>>1, y = (b+c-a)>>1, z = (a+c-b)>>1;
            (x==0&&y==0)||(x==0&&z==0)||(y==0&&z==0)||x<0||y<0||z<0) {//是否有两条边为0 是否有负边长
            cout << "Impossible\n";
        } else cout << x << ' ' << y << ' ' << z << '\n';
    } else cout << "Impossible\n";
    return 0;
}