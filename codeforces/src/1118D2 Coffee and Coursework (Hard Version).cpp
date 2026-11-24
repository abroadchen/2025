//
// Created by Psy.C on 2026/11/24.
//

/**
真正学会的起点..
ans=累计贡献 cnt=当前衰减轮次 t=下一个要用的任务指针
模拟用 x 天安排：
每"轮"（cnt）给 x 天各放 1 个任务，第 cnt 轮的任务都减去 cnt 的衰减。
若某任务放进某天时 a[t]-cnt <= 0（衰减到非正）或任务已用完 t>n，则 flg=0 结束，判定不达标。
累计贡献 ans 达到 ≥ m 即真
天数范围 [1, n]，二分：可行就缩小上界，不可行升下界。
f 记录是否曾找到过可行解；最后若从未可行（f 仍 true）且 r 也不可行 → -1，否则输出 r
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 2e5+10;

int m, a[N], n;
inline bool check(int x) {
    int ans = 0, cnt = 0, t = 1;
    bool flg = 1;
    while (ans < m && flg) {//未达标且有任务可放时继续
        rep(i,x) {
            ans += a[t]-cnt; t++;//实际贡献 = 原值 - 衰减
            if (a[t]-cnt <= 0 || t > n) { flg = 0; break; }
        }
        cnt++;//完成一轮，衰减 +1
    }
    return ans >= m;
}

bool f;
int main() {
    fast;
    f = 1; cin >> n >> m;
    rep(i,n) cin >> a[i];
    sort(a+1,a+n+1,greater<>());
    int l = 1, r = n;
    while (l < r) {
        int mid = (l+r)>>1;
        if (check(mid)) f = 0, r = mid; else l = mid+1;
    }
    if (f && !check(r)) cout << "-1"; else cout << r;
    return 0;
}