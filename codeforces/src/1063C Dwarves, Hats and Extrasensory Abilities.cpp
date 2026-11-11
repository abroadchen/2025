//
// Created by Psy.C on 2026/11/11.
//

/**
真正学会的起点..
读入参数 n（可查询的次数上限）。
先输出 0 1 作为基准查询，读回字符串 a。
二分区间初始为 [0, inf]（inf = 1e9）
每次取中点 mid，输出 "mid 1" 作为查询点，读回反馈字符串 b。
比较判定：b 与基准 a 是否相等。
若 a == b：说明 mid 与 0 同侧（落在同一"颜色/性质"区），右移下界 l = mid；
否则：说明 mid 在另一侧，左移上界 r = mid。
这就是标准二分查找的 l/r 更新逻辑，用于逼近两种性质的分界点
最终输出 l 0 与 r 2，提交答案
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int inf = 1e9;


string a, b;
int main() {
    fast;
    int n; cin >> n; cout << "0 1" << endl;
    cin >> a;
    int l = 0, r = inf;
    for (int i = 2; i <= n; i++) {
        int mid = (l+r)>>1;
        cout << mid << " 1" << endl;
        cin >> b;
        if (a == b) l = mid; else r = mid;
    }
    cout << l << " 0 " << r << " 2";
    return 0;
}