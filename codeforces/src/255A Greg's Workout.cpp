//
// Created by Psy.C on 2025/12/18.
//
/*
*cnt[0]：用于存储第一组元素的和
cnt[1]：用于存储第二组元素的和
cnt[2]：用于存储第三组元素的和
 *
*如果下标i除以3余0（即i=0,3,6,9...），将a[i]加到cnt[0]
如果下标i除以3余1（即i=1,4,7,10...），将a[i]加到cnt[1]
如果下标i除以3余2（即i=2,5,8,11...），将a[i]加到cnt[2]
 *
*如果第一组（cnt[0]）的和最大，输出"chest"（胸部）
如果第二组（cnt[1]）的和最大，输出"biceps"（肱二头肌）
否则（第三组cnt[2]的和最大或存在相等情况），输出"back"（背部）
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll n; cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    ll cnt[3] = {};
    for (int i = 0; i < n; ++i) {
        if (i % 3 == 0) cnt[0] += a[i];
        else if (i % 3 == 1) cnt[1] += a[i];
        else cnt[2] += a[i];
    }
    if (cnt[0] > cnt[1] && cnt[0] > cnt[2]) cout << "chest\n";
    else if (cnt[1] > cnt[0] && cnt[1] > cnt[2]) cout << "biceps\n";
    else cout << "back\n";
    return 0;
}