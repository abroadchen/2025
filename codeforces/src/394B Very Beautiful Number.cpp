//
// Created by Psy.C on 2026/1/30.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000010
using namespace std;


int main() {
    fast;
    int p, x; cin >> p >> x;// p（位数）和 x（倍数
    int ok = 0, a[N];//是否找到解 存储数字的数组
    for (int i = 1, c; i < 10; ++i) {
        c = 0;//进位变量
        a[p-1] = i;//设置最后一位数字
        for (int j = p - 2; j >= 0; --j) {
            a[j] = (a[j+1] * x + c) % 10;//当前位的数字
            c = (a[j+1] * x + c) / 10;
        }
        //第一位数字乘以 x 加上进位是否等于最后一位 第一位不为 0
        if (a[0] * x + c == a[p-1] && a[0] != 0) {
            ok = 1; break;
        }
    }
    if (ok) {
        for (int i = 0; i < p; ++i) cout << a[i];//输出整个数字
        cout << '\n';
    } else cout << "Impossible\n";
    return 0;
}