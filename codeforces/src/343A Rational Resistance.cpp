//
// Created by Psy.C on 2026/1/13.
//
///O(log(min(a,b)))
/**
* 每次将较大的数减去较小的数
当能整除时，用整除的结果批量计算步数
直到其中一个数变为0
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll a, b, ans = 0; cin >> a >> b;
    while (true) {
        if (a < b) {
            b -= a;
            swap(a, b);//确保a ≥ b
            ans++;//步数加1
        }
        ans += a / b;//a中包含多少个完整的b
        a %= b;//更新a为余数
        if (!a || !b) break;//当a或b为0时停止
    }
    cout << ans << '\n';
    return 0;
}