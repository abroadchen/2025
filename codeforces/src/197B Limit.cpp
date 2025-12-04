//
// Created by Psy.C on 2025/12/3.
//

#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 110
using namespace std;

int n, m, a[N], b[N];

int main() {
    fast;
    while (cin >> n >> m) {
        n++, m++;//数组索引从0开始，而多项式次数从最高次项开始存储
        for (int i = 0; i < n; i++) cin >> a[i];//读取第一个多项式的n个系数
        for (int i = 0; i < m; i++) cin >> b[i];
        if (n == m) {
            if (b[0] < 0) { b[0] = -b[0]; a[0] = -a[0]; }//如果分母多项式的最高次项系数为负，将分子分母都变为正数
            int x = __gcd(a[0], b[0]);//计算分子分母最高次项系数的最大公约数
            if (x < 0) x = -x;//确保最大公约数为正数
            cout << a[0] / x << '/' << b[0] / x << '\n';
        } else if (n > m) {//第一个多项式的次数大于第二个多项式
            if (a[0] > 0 && b[0] > 0 || a[0] < 0 && b[0] < 0)//最高次项系数同号
                cout << "Infinity\n";
            else cout << "-Infinity\n";
        } else  cout << "0/1\n";
    }
    return 0;
}