//
// Created by Psy.C on 2026/2/19.
//
/**
n: 输入的原始数字，每次减去三角形数后会更新
m: 当前的三角形数（1, 3, 6, 10, ...）
i: 三角形数的序号（第几个三角形数）
cnt: 计数器，记录成功减去的三角形数个数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int n, m = 1, i = 1;
int main() {
    fast;
    cin >> n;
    int cnt = 0;
    while (m <= n) {
        m = (i*i + i) / 2;//第i个三角形数: 1+2+...+i = i*(i+1)/2
        if (m > n) break;//当前三角形数大于剩余数
        n = n - m;
        cnt++;
        i++;//移动到下一个三角形数
    }
    cout << cnt << '\n';
    return 0;
}
