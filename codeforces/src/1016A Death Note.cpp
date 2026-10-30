//
// Created by Psy.C on 2026/10/30.
//

/**
真正学会的起点..
n：天数（轮数），m：桶/槽总容量，a[i]：第 i 天需要的资源量
把 m 当成一个容器的满容量，lst 是当前容器中还剩余的库存量，a[i] 是第 i 天要用掉的量，ans 是第 i 天触发的「装满/换成新容器」的次数。

初始 lst = m：一开始容器是满的。
情况 1：a[i] < lst（当天需要量小于当前剩余）
当天不用补货，直接消耗，剩余 lst -= a[i]，ans 保持 0
情况 2：a[i] >= lst（当天需要量 ≥ 当前剩余，必须重新补充）
a[i] -= lst：用光当前剩余的量，还差 a[i]（此时 ≥ 0）。
lst = m; ans++;：补给一个满容器，次数 +1。
ans += a[i]/m：还差的部分，每凑满一整桶 m 又要补一次。
lst = m - a[i]%m：最后一个容器若没恰好装满用完，剩 m - (a[i]%m) 留给下一天；若 a[i]%m==0 则刚好用完，剩 m（即又满）。
每行输出当天的 ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
using namespace std;

constexpr int N = 2e5+5;

int n, m, a[N];
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) cin >> a[i];
    int lst = m, ans;
    rep(i,n) {
        ans = 0;
        if (a[i] < lst) lst -= a[i];
        else {
            a[i] -= lst; lst = m; ans++;
            ans += a[i]/m;
            lst = m - a[i]%m;
        }
        cout << ans << ' ';
    }
    return 0;
}