//
// Created by Psy.C on 2025/12/23.
//
/*
 *auto& i : a遍历每一行，auto& j : i遍历每一行的每个元素
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=0;i<n;++i)
using namespace std;


int main() {
    fast;
    int a[3][3], x;
    for (auto& i : a) for (auto& j : i) j = 1;
    rep(i,3) rep(j,3) {
        cin >> x;//读入每个位置的操作次数x
        if (x % 2 == 1) {//只有奇数次操作才有效果
            a[i][j] = 1 - a[i][j];//翻转当前位置的值
            if (i - 1 >= 0) a[i-1][j] = 1 - a[i-1][j];//翻转相邻四个位置的值（上、下、左、右）
            if (i + 1 < 3) a[i+1][j] = 1 - a[i+1][j];
            if (j - 1 >= 0) a[i][j-1] = 1 - a[i][j-1];
            if (j + 1 < 3) a[i][j+1] = 1 - a[i][j+1];
        }
    }
    for (const auto& i : a) rep(j,3) {
        //每行的前两个元素，直接输出不换行
        if (j < 2) cout << i[j]; else cout << i[j] << '\n';
    }
    return 0;
}