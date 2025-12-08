//
// Created by Psy.C on 2025/12/8.
//
/*
*p：输入的原始数字
d：差值限制
*k：位数计数器，从1开始（个位）
ans：答案，初始值为原始数字p
*no：当前尝试的数字，初始为p
x：10的k次方，表示当前处理的位权值（10, 100, 1000...）
*p % x：获取p在当前位以下的数字
p - p % x：将p的低k位清零
p - p % x - 1：再减1，使得低k位变成999...9的形式
*dif：原始数字p与候选数字no的差值
k自增，准备处理更高一位
 *
*如果差值dif不超过限制d：
并且no的低k位大于p的低k位（no % x > p % x）：
更新答案ans为no
否则（差值超过限制d）跳出循环
 *
 */
#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll p, d; cin>>p>>d;
    ll k = 1, ans = p;
    while (true) {
        ll no = p;
        const ll x = static_cast<ll>(pow(10, k));
        no = p - p % x - 1;
        const ll dif = p - no;
        k++;
        if (dif <= d) {
            if (no % x > p % x) ans = no;
        } else break;
    }
    cout << ans;
    return 0;
}