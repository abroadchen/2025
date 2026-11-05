//
// Created by Psy.C on 2026/11/5.
//

/**
真正学会的起点..
输出查询区间，读回答。
若 Y 且区间已缩成一个点（l==r），命中目标，exit(0) 结束程序。
否则返回布尔值表示目标是否在该区间
搜索范围为 [1, n]，目标每次可移动 k 步
标准二分：询问 [l, mid]，缩小搜索区间。answer=Y 则压到左半，N 则挪到右半。
防逃逸扩展：每次询问后目标会随机移动最多 k 步，所以必须把区间向外扩 k（但不能越出 [1,n]），即 l=max(1,l-k), r=min(n,r+k)，保证目标还包含在搜索范围内。
随机单点试探：在扩后的区间里随机取一个点 mid，单独询问 [mid, mid]。由于目标会随机移动，随机试探比单纯二分更能跟上目标位置。
再次扩展区间，进入下一轮
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e6+10;

char s[11];
bool ask(ll l, ll r) {
    cout << l << ' ' << r << endl;
    cin >> s;
    if (s[0] == 'Y') {
        if (l == r) exit(0);
        else return 1;
    }
    return 0;
}

ll n, k;
int main() {
    fast;
    srand(time(0));
    cin >> n >> k;
    ll l = 1, r = n;
    while (l <= r) {
        ll mid = l + (r - l) / 2;
        if (ask(l, mid)) r = mid; else l = mid + 1;
        l = max(1ll, l-k); r = min(n, r+k);
        mid = l + rand()%(r-l+1); ask(mid, mid);
        l = max(1ll, l-k); r = min(n, r+k);
    }
    return 0;
}