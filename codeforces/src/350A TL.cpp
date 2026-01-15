//
// Created by Psy.C on 2026/1/14.
//
/**
 * n表示第一组数据个数，m表示第二组数据个数
*ax = 100: 第一组数据的最小值（初始化为较大值100）
ad = 1: 第一组数据的最大值（初始化为较小值1）
bx = 100: 第二组数据的最小值（初始化为100）
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    int ax = 100, ad = 1, bx = 100;
    for (int i = 0, x; i < n; ++i) {
        cin >> x;//读入当前数据
        if (ax > x) ax = x;//更新第一组的最小值
        if (ad < x) ad = x;//更新第一组的最大值
    }
    for (int i = 0, x; i < m; ++i) {
        cin >> x;
        if (bx > x) bx = x;//更新第二组的最小值
    }
    if (bx <= ad) { cout << "-1\n"; return 0; }//第二组的最小值 ≤ 第一组的最大值
    if (2 * ax >= bx) { cout << "-1\n"; return 0; }//第一组最小值的2倍 ≥ 第二组最小值
    ad = max(ad, ax * 2);//第一组最大值和第一组最小值的2倍中的较大者
    cout << ad << '\n';
    return 0;
}