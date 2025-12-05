//
// Created by Psy.C on 2025/12/5.
//
/*
*x：目标分数
t：时间限制（射击次数上限）
a：第一次射击的初始分数
b：第二次射击的初始分数
da：第一次射击每次时间步的分数减少量
db：第二次射击每次时间步的分数减少量
 *
*i：第一次射击的时间步（0到t-1）
j：第二次射击的时间步（0到t-1）
检查以下几种情况是否能满足目标分数x：
x == a - da * i + b - db * j：两次射击都进行，总分等于目标
x == 0：目标分数为0（可能表示不射击）
x == a - da * i：只进行第一次射击，分数等于目标
x == b - db * j：只进行第二次射击，分数等于目标
 *
 *时间复杂度：O(t²)，空间复杂度：O(1)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=0;i<n;++i)
using namespace std;


int main() {
    fast;
    int x, t, a, b, da, db;
    cin >> x >> t >> a >> b >> da >> db;
    rep(i,t) rep(j,t) {
        if (x == a - da * i + b - db * j || x == 0 ||
            x == a - da * i || x == b - db * j) {
            cout << "YES"; return 0;
        }
    }
    cout << "NO";
    return 0;
}