//
// Created by Psy.C on 2026/4/11.
//
/**
读取元素数量n和第一个数字
如果只有一个元素，输出0（不需要插入）和数字本身

初始化需要插入的计数器
对于每个后续元素，读取数字
检查当前数字和前一个数字的GCD是否不等于1
如果它们不是互质的（GCD ≠ 1），则增加计数器
输出所需的插入总数
输出第一个数字
对于每个后续数字：
如果当前数字和前一个数字不是互质的，在数字前插入" 1 "（使它们互质）
否则只用空格输出数字
以换行符结束

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int gcd(int a, int b) {
    if (a % b == 0) return b;
    return gcd(b, a % b);
}

constexpr int N = 1005;
int n, num[N];
int main() {
    fast;
    cin >> n >> num[1];
    if (n == 1) {
        cout << "0\n" << num[1] << '\n';
        return 0;
    }
    int cnt = 0;
    for (int i = 2; i <= n; ++i) {
        cin >> num[i];
        if (gcd(num[i], num[i-1]) != 1)
            cnt++;
    }
    cout << cnt << '\n' << num[1];
    for (int i = 2; i <= n; ++i) {
        if (gcd(num[i], num[i-1]) != 1)
            cout << " 1 " << num[i];
        else
            cout << ' ' << num[i];
    }
    cout << '\n';
    return 0;
}