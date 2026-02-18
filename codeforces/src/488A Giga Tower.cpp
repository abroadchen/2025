//
// Created by Psy.C on 2026/2/18.
//
/**
最坏情况：O(∞)（理论上可能无限循环）
实际情况：平均O(log x)（因为每10个数中大约有1个包含8）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

bool check(int n) {//数字n是否包含数字8
    n = abs(n);
    while (n) {
        if (n%10 == 8) return true;//个位数是否为8
        n /= 10;//去掉个位数
    }
    return false;
}

int x;
int main() {
    fast;
    cin >> x;
    for (int i = 1; i; ++i) {//i永远不会为0
        if (check(x + i)) {
            cout << i << '\n';
            break;
        }
    }
    return 0;
}