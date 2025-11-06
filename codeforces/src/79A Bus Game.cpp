//
// Created by Psy.C on 2025/11/6.
//

#include <cstdio>
#include <iostream>
using namespace std;

long int x, y;
bool w(1);

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> x >> y;
    while (x * 10 + y >= 22 && y >= 2) {//总价值至少为22 y资源至少为2
        if (w || y < 12) {//消耗2个x资源和2个y资源
            x -= 2;
            y -= 2;
        } else if (y < 22) {//消耗1个x资源和12个y资源
            x--;
            y -= 12;
        } else y -= 22;//只消耗22个y资源
        w = !w;//切换玩家回合
    }
    if (w) cout << "Hanako";
    else cout << "Ciel";
    return 0;
}