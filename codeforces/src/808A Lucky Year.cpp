//
// Created by Psy.C on 2026/9/20.
//
/**
n 到"下一位整百/整千…进位数"的距离，即 10^(l-1) * (最高位+1) - n，也就是进到下一个整"位"时的进位间距
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int get(int& x) {
    int sum = 0;
    if (x == 0) return 1;//特判 0：1 位数
    while (x >= 10) {
        x /= 10;//不断去掉最低位
        sum++;//记录去掉了几位
    }
    return sum+1;//去掉的位数 + 1 = 原 x 的总位数
}
int ksm(int y) {
    int x = 1;
    while (--y) x *= 10;//乘 y-1 次 10
    return x;
}


int main() {
    fast;
    int n; cin >> n;
    int x = n, l = get(x);
    cout << (x+1)*ksm(l)-n;
    return 0;
}