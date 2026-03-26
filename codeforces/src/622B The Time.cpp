//
// Created by Psy.C on 2026/3/26.
//
/**
如果小时小于10，在前面补0
输出小时，然后输出冒号':'
如果分钟小于10，在前面补0
输出分钟
c接收冒号':'字符，但不会被使用
循环a次，每次增加1分钟
m++：分钟加1
if (m == 60) h++, m = 0：如果分钟达到60，小时加1，分钟归0
if (h == 24) h = 0：如果小时达到24，归零（24小时制）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

void get(int h, int m) {
    if (h < 10) cout << 0;
    cout << h << ':';
    if (m < 10) cout << 0;
    cout << m;
}

int h, m, a;
char c;
int main() {
    fast;
    cin >> h >> c >> m >> a;
    while (a--) {
        m++;
        if (m == 60) h++, m = 0;
        if (h == 24) h = 0;
    }
    get(h, m);
    return 0;
}