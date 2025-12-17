//
// Created by Psy.C on 2025/12/16.
//
/*
*lo：左侧为1的计数
lc：左侧为0的计数
ro：右侧为1的计数
rc：右侧为0的计数
 *
*线性时间复杂度：O(n)，只需一次遍历
常数空间复杂度：只使用几个计数器变量
 *
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll n; cin>>n;
    ll lo = 0, lc = 0, ro = 0, rc = 0;
    for (int i = 0, l, r; i < n; ++i) {
        cin>>l>>r;
        if (l == 1) lo++; else lc++;
        if (r == 1) ro++; else rc++;
    }
    cout << min(rc, ro) + min(lc, lo) << '\n';
    return 0;
}