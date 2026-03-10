//
// Created by Psy.C on 2026/3/9.
//
/**
n：数字总数
k：需要选择的数字个数
od：奇数的个数
ev：偶数的个数
n1：剩余奇数位置数
n2：剩余偶数位置数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, k, od, ev, n1, n2;
int get() {
    if (n == k) return od%2;//如果全部选择，奇数个数决定胜负
    if (n1 > n2) {//奇数位置更多
        if (n2 >= od) return 0;//奇数不够用，Daenerys赢
        if (n2 < ev) return 1;//偶数够用，Stannis赢
        return k%2;//只能用奇数，看k的奇偶性
    }
    if (n1 >= ev) return k%2;//偶数不够用，看k的奇偶性
    return 0;//Daenerys赢
}


int main() {
    fast;
    cin >> n >> k;
    od = 0, ev = 0, n1 = (n-k+1)/2, n2 = (n-k)/2;
    for (int i = 1, c; i <= n; ++i) {
        cin >> c;
        if (c%2) od++; else ev++;
    }
    int f = get();
    if (f) cout << "Stannis\n"; else cout << "Daenerys\n";
    return 0;
}