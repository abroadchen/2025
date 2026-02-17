//
// Created by Psy.C on 2026/2/17.
//
/**
d == 0：区间长度为0，只有一个数，无法找到三个数
d == 1：区间长度为1，只有两个数，无法找到三个数
d == 2 && l&1 && r&1：区间长度为2且两端都是奇数
l&1：判断l是否为奇数（与1按位与，奇数最低位为1）
r&1：判断r是否为奇数
如果l是奇数，r也是奇数，且r=l+2，那么三个连续数是{l,l+1,l+2}
如果l和r都奇数，则l和l+2都是奇数，只有l+1是偶数，无法找到三个互质的数

时间复杂度：O(1)
空间复杂度：O(1)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll l, r, d;
int main() {
    fast;
    cin >> l >> r; d = r - l;
    if (d == 0 || d == 1 || (d == 2 && l&1 && r&1))
        cout << "-1\n";
    else {
        while (l&1 && l < r) l++;//找到一个偶数作为起始点 {even, odd, even+2}
        cout << l << ' ' << l + 1 << ' ' << l + 2 << '\n';
    }
    return 0;
}