//
// Created by Psy.C on 2026/3/31.
//
/**
od = 0：奇数位置的起始索引
ev = 1：偶数位置的起始索引
操作1（x == 1）：平移操作
od = (od + y + n) % n：奇偶索引同时平移 y 位
ev = (ev + y + n) % n：+n 防止负数取模
操作2（x != 1）：交换操作
如果 od 为奇数：od 左移1位，ev 右移1位
如果 od 为偶数：od 右移1位，ev 左移1位
从1开始依次填入数字
b[od] = cnt++; b[ev] = cnt++;：在奇偶位置分别填入连续数字
od 和 ev 每次增加2（间隔为2）
时间复杂度：O(n + q)，空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+5;
int n, q, b[N];
int main() {
    fast;
    cin >> n >> q;
    int od = 0, ev = 1, x, y;
    while (q--) {
        cin >> x;
        if (x == 1) {
            cin >> y;
            od = (od + y + n) % n;
            ev = (ev + y + n) % n;
        } else {
            if (od%2) {
                od = (od - 1 + n) % n;
                ev = (ev + 1 + n) % n;
            } else {
                od = (od + 1 + n) % n;
                ev = (ev - 1 + n) % n;
            }
        }
    }
    int cnt = 1;
    while (cnt <= n) {
        b[od] = cnt++; b[ev] = cnt++;
        od = (od + 2 + n) % n;
        ev = (ev + 2 + n) % n;
    }
    for (int i = 0; i < n-1; ++i) cout << b[i] << ' ';
    cout << b[n-1] << '\n';
    return 0;
}