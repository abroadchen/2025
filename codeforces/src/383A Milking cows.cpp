//
// Created by Psy.C on 2026/1/26.
//
/*
* // 此时 a[l] == 1, a[r] == 0，需要处理这对逆序
    ans += z;      // 把右边的0移到左边需要跨越z个剩余的0
    l++;           // 左指针前进（已处理a[l]）
    o--;           // 因为a[l]原本是1，现在被处理了，所以剩余1的计数减1
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 200007
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    int z = 0, o = 0, a[N];
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i] == 0) z++; else o++;
    }
    ll ans = 0;
    int l = 1, r = n;
    while (l <= r) {
        while (a[l] == 0 && l <= r) { l++; z--; }//跳过左边的0，并减少0的计数
        while (a[r] == 1 && l <= r) { r--; o--; }//跳过右边的1，并减少1的计数
        if (l > r) break;//如果指针相遇则结束
        ans += z;//将当前剩余的0的个数加到答案中
        l++; o--;//移动左指针，减少1的计数（相当于交换了a[l]和a[r]）
    }
    cout << ans << '\n';
    return 0;
}