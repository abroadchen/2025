//
// Created by Psy.C on 2025/11/16.
//
/*
 *
*当p[k]为假（0）时继续循环
++k：将k递增1
-= k > n ? n : 0：如果k超过n，则减去n（实现循环效果）
这形成了一个循环搜索：从位置k开始，找到第一个p[k]为真的位置
 *
 */
#include <iostream>
using namespace std;

const int N = 1005;
int n, k, i, p[N];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin.tie(nullptr)->sync_with_stdio(false);
    for (cin >> n >> k; i++ < n;) cin >> p[i];
    for (; !p[k];) ++k -= k > n ? n : 0;
    cout << k;
    return 0;
}