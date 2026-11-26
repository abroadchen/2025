//
// Created by Psy.C on 2026/11/26.
//

/**
真正学会的起点..
n：交互服务器本次返回的车/组数。
a[1..n]：服务器返回的每组组成的字符串（如 "24" 表示第 2、4 位被叫到且聚成一组）。
rd()：封装一次"输出指令后的回读"，读入分组 n 与每个组
 快慢指针（龟=2，兔=4）‍：兔每轮走 2 步（连续两轮"next"，第一轮带 2 一起、第二轮 4 单独），龟走 1 步（2 只在偶数步前进）。当 2 与 4 同组（"24"）即二者在环上相遇
 让 0–9 全部位置一起前进，一轮读一次。
当 n == 1（所有位置最终归到同一个集合）时，说明已经到了"终点 / 环尾"，输出 "done" 结束
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n;
string a[11];
void rd() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
}

int main() {
    fast;
    while (1) {
        cout << "next 2 4" << endl;
        rd();
        cout << "next 4" << endl;
        rd();
        if (n == 2 && a[1] == "24" || a[2] == "24") break;
    }
    while (1) {
        cout << "next 0 1 2 3 4 5 6 7 8 9" << endl;
        rd();
        if (n == 1) { cout << "done" << endl; break; }
    }
    return 0;
}