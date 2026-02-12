//
// Created by Psy.C on 2026/2/12.
//
/**
c - 'A' + 1：将字符转换为索引（'A'→1，'B'→2，...，'Z'→26）
num[c - 'A' + 1]++：对应字母的计数加1
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 50
using namespace std;

ll n, k, num[N];

int main() {
    fast;
    cin >> n >> k; char c;
    for (int i = 1; i <= n; ++i) {
        cin >> c;
        num[c - 'A' + 1]++;
    }
    sort(num + 1, num + 26 + 1);
    int i = 26; //从字母表末尾开始（字母Z对应的位置）
    ll ans = 0;
    while (num[i] != 0) {//当前字母计数不为0时
        if (k <= num[i]) { ans += k*k; break; }
        ans += num[i]*num[i];
        k -= num[i];
        i--;//移到前一个字母（计数较少的字母）
    }
    cout << ans << '\n';
    return 0;
}