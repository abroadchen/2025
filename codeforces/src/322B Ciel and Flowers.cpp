//
// Created by Psy.C on 2026/1/8.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    unsigned r, g, b; cin >> r >> g >> b;
    const unsigned R = r % 3, G = g % 3, B = b % 3;//不能被3整除的剩余数量
    unsigned cnt = r / 3 + g / 3 + b / 3 + min(R, min(G, B));
    if (R == 2 && G == 2 && B == 0 && b != 0 ||//红色余2，绿色余2，蓝色余0且蓝色总数不为0
        G == 2 && B == 2 && R == 0 && r != 0 ||
        B == 2 && R == 2 && G == 0 && g != 0) cnt += 1;//可以额外形成1个组合
    cout << cnt << '\n';
    return 0;
}