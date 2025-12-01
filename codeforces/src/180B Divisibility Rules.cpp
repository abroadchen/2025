//
// Created by Psy.C on 2025/12/1.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int b, d;
int gcd(const int x, const int y) { return y == 0 ? x : gcd(y, x % y); }

int main() {
    fast;
    cin >> b >> d;
    int k = 0;//处理次数
    for (; gcd(b, d) > 1; ++k) d /= gcd(b, d);//移除d中与b公因子的部分
    if (d == 1) cout << "2-type\n" << k;//d的所有因子都能被b的幂次整除
    else if (k == 0 && b % d == 1) cout << "3-type";//没有进行预处理(k = 0)且b ≡ 1 (mod d)
    else if (k == 0 && b % d == d - 1) cout << "11-type";//b ≡ -1 (mod d)
    else if ((b * b - 1)/(b % 2 + 1) % d == 0) cout << "6-type";
    else cout << "7-type";
    return 0;
}