//
// Created by Psy.C on 2026/4/20.
//
/**
n: 物品数量
b: 单个物品的最大容量限制
d: 容器的容量
O(n): 遍历一次物品数组
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, b, d;
int main() {
    fast;
    cin >> n >> b >> d;
    int num = 0;//容器计数器
    for (int i = 0, a, tot = 0; i < n; ++i) {
        cin >> a;
        if (a <= b) {
            tot += a;//将物品加入当前容器
            if (tot > d) {
                num++;
                tot = 0;//重置当前容器总量为0
            }
        }
    }
    cout << num << '\n';
    return 0;
}