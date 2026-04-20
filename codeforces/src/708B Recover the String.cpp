//
// Created by Psy.C on 2026/4/19.
//
/**
a00: 00相邻对的数量
a01: 01相邻对的数量
a10: 10相邻对的数量
a11: 11相邻对的数量
l: 0的个数
r: 1的个数
l: 0的个数，通过公式 l*(l-1)/2 = a00 推导
r: 1的个数，通过公式 r*(r-1)/2 = a11 推导
sqrt(2*a00) 近似求解 l*(l-1) ≈ 2*a00
如果没有01或10相邻对（字符串全为0或全为1）
调整l和r的值
特殊情况：全为0时l至少为1
验证计算出的l和r是否满足条件
l*(l-1)/2 = a00：00对数量
r*(r-1)/2 = a11：11对数量
a01 + a10 = l*r：01和10对的总数量
处理01对：
if (r > a01): 如果1的剩余数量大于待处理的01对
输出'1'，减少1的数量
else: 否则输出'0'，减少0的数量，减少a01
输出剩余的1：while (r--) cout << '1';
输出剩余的0：while (l--) cout << '0';
O(l + r): 输出字符串
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a00, a01, a10, a11, l, r;
int main() {
    fast;
    cin >> a00 >> a01 >> a10 >> a11;
    l = 1 + (int)sqrt(2.*a00); r = 1 + (int)sqrt(2.*a11);
    if (a01 + a10 == 0) {
        l = a00 ? l : 0; r = a11 ? r : 0;
        if (a00 + a11 == 0) l = 1;
    }
    if (l*(l-1) != 2*a00 || r*(r-1) != 2*a11 || a01+a10 != l*r) {
        cout << "Impossible\n";
        return 0;
    }
    while (a01) {
        if (r > a01) cout << '1', r--;
        else cout << '0', l--, a01 -= r;
    }
    while (r--) cout << '1';
    while (l--) cout << '0';
    cout << '\n';
    return 0;
}