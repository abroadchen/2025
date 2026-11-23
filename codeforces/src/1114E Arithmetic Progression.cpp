//
// Created by Psy.C on 2026/11/23.
//

/**
真正学会的起点..
输出 > x，读回 0/1，返回是否"最大值 > x"
通过二分 > mid 查询，找到最大值 mx
随机挑（最多 30 个）不同位置的值。
排序后，对相邻差值取 gcd，得到公差
d（因为任意两数之差是 d 的整数倍，gcd 消除倍数因子还原出最小公差）。
用随机化保证样本分布够广，从而 gcd 能还原真实公差
已知最大值 mx = 首项 + (n-1)d，故**首项 = mx − d(n−1)**。
输出 ! <首项> <公差> 给判题器。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 1e6+10, M = 1e9, B = 1048575;

bool check(int x) {
    cout << "> " << x << endl;
    cin >> x;
    return x;
}

int x = M+7, y = M+9, n;
int rnd() { return ((1ll*rand()*x+y+rand())&B)%n + 1; }
int ask(int x) {
    cout << "? " << x << endl;
    cin >> x;
    return x;
}
int gcd(int x, int y) { return !y?x:gcd(y,x%y); }

int mx, p[N], a[31], d;
int main() {
    fast;
    srand(time(0)); cin >> n;
    int l = 0, r = M;
    while (l <= r) {
        int mid = (l+r)>>1;
        if (check(mid)) l = mid+1; else r = mid-1, mx = mid;
    }
    rep(i,n) p[i] = i;
    rep(i,n) swap(p[i], p[rnd()]);//随机打乱位置
    rep(i,min(n,30)) a[i] = ask(p[i]);//问 30 个随机位置的值
    sort(a+1,a+min(n,30)+1);
    d = a[2] - a[1];
    for (int i = 2; i < min(n,30); i++) d = gcd(d,a[i+1]-a[i]);
    cout << "! " << mx-d*(n-1) << ' ' << d << endl;
    return 0;
}